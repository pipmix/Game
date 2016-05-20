#pragma once
#include "Common.h"
#include "Texture.h"

class Model
{
public:
	Model(ID3D11Device* d, ID3D11DeviceContext* c, wstring f, int t);
	~Model();

	void LoadShaders();
	void SetShaders();
	void SetBuffers();
	void SetLocation(XMFLOAT3 l);
	void Move(XMFLOAT3 l);


	void LoadMesh();

	void Draw();
	void Update();

	XMFLOAT4X4* GetWorldMatrix();


private:

	ComPtr<ID3D11VertexShader> mVertexShader;
	ComPtr<ID3D11PixelShader> mPixelShader;
	ID3DBlob* mVertexBlob;
	
	ComPtr<ID3D11Buffer>		mVertexBuffer;
	ComPtr<ID3D11InputLayout>	mInputLayout;
	ComPtr<ID3D11Buffer>		mIndexBuffer;
	
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;

	int indexCount;

	float time = 0.0f;

	XMFLOAT3 mPosition;
	XMFLOAT4X4 mWorldMatrix;


	int modelType;

	wstring fileName;
	string materialName;
	string textureName;
	int numOfVertices;
	int numOfIndices;


	wstring shaderName;
	wstring meshName;

	Texture* texture;

};

