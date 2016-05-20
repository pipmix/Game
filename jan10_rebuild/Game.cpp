#include "Game.h"

Game::Game(HWND& hw, HINSTANCE& hI): m_Window(hw), m_HInstance(hI) {
	

	CreateDeviceResources();
	CreateWindowResources();


	models[0] = new Model(mDevice.Get(), mContext.Get(), L"wallTopFloor", 1);
	models[1] = new Model(mDevice.Get(), mContext.Get(), L"wallGround", 1);
	models[2] = new Model(mDevice.Get(), mContext.Get(), L"wall01", 1);
	models[3] = new Model(mDevice.Get(), mContext.Get(), L"tiledBrick", 1);
	models[4] = new Model(mDevice.Get(), mContext.Get(), L"arrows", 1);
	numberOfModels = 5;
	time = 0.0f;


	
	m_Timer = new Timer;
	m_Input = new Input(hw, hI);
	m_Player = new Player(m_Input);
	m_Player->SetPosition(XMFLOAT3{ -15.0f, 10.0f , 15.0f });
	m_Camera = new Camera(hw, m_Player, m_Input);

	//m_LightList = new LightList(mDevice.Get(), mContext.Get());

}
Game::~Game() { }

void Game::CreateDeviceResources() {

	RECT rc = { 0,0,0,0 };
	GetClientRect(m_Window, &rc);
	mWindowWidth = rc.right;
	mWidowHeight = rc.bottom;
	m_AspectRaio = static_cast<float>(mWindowWidth) / static_cast<float>(mWidowHeight) ;

		

	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = mWindowWidth;
	swapChainDesc.BufferDesc.Height = mWidowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_Window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &swapChainDesc, mSwapChain.GetAddressOf(), mDevice.GetAddressOf(), NULL, mContext.GetAddressOf());


	// CREATE LINEAR AND POINT SAMPLERS
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = 3.0f;
	samplerDesc.MipLODBias = 0.0f;

	mDevice->CreateSamplerState(&samplerDesc, &mSamplerStateLinear);

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	mDevice->CreateSamplerState(&samplerDesc, &mSamplerStatePoint);

	// CREATE CONSTANT BUFFERS
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(CBUFFER), D3D11_BIND_CONSTANT_BUFFER);
	mDevice->CreateBuffer(&constantBufferDesc, nullptr, &mCBuffer);

	CD3D11_BUFFER_DESC constantBufferDesc2(sizeof(CBBUFFER_AMBIENT), D3D11_BIND_CONSTANT_BUFFER);
	mDevice->CreateBuffer(&constantBufferDesc2, nullptr, &mCB_AmbientBuffer);

}




void Game::CreateWindowResources() {

	// BACKBUFFER
	ComPtr<ID3D11Texture2D> backBuffer;
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mBackBuffer.ReleaseAndGetAddressOf());

	//ZBUFFER
	D3D11_TEXTURE2D_DESC zBufferDesc = { 0 };
	zBufferDesc.Width = mWindowWidth;
	zBufferDesc.Height = mWidowHeight;
	zBufferDesc.ArraySize = 1;
	zBufferDesc.MipLevels = 1;
	zBufferDesc.SampleDesc.Count = 1;
	zBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	zBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ComPtr<ID3D11Texture2D> zbuffertexture;
	mDevice->CreateTexture2D(&zBufferDesc, nullptr, &zbuffertexture);

	//ZBUFFER VIEW 
	D3D11_DEPTH_STENCIL_VIEW_DESC stencilViewDesc;
	ZeroMemory(&stencilViewDesc, sizeof(stencilViewDesc));
	stencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	mDevice->CreateDepthStencilView(zbuffertexture.Get(), &stencilViewDesc, &mZBuffer);

	//ZBUFFER STATE 
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf());




}

void Game::Update() {

	m_Timer->Update();
	m_Input->Update(m_Timer->GetDelta());


	
	m_Player->Update(m_Timer->GetDelta());

	m_Camera->Update(m_Timer->GetDelta());

	for (int i = 0; i < numberOfModels; i++)models[i]->Update();

}

void Game::Draw() {

	ClearRenderTargets();
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mContext->VSSetConstantBuffers(0, 1, mCBuffer.GetAddressOf());
	mContext->PSSetConstantBuffers(0, 1, mCB_AmbientBuffer.GetAddressOf());

	mContext->PSSetSamplers(0, 1, mSamplerStateLinear.GetAddressOf());


	for (int i = 0; i < numberOfModels; i++) {

		XMMATRIX worldMatrix = XMLoadFloat4x4(models[i]->GetWorldMatrix());


		XMMATRIX finalMatrix = worldMatrix * XMLoadFloat4x4(&m_Camera->GetCameraScreenMatrix());


		CBUFFER cb;
		XMStoreFloat4x4(&cb.s_FinalMatrix, finalMatrix);
		XMStoreFloat4x4(&cb.s_WorldMatrix, worldMatrix);

		mContext->UpdateSubresource(mCBuffer.Get(), 0, 0, &cb, 0, 0);


		CBBUFFER_AMBIENT cbAmb;
		cbAmb.vAmbientLower = { 0.5f, 0.5f, 2.5f };
		cbAmb.vAmbientRange = { 1.0f, 0.5f, 0.5f };



		mContext->UpdateSubresource(mCB_AmbientBuffer.Get(), 0, 0, &cbAmb, 0, 0);
		models[i]->Draw();

	}

	mSwapChain->Present(1, 0);
}


void Game::ClearRenderTargets() {

	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };




	mContext->ClearRenderTargetView(mBackBuffer.Get(), fill);
	mContext->ClearDepthStencilView(mZBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mContext->OMSetRenderTargets(1, mBackBuffer.GetAddressOf(), mZBuffer.Get());
	mContext->OMSetDepthStencilState(mDepthStencilState.Get(), 0);



	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(mWindowWidth), static_cast<float>(mWidowHeight));
	mContext->RSSetViewports(1, &viewport);

}