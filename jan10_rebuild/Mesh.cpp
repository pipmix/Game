#include "Mesh.h"



Mesh::Mesh(ID3D11Device* d, wstring fn) : fileName(fn){


	wstring completePathAndName = gPath + gMeshPath + fileName + L".mesh";
	string completeName(completePathAndName.begin(), completePathAndName.end());




	ifstream file(completePathAndName);




	if (file) {

		file >> materialName >> textureName >> numOfIndices >> numOfVertices;

		unsigned short* indices = new unsigned short[numOfIndices];

		for (int i = 0; i < numOfIndices; i++) file >> indices[i];
		

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

		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
		

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(indices), D3D11_BIND_INDEX_BUFFER);

		d->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mVertexBuffer);
		d->CreateBuffer(&indexBufferDesc, &indexBufferData, &mIndexBuffer);

		delete[] vertices;
		delete[] indices;



	}





}

Mesh::~Mesh(){
}

void Mesh::Set(ID3D11DeviceContext* c) {


	UINT stride = sizeof(VERTEXPNU);
	UINT offset = 0;

	c->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
	c->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	c->IASetInputLayout(mInputLayout.Get());

	c->DrawIndexed(numOfIndices, 0, 0);

}
