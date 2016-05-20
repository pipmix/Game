#pragma once
#include "Common.h"
#include "Timer.h"
#include "Model.h"
#include "LightList.h"
#include "Camera.h"




class Game{
public:


			Game					(HWND& h, HINSTANCE& hI);
			~Game					();

	void	CreateDeviceResources	();
	void	CreateWindowResources	();
	void	Update					();
	void	Draw					();
	void	ClearRenderTargets		();


private:

	ComPtr<ID3D11Device>			mDevice;
	ComPtr<ID3D11DeviceContext>		mContext;
	ComPtr<ID3D11RenderTargetView>	mBackBuffer;
	ComPtr<ID3D11DepthStencilView>	mZBuffer;
	ComPtr<IDXGISwapChain>			mSwapChain;
	ComPtr<ID3D11DepthStencilState> mDepthStencilState;
	ComPtr<ID3D11DepthStencilState> mDepthStencilStateOff;
	ComPtr<ID3D11SamplerState>		mSamplerStateLinear;
	ComPtr<ID3D11SamplerState>		mSamplerStatePoint;

	CBUFFER							mCBufferData;
	CBBUFFER_AMBIENT				mCB_AmbientData;

	
	ComPtr<ID3D11Buffer>			mCBuffer;
	ComPtr<ID3D11Buffer>			mCB_AmbientBuffer;

	LONG mWindowWidth, mWidowHeight;
	float m_AspectRaio;

	HWND m_Window;
	HINSTANCE m_HInstance;

	float time = 0;

	bool mCameraUpToDate = false;


	Model* models[5];
	int numberOfModels;

	bool flag1 = false;
	bool m_visualize = true;

	XMFLOAT4X4 mCameraMatrix;


	LightList* m_LightList;
	Camera* m_Camera;
	Timer* m_Timer;
	Input* m_Input;
	Player* m_Player;

	

};

