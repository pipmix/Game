#pragma once
#include "Common.h"
class Mesh{


public:
	Mesh(ID3D11Device* d, wstring fn);
	void Set(ID3D11DeviceContext* c);
	~Mesh();

private:


	ComPtr<ID3D11Buffer>		mVertexBuffer;
	ComPtr<ID3D11InputLayout>	mInputLayout;
	ComPtr<ID3D11Buffer>		mIndexBuffer;

	wstring fileName;

	string materialName;
	string textureName;
	int numOfVertices;
	int numOfIndices;



};

