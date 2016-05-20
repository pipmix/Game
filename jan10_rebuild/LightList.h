#pragma once
#include "Common.h"
class LightList{


public:

	LightList(ID3D11Device* d, ID3D11DeviceContext* c);
	~LightList();

	void SetAmbientLight(XMFLOAT3 lowColor,  XMFLOAT3 upColor);
	void SetDirectionalLight(XMFLOAT3 direction,  XMFLOAT3 color);


	void ClearLights();

	void AddPointLight(XMFLOAT3 pos, float range, XMFLOAT3 color);
	void AddSpotLight(XMFLOAT3 pos, XMFLOAT3 direction, float range, float outAngle, float inAngle,  XMFLOAT3 color);


	void DoLighting(ID3D11ShaderResourceView* ds, ID3D11ShaderResourceView* color, ID3D11ShaderResourceView* normal, ID3D11ShaderResourceView* spec);
	void DirectionalLight();

private:

	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_Context;

	ComPtr<ID3D11VertexShader>	m_pDirLightVertexShader;
	ComPtr<ID3D11PixelShader>	m_pDirLightPixelShader;
	ComPtr<ID3D11Buffer>		m_pDirLightCB;

	// Depth state with no writes and stencil test on
	ComPtr<ID3D11DepthStencilState> m_pNoDepthWriteLessStencilMaskState;


	XMFLOAT3 m_AmbientLowerColor;
	XMFLOAT3 m_AmbientUpperColor;
	XMFLOAT3 m_DirectionalDir;
	XMFLOAT3 m_DirectionalColor;

	vector<Light> m_ArrLights;

};