#pragma once
#include "Common.h"
#include "Input.h"

class Player{

public:
	Player(Input* input);
	~Player();

	void Update(float time);

	void SetPosition(XMFLOAT3 p);
	XMFLOAT3& GetPosition();
	XMFLOAT3& GetLookingAtDirection();


	void Rotate(float angle, XMFLOAT3 axis);



private:

	XMFLOAT3 m_Position;


	XMFLOAT3 m_FacingVector;
	XMFLOAT3 m_UpVector;
	XMFLOAT3 m_SideVector;


	Input* m_Input;

	XMFLOAT4 m_Quat;


	float m_MoveLeftRight = 0.0f;
	float m_MoveBackForward = 0.0f;
	float m_MoveUpDown = 0.0f;

	float m_RotateUp = 0.0f;
	float m_RotateSide = 0.0f;


	float speed = 0.1f;

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;

	XMFLOAT2 m_MouseDelta;
};

