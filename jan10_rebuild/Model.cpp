#include "Model.h"



Model::Model(ID3D11Device* d, ID3D11DeviceContext* c, wstring fn, int mt) : mDevice(d), mContext(c), fileName(fn), modelType(mt) {

	if (modelType == 0 ) mPosition = { 0.0f,0.0f,0.0f };
	else if (modelType == 1) mPosition = { 0.0f, 0.0f,0.0f };
	else if (modelType == 2) mPosition = { 0.0f, 0.0f,0.0f };


	texture = new Texture(fileName, mDevice, 1);

	

	LoadShaders();
	LoadMesh();
}


Model::~Model(){



}

void Model::SetLocation(XMFLOAT3 l) {

	mPosition = l;
	//XMMATRIX translateMatrix = XMMatrixTranslation(l.x,l.y,l.z);
	//XMStoreFloat4x4(&mWorldMatrix, translateMatrix);

}
void Model::Move(XMFLOAT3 l) {

}




void Model::LoadShaders() {

	wstring vertexDir;
	wstring pixelDir;

	

	if (modelType == 0) {

		vertexDir = gPath + gShaderPath + L"VertexShader.cso";
		pixelDir = gPath + gShaderPath + L"PixelShader.cso";

	} else if (modelType == 2) {

		vertexDir = gPath + gShaderPath + L"BasicVS.cso";
		pixelDir = gPath + gShaderPath + L"BasicPS.cso";

	} else if (modelType == 1) {

		vertexDir = gPath + gShaderPath + L"HemisphereicVS.cso";
		pixelDir = gPath + gShaderPath + L"HemisphereicPS.cso";
		modelType = 1;
	}

	
	D3DReadFileToBlob(vertexDir.c_str(), &mVertexBlob);
	mDevice->CreateVertexShader(mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), NULL, &mVertexShader);

	
	
	ID3DBlob* pixelBlob;
	D3DReadFileToBlob(pixelDir.c_str(), &pixelBlob);
	mDevice->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), NULL, &mPixelShader);
	pixelBlob->Release();

	if (modelType == 0) {

		mDevice->CreateInputLayout(layoutP, ARRAYSIZE(layoutP), mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), &mInputLayout);

	}
	else if (modelType == 1) {

		mDevice->CreateInputLayout(layoutPNU, ARRAYSIZE(layoutPNU), mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), &mInputLayout);

	}



}


void Model::SetShaders() {

	mContext->VSSetShader(mVertexShader.Get(), 0, 0);
	mContext->PSSetShader(mPixelShader.Get(), 0, 0);

	if (modelType == 1) {
		mContext->PSSetShaderResources(0, 1, texture->ReturnTexture().GetAddressOf());

	}
	if (modelType == 2) {
		mContext->PSSetShaderResources(0, 1, texture->ReturnTexture().GetAddressOf());

	}
}

void Model::SetBuffers() {

	UINT stride = sizeof(VERTEXPNU);
	UINT offset = 0;

	mContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	mContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	mContext->IASetInputLayout(mInputLayout.Get());
	
}

void Model::Draw() {

	SetShaders();
	SetBuffers();
	mContext->DrawIndexed(indexCount, 0, 0);

}

void Model::Update() {

	time += 0.00f;



	XMMATRIX matRotate = XMMatrixRotationY(time) * XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	
	XMStoreFloat4x4(&mWorldMatrix, matRotate);


}

void Model::LoadMesh() {

	wstring completePathAndName = gPath + gMeshPath + fileName + L".mesh";
	ifstream file(completePathAndName);

	if (file) {

		file >> materialName >> textureName >> numOfIndices >> numOfVertices;

		unsigned short * indices = new unsigned short[numOfIndices];
		for (int i = 0; i < numOfIndices; i++) file >> indices[i];

		indexCount = numOfIndices;
		


		VERTEXPNU* vertices = new VERTEXPNU[numOfVertices];

		for (int i = 0; i < numOfVertices; i++) {
			file >> vertices[i].pos.x
				>> vertices[i].pos.y
				>> vertices[i].pos.z
				>> vertices[i].normal.x
				>> vertices[i].normal.y
				>> vertices[i].normal.z
				>> vertices[i].uv.x
				>> vertices[i].uv.y;
		}
		file.close();

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VERTEXPNU)*numOfVertices, D3D11_BIND_VERTEX_BUFFER);

		mDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mVertexBuffer);


		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short)*numOfIndices, D3D11_BIND_INDEX_BUFFER);

		
		mDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &mIndexBuffer);

		delete[] vertices;
		delete[] indices;

	}


}

XMFLOAT4X4* Model::GetWorldMatrix() {

	return &mWorldMatrix;
}
