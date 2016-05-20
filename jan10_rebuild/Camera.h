#pragma once
#include "Common.h"
#include "Player.h"

class Camera{

public:

				Camera			(HWND& h, Player* p, Input* in);
				~Camera			();


				void	MoveCameraTo(XMFLOAT3 pos, XMFLOAT3 rot);

				XMMATRIX CreateScreenMatrix();
				XMMATRIX CreateCameraMatrix();

				void UpdateLookAt();


				XMVECTOR PreviewMove(XMVECTOR amount);


				void Move(XMVECTOR scale);

	void		Update			(float t);

	
	XMFLOAT4X4& GetCameraScreenMatrix();

private:


	XMFLOAT3 	m_CameraPosition;
	XMFLOAT3 	m_CameraRotation;
	float		m_CameraSpeed;
	XMFLOAT3	m_CameraLookAt;
	XMFLOAT3	m_CameraUp;

	// Settings
	float		m_Fov;
	float		m_AspectRatio;
	float		m_NearClip;
	float		m_FarClip;
	LONG		m_ClientWidth;
	LONG		m_ClientHeight;

	Input*		m_Input;


	XMFLOAT3 m_MouseRotationBuffer;

	Player*		m_Player;

	XMFLOAT4X4 m_CameraMatrix;
	XMFLOAT4X4 m_ScreenMatrix;
	XMFLOAT4X4 m_CameraScreenMatrix;

	XMFLOAT2 m_MousePosition;
	XMFLOAT2 m_PrevMousePosition;

};

