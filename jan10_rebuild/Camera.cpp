#include "Camera.h"

float WrapAngle(float x) {
	if (x < -XM_PI)return (x + XM_PI);
	else if (x > XM_PI) return (x - XM_PI);
	else return x;
}

Camera::Camera(HWND& hwnd, Player* p, Input* in) : m_Player(p), m_Input(in){

	RECT rc = { 0,0,0,0 };
	GetClientRect(hwnd, &rc);
	m_ClientWidth =  rc.right;
	m_ClientHeight = rc.bottom;
	m_Fov = XMConvertToRadians(45);
	m_AspectRatio = static_cast<float>(m_ClientWidth) / static_cast<float>(m_ClientHeight);
	m_NearClip = 0.1f;
	m_FarClip = 1000.0f;

	m_CameraPosition = m_Player->GetPosition();
	m_CameraLookAt = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_CameraUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_CameraSpeed = 0.02f;

	m_CameraPosition = XMFLOAT3{ 5.0f, 2.0f, 5.0f };
	m_CameraRotation = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	UpdateLookAt();
	m_PrevMousePosition = m_Input->GetMousePosition();
}

Camera::~Camera(){
}

XMMATRIX Camera::CreateCameraMatrix(){

	XMVECTOR pos, lookAt, uP;
	pos = XMLoadFloat3(&m_CameraPosition);
	lookAt = XMLoadFloat3(&m_CameraLookAt);
	uP = XMLoadFloat3(&m_CameraUp);

	XMMATRIX cameraMatrix = XMMatrixLookAtLH(pos, lookAt, uP);

	return cameraMatrix;


}

XMMATRIX Camera::CreateScreenMatrix() {

	XMMATRIX screenMatrix = XMMatrixPerspectiveFovLH(m_Fov, m_AspectRatio, m_NearClip, m_FarClip);

	return screenMatrix;
}




void Camera::Update(float t){


	if (m_Input->IsPressed(INPUT_ROTATELEFT))m_CameraRotation.y -= (m_CameraSpeed * t) / 2;
	if (m_Input->IsPressed(INPUT_ROTATERIGHT))m_CameraRotation.y += (m_CameraSpeed * t) / 2;



	// MOVE
	XMFLOAT3 moveFloat = XMFLOAT3{ 0.0f,0.0f,0.0f };

	if (m_Input->IsPressed(INPUT_UP))moveFloat.z = 1.0f;
	if (m_Input->IsPressed(INPUT_DOWN))moveFloat.z = -1.0f;
	if (m_Input->IsPressed(INPUT_RIGHT))moveFloat.x = 1.0f;
	if (m_Input->IsPressed(INPUT_LEFT))moveFloat.x = -1.0f;

	XMVECTOR moveVector = XMLoadFloat3(&moveFloat);

	XMVector3Normalize(moveVector);
	moveVector *=  t * m_CameraSpeed;

	Move(moveVector);
	// END MOVE

	XMMATRIX cameraScreenMatrix = CreateCameraMatrix() * CreateScreenMatrix();
	XMStoreFloat4x4(&m_CameraScreenMatrix, cameraScreenMatrix);

	m_PrevMousePosition = m_MousePosition;
	
}

void Camera::MoveCameraTo(XMFLOAT3 pos, XMFLOAT3 rot) {

	m_CameraPosition = pos;
	m_CameraRotation = rot;
	UpdateLookAt();

}


void Camera::UpdateLookAt() {


	XMMATRIX rotationMatrix = XMMatrixRotationX(m_CameraRotation.x) * XMMatrixRotationY(m_CameraRotation.y);
	XMVECTOR lookAtOffset = XMVector3Transform(XMVECTOR{0.0f, 0.0f, 1.0f}, rotationMatrix);
	XMVECTOR cameraPosition = XMLoadFloat3(&m_CameraPosition);
	XMVECTOR cameraLookAt = cameraPosition + lookAtOffset;
	XMStoreFloat3(&m_CameraLookAt, cameraLookAt);

}

XMFLOAT4X4& Camera::GetCameraScreenMatrix() {

	return m_CameraScreenMatrix;
}

XMVECTOR Camera::PreviewMove(XMVECTOR amount) {

	XMMATRIX rotate = XMMatrixRotationY(m_CameraRotation.y);
	XMVECTOR movement = amount;
	movement = XMVector3Transform(movement, rotate);
	XMVECTOR position = XMLoadFloat3(&m_CameraPosition);
	//XMStoreFloat3(&m_CameraPosition, position);
	return position + movement;

}


void Camera::Move(XMVECTOR scale) {

	XMFLOAT3 temp; 
	XMStoreFloat3(&temp, PreviewMove(scale));

	MoveCameraTo(temp, m_CameraRotation);


}