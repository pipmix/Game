#pragma once


#include <d3d11_1.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXCollision.h>
#pragma comment(lib, "d3d11.lib")

#include <wrl\client.h>
#include <string>
#include <ppltasks.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

#include <amp.h>




using namespace DirectX;
using namespace std;
using namespace Concurrency::direct3d;

using Microsoft::WRL::ComPtr;

const wstring gPath = L"C:/Files/";
const wstring gTexturePath = L"Textures/";
const wstring gShaderPath = L"Shaders/";
const wstring gMeshPath = L"Meshes/";



// Data types





struct CBUFFER {

	XMFLOAT4X4 s_FinalMatrix;
	XMFLOAT4X4 s_WorldMatrix;
	XMFLOAT4X4 screenMatrix;

};

struct CBBUFFER_AMBIENT{

	XMFLOAT3 vAmbientLower;
	float pad;
	XMFLOAT3 vAmbientRange;
	float pad2;

};

struct VERTEXP {

	XMFLOAT3 position;

};


static const D3D11_INPUT_ELEMENT_DESC layoutP[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }

};

struct VERTEXPNU {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};

const D3D11_INPUT_ELEMENT_DESC layoutPNU[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

enum INPUTVALUES {

	INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, INPUT_A, INPUT_B, INPUT_X, INPUT_Y, INPUT_L, INPUT_R, INPUT_START, INPUT_SELECT, INPUT_RAISE, INPUT_LOWER, INPUT_ROTATELEFT, INPUT_ROTATERIGHT


};


struct GBUFFERUNPACK{
	XMFLOAT4 PerspectiveValues;
	XMFLOAT4X4  ViewInv;
};



enum LIGHT_TYPE{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_CAPSULE
};


struct Light{

	LIGHT_TYPE m_LightType;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Direction;
	float m_Range;
	float m_Length;
	float m_OuterAngle;
	float m_InnerAngle;
	XMFLOAT3 m_Color;
};


