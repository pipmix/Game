#pragma once

#include "Common.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"



class Texture {
public:

	Texture(wstring fileName, ID3D11Device* d, bool t);
	~Texture();

	wstring						ReturnName();
	ComPtr<ID3D11ShaderResourceView> ReturnTexture() const;

private:

	int textureSizeX;
	int textureSizeY;

	wstring	textureName;

	ComPtr<ID3D11ShaderResourceView> textureResourceView;

	bool tileAble;

};