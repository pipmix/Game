#include "Texture.h"

Texture::Texture(wstring n, ID3D11Device* d, bool t) : textureName(n), tileAble(t) {

	wstring s = gPath + gTexturePath + textureName + L".dds";
	//CreateWICTextureFromFile(d, nullptr, s.c_str(), nullptr, &textureResourceView, 0);


	CreateDDSTextureFromFile(d, s.c_str(), NULL, &textureResourceView, NULL);

}


Texture::~Texture() {
	

}

ComPtr<ID3D11ShaderResourceView> Texture::ReturnTexture() const {
	return textureResourceView;

}

wstring Texture::ReturnName() {
	return textureName;
}

