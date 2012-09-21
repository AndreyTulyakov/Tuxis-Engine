/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Graphics class
Required: <d3d11.h> <d3dx11.h> <d3dx10.h> <xnamath.h>
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include "MMSystem.h"

#include "Log.h"
#include "Window.h"
#include "EngineBase.h"
#include "Types.h"


namespace Tuxis
{

	class TUXIS_DECLSPEC Graphics
	{
	public:



		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();



		Graphics();
		~Graphics();

		Graphics( Window* pWindow, bool windowed,bool vsync);
		bool Initialize( Window* pWindow, bool windowed,bool vsync );

		int GetWidth();
		int GetHeight();

		void SetRenderTarget(ID3D11RenderTargetView** pRenderTarget);
		void SetWireframeMode(bool pEnable);

		void EnableStencilBuffer();
		void DisableStencilBuffer();

		void SetClearColor(Color prColor);
		void Clear();


		int GetFPS();
		void Flip();
		void  CalculateFrameRate();
		void  Release();

		void SetViewport( float pX, float pY, float pWidth, float pHeight );

		ID3D11DepthStencilView* GetDepthStencilView();

		static Graphics* Instance();
		static bool isReady();

	private:
		static bool mReady;
		static Graphics* mInstance;
		Color mClearColor;

		
		void ZeroInit();
		bool  InitializeDirectX();

		void CreateDeviceAndSwapChain();
		void CreateBackBuffer();
		void CreateWireframeState();
		void CreateBlendState();
		void CreateRasterState();
		void CreateDepthStencilBuffer();


		HWND						WindowHandler;
		ID3D11Device				*Device;			
		ID3D11DeviceContext			*Context;		
		IDXGISwapChain				*SwapChain;	
		D3D_FEATURE_LEVEL			FeatureLevel;

		ID3D11BlendState			*BlendState;
		ID3D11RasterizerState		*RasterState;
		ID3D11RasterizerState		*WireFrameState;

		ID3D11RenderTargetView		*BackBuffer;
		ID3D11RenderTargetView		**CurrentRenderTarget;

		ID3D11DepthStencilView*		DepthStencilView;
		ID3D11DepthStencilView*		isDepthStencilView;
		ID3D11DepthStencilState*	pDSState;

		long hr;
		//LPCTSTR Caption;
		int Width, Height, Depth;
		bool Windowed, VSync;
		int FPS;
		D3D11_VIEWPORT ViewPort;

	};

}