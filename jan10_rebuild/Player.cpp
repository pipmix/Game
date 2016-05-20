#include "Player.h"



Player::Player(Input* i) : m_Input(i){
	m_FacingVector = XMFLOAT3{ 1.0f, 0.0f, 0.0f };
	m_SideVector = XMFLOAT3{ 0.0f, 0.0f, 1.0f };
	m_UpVector = XMFLOAT3{ 0.0f, 1.0f, 0.0f };

}


Player::~Player(){
}


void Player::Update(float time) {

	m_MoveBackForward = 0.0f;
	m_MoveLeftRight = 0.0f;
	m_MoveUpDown = 0.0f;
	m_Yaw = 0.0f;


	if (m_Input->IsPressed(INPUT_UP))	 m_MoveBackForward += (speed * time);

	
	if (m_Input->IsPressed(INPUT_DOWN))		m_MoveBackForward -= (speed * time);

	
	if (m_Input->IsPressed(INPUT_RIGHT)) {

		m_MoveLeftRight -= (speed * time);

	}
	if (m_Input->IsPressed(INPUT_LEFT)) {

		m_MoveLeftRight += (speed * time);

	}
	if (m_Input->IsPressed(INPUT_RAISE)) {

		m_MoveUpDown += (speed * time);

	}
	if (m_Input->IsPressed(INPUT_LOWER)) {

		m_MoveUpDown -= (speed * time);

	}
	if (m_Input->IsPressed(INPUT_ROTATELEFT)) {

		//m_Yaw += (speed * time);
		m_FacingVector.z += (0.01f * time);
		

	}
	if (m_Input->IsPressed(INPUT_ROTATERIGHT)) {

		//m_Yaw -= (speed * time);
		m_FacingVector.z -= (0.01f * time);

	}

	m_MouseDelta = m_Input->GetMouseDelta();

	m_Position.x += m_MoveBackForward;
	m_Position.z += m_MoveLeftRight;
	m_Position.y += m_MoveUpDown;

	//m_Yaw += m_MouseDelta.x * (time * speed);
	//m_Pitch += m_MouseDelta.y * (time * speed);
	XMVECTOR posss = XMVECTOR{ 1.0f,1.0f,1.0f };
	XMVECTOR tt = XMQuaternionIdentity();

	//XMVECTOR test = XMLoadFloat3(&m_FacingVector);

	
	//XMVector3Rotate()


	//XMMATRIX TEMPER = XMMatrixRotationRollPitchYaw(XMConvertToRadians( m_Yaw*time*speed), XMConvertToRadians(m_Yaw*time*speed), XMConvertToRadians(m_Yaw*time*speed));
	//XMVector3Transform(test, TEMPER);
	////XMVector3Normalize(test);

	//XMStoreFloat3(&m_FacingVector, test);



}


XMFLOAT3& Player::GetPosition() {
	return m_Position;
}

XMFLOAT3& Player::GetLookingAtDirection() {

	return m_FacingVector;
}

void Player::SetPosition(XMFLOAT3 p) {

	m_Position = p;

}

