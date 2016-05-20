#include "LightList.h"


struct CB_DIRECTIONAL{
	XMFLOAT3 vAmbientLower;
	float pad;
	XMFLOAT3 vAmbientRange;
	float pad2;
	XMFLOAT3 vDirToLight;
	float pad3;
	XMFLOAT3 vDirectionalColor;
	float pad4;
};



LightList::LightList(ID3D11Device* d, ID3D11DeviceContext* c) : m_Device(d), m_Context(c) {


	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.ByteWidth = sizeof(CB_DIRECTIONAL);
	m_Device->CreateBuffer(&cbDesc, NULL, &m_pDirLightCB);

	// LOAD HLSL DirLight.hlsl!!!!!!!!!!!!! add to a WCHAR str array
	// Read the HLSL file

	wstring vertexDir = gPath + gShaderPath + L"DirLightVS.cso";
	wstring pixelDir = gPath + gShaderPath + L"DirLightPS.cso";


	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ID3DBlob* vertexBlob;
	D3DReadFileToBlob(pixelDir.c_str(), &vertexBlob);
	m_Device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), NULL, &m_pDirLightVertexShader);
	vertexBlob->Release();

	ID3DBlob* pixelBlob;
	D3DReadFileToBlob(pixelDir.c_str(), &pixelBlob);
	m_Device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), NULL, &m_pDirLightPixelShader);
	pixelBlob->Release();


	D3D11_DEPTH_STENCIL_DESC descDepth;
	descDepth.DepthEnable = TRUE;
	descDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	descDepth.DepthFunc = D3D11_COMPARISON_LESS;
	descDepth.StencilEnable = TRUE;
	descDepth.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	descDepth.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	const D3D11_DEPTH_STENCILOP_DESC noSkyStencilOp = { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_EQUAL };
	descDepth.FrontFace = noSkyStencilOp;
	descDepth.BackFace = noSkyStencilOp;
	m_Device->CreateDepthStencilState(&descDepth, &m_pNoDepthWriteLessStencilMaskState);

}



LightList::~LightList()
{

}

	

void LightList::DoLighting(ID3D11ShaderResourceView* ds, ID3D11ShaderResourceView* color, ID3D11ShaderResourceView* normal, ID3D11ShaderResourceView* spec) {
	
	m_Context->OMSetDepthStencilState(m_pNoDepthWriteLessStencilMaskState.Get(), 1);

	ID3D11ShaderResourceView* arrViews[4] = { ds, color, normal , spec };
	m_Context->PSSetShaderResources(0, 4, arrViews);

	DirectionalLight();

	ZeroMemory(arrViews, sizeof(arrViews));
	m_Context->PSSetShaderResources(0, 4, arrViews);
}

void LightList::DirectionalLight(){


	D3D11_MAPPED_SUBRESOURCE MappedResource;
	m_Context->Map(m_pDirLightCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	CB_DIRECTIONAL* pDirectionalValuesCB = (CB_DIRECTIONAL*)MappedResource.pData;
	pDirectionalValuesCB->vAmbientLower = m_AmbientLowerColor;

	XMFLOAT3 temp1;
	temp1.x = m_AmbientUpperColor.x - m_AmbientLowerColor.x;
	temp1.y = m_AmbientUpperColor.y - m_AmbientLowerColor.y;
	temp1.z = m_AmbientUpperColor.z - m_AmbientLowerColor.z;
	pDirectionalValuesCB->vAmbientRange = temp1;

	XMFLOAT3 temp2 = m_DirectionalDir;
	temp2.x = m_DirectionalDir.x * -1;
	temp2.y = m_DirectionalDir.y * -1;
	temp2.z = m_DirectionalDir.z * -1;
	pDirectionalValuesCB->vDirToLight = temp2;
	pDirectionalValuesCB->vDirectionalColor = m_DirectionalColor;
	m_Context->Unmap(m_pDirLightCB.Get(), 0);
	m_Context->PSSetConstantBuffers(1, 1, &m_pDirLightCB);

	m_Context->IASetInputLayout(NULL);
	m_Context->IASetVertexBuffers(0, 0, NULL, NULL, NULL);
	m_Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Context->VSSetShader(m_pDirLightVertexShader.Get(), NULL, 0);
	m_Context->GSSetShader(NULL, NULL, 0);
	m_Context->PSSetShader(m_pDirLightPixelShader.Get(), NULL, 0);
	m_Context->Draw(4, 0);

	ID3D11ShaderResourceView *arrRV[1] = { NULL };
	m_Context->PSSetShaderResources(4, 1, arrRV);
	m_Context->VSSetShader(NULL, NULL, 0);
	m_Context->PSSetShader(NULL, NULL, 0);
	m_Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}




void LightList::SetAmbientLight(XMFLOAT3 vAmbientLowerColor, XMFLOAT3 vAmbientUpperColor){
	m_AmbientLowerColor = vAmbientLowerColor;
	m_AmbientUpperColor = vAmbientUpperColor;
}

// Set the directional light values
void LightList::SetDirectionalLight(XMFLOAT3 vDirectionalDir, XMFLOAT3 vDirectionalCorol){

	XMStoreFloat3(&m_DirectionalDir, XMVector3Normalize(XMLoadFloat3(&vDirectionalDir)));
	m_DirectionalColor = vDirectionalCorol;
}


void LightList::ClearLights() { 
	m_ArrLights.clear(); 
}


void LightList::AddPointLight(XMFLOAT3 vPointPosition, float fPointRange, XMFLOAT3 vPointColor){

	Light pointLight;
	pointLight.m_LightType = LIGHT_POINT;
	pointLight.m_Position = vPointPosition;
	pointLight.m_Range = fPointRange;
	pointLight.m_Color = vPointColor;
	m_ArrLights.push_back(pointLight);
}

void LightList::AddSpotLight(XMFLOAT3 vSpotPosition, XMFLOAT3 vSpotDirection, float fSpotRange,float fSpotOuterAngle, float fSpotInnerAngle, XMFLOAT3 vSpotColor){
	
	Light spotLight;

	spotLight.m_LightType = LIGHT_SPOT;
	spotLight.m_Position = vSpotPosition;
	spotLight.m_Direction = vSpotDirection;
	spotLight.m_Range = fSpotRange;
	spotLight.m_OuterAngle = XM_PI * fSpotOuterAngle / 180.0f;
	spotLight.m_InnerAngle = XM_PI * fSpotInnerAngle / 180.0f;
	spotLight.m_Color = vSpotColor;
	m_ArrLights.push_back(spotLight);
}