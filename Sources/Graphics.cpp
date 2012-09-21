#include "stdafx.h"
#include "Graphics.h"

namespace Tuxis
{
	bool Graphics::mReady=false;
	Graphics* Graphics::mInstance=nullptr;

	Graphics::Graphics()
	{
		
		if(mInstance == nullptr)
		{
			mInstance = this;
		}
		else
			Log::Warning("Graphics::Graphics object already created.");

		ZeroInit();
		

		pDSState=0;
		FeatureLevel=D3D_FEATURE_LEVEL_10_0;

		mClearColor(0.5f,0.5f,0.9f,1.0f);
	
		mReady = false;
	}

	bool Graphics::isReady()
	{
		return mReady;
	}

	Graphics::~Graphics()
	{
		mInstance = nullptr;
		mReady = false;	
	}

	Graphics* Graphics::Instance()
	{
		if(mInstance == nullptr)
		{
			Log::Error("Graphics::Instance: you must create object before.");
			return nullptr;
		}
		else
			return mInstance;
	}

	
	
	bool Graphics::Initialize( Window* pWindow, bool windowed,bool vsync )
	{
		WindowHandler = pWindow->GetHWND();
		Width		= pWindow->GetWidth();
		Height		= pWindow->GetHeight();
	
		Windowed	= windowed;
		VSync		= vsync;
		Depth		= 32;

		hr = 0;
		FPS = 0;
	
		mReady=InitializeDirectX();
		return mReady;
	}
	
	ID3D11Device* Graphics::GetDevice()
	{ 
		return Device; 
	}	
	
	ID3D11DeviceContext* Graphics::GetContext()		
	{ 
		return Context;
	}
	
	int Graphics::GetWidth()
	{
		return Width;
	}
	
	int Graphics::GetHeight()
	{
		return Height;
	}
	
	void Graphics::Clear()
	{
		Context->ClearRenderTargetView( *CurrentRenderTarget, (float*)&mClearColor );
		if(isDepthStencilView)
			Context->ClearDepthStencilView(isDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);	
	}

	void Graphics::SetClearColor( Color prColor )
	{
		mClearColor=prColor;
	}
	
	void Graphics::SetRenderTarget(ID3D11RenderTargetView** pRenderTarget)
	{
		if(pRenderTarget==0)
			CurrentRenderTarget=&BackBuffer;
		else
			CurrentRenderTarget=pRenderTarget;
	
		Context->OMSetRenderTargets( 1, CurrentRenderTarget, isDepthStencilView);
	}

	void Graphics::SetWireframeMode(bool pEnable)
	{
		if(RasterState && WireFrameState)
		{
			if(pEnable)
			{
				Context->RSSetState( WireFrameState );
			}
			else
			{
				Context->RSSetState( RasterState );
			}
		}	
	}	

	ID3D11DepthStencilView* Graphics::GetDepthStencilView()
	{
		return DepthStencilView;
	}	
	
	void Graphics::EnableStencilBuffer()
	{
		isDepthStencilView=DepthStencilView;
		Context->OMSetRenderTargets( 1, CurrentRenderTarget, isDepthStencilView );
	}
	
	void Graphics::DisableStencilBuffer()
	{
		isDepthStencilView=0;
		Context->OMSetRenderTargets( 1, CurrentRenderTarget, isDepthStencilView );
	}
	
	
	
	bool Graphics::InitializeDirectX()
	{ 
		CreateDeviceAndSwapChain();
		CreateBackBuffer();

		CreateWireframeState();
		CreateBlendState();
		CreateRasterState();

		CreateDepthStencilBuffer();
		Context->OMSetRenderTargets( 1, &BackBuffer, isDepthStencilView );
		SetViewport( 0.0f, 0.0f, (float)Width, (float)Height );
	
		return true;
	}

	void Graphics::CreateDepthStencilBuffer()
	{
		
		ID3D11Texture2D* DepthStencilBuffer = NULL;
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = Width;
		descDepth.Height = Height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		Device->CreateTexture2D( &descDepth, NULL, &DepthStencilBuffer );

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		// Create the depth stencil view
		hr = Device->CreateDepthStencilView( DepthStencilBuffer, 0, &DepthStencilView ); 
		if( FAILED(hr) )	Log::Error( "Graphics::CreateDepthStencilBuffer()" );
		isDepthStencilView=DepthStencilView;

		DepthStencilBuffer->Release();
	}
	
	
	void Graphics::CreateDeviceAndSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory( &scd, sizeof( DXGI_SWAP_CHAIN_DESC ) );
		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = WindowHandler;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = Windowed;           
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		
		int DEVICE_CREATION_MODE;

#ifdef _DEBUG
		DEVICE_CREATION_MODE=D3D11_CREATE_DEVICE_DEBUG;
#else
		DEVICE_CREATION_MODE=D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif

		hr = D3D11CreateDeviceAndSwapChain( NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			DEVICE_CREATION_MODE,
			&FeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&scd,
			&SwapChain,
			&Device,
			NULL,
			&Context );


	
		if( FAILED(hr) )	Log::Error( "Graphics::CreateDeviceAndSwapChain()" );		
	}
	
	
	void Graphics::SetViewport( float pX, float pY, float pWidth, float pHeight )
	{
		ViewPort.Width = pWidth;
		ViewPort.Height = pHeight;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = pX;
		ViewPort.TopLeftY = pY;
		Context->RSSetViewports( 1, &ViewPort );
	}
	
	
	void Graphics::CreateBackBuffer()
	{
		ID3D11Texture2D *pBackBuffer;
	
		hr = SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID * )&pBackBuffer );
		if( FAILED(hr) )	Log::Error( "Graphics::CreateBackBuffer: SwapChain->GetBuffer" );
	
		hr = Device->CreateRenderTargetView( pBackBuffer, NULL, &BackBuffer );
		if( FAILED(hr) )	Log::Error( "Graphics::CreateBackBuffer: Device->CreateRenderTargetView" );
	
		_RELEASE(pBackBuffer)
	
		CurrentRenderTarget = &BackBuffer;
	}
	
	
	void Graphics::CreateBlendState()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory( &blendDesc, sizeof( blendDesc ) );
	
		blendDesc.RenderTarget[0].BlendEnable		= TRUE;
		blendDesc.RenderTarget[0].BlendOp			= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].BlendOpAlpha		= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend			= D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend			= D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].SrcBlendAlpha		= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha	= D3D11_BLEND_ONE;//D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		
		
		hr = Device->CreateBlendState( &blendDesc, &BlendState );
		if( FAILED(hr) )	Log::Error( "Graphics::CreateBlendState: Device->CreateBlendState" );
	
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		Context->OMSetBlendState( BlendState, blendFactor, 0xFFFFFFFF );
	}
	
	
	void Graphics::CreateWireframeState()
	{
		D3D11_RASTERIZER_DESC RasterStateDesc;
		ZeroMemory(&RasterStateDesc, sizeof(D3D11_RASTERIZER_DESC));
	
		RasterStateDesc.FillMode = D3D11_FILL_WIREFRAME;
		RasterStateDesc.CullMode = D3D11_CULL_NONE;
	
		hr = Device->CreateRasterizerState(&RasterStateDesc, &WireFrameState);
		if( FAILED(hr) )	Log::Error( "Graphics::CreateWireframeState: Device->CreateRasterizerState" );
	}
	
	
	void Graphics::CreateRasterState()
	{
		D3D11_RASTERIZER_DESC RasterStateDesc;
		RasterStateDesc.FillMode = D3D11_FILL_SOLID;
		RasterStateDesc.CullMode = D3D11_CULL_BACK;
		
		RasterStateDesc.FrontCounterClockwise = false;
			
		RasterStateDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
		RasterStateDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
		RasterStateDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		RasterStateDesc.DepthClipEnable = true;
			
		RasterStateDesc.ScissorEnable = false;
		RasterStateDesc.MultisampleEnable = false; //true;
		RasterStateDesc.AntialiasedLineEnable = false; //true;
		
		hr = Device->CreateRasterizerState( &RasterStateDesc , &RasterState );
		if( FAILED(hr) )	Log::Error( "Graphics::CreateRasterState: Device->CreateRasterizerState" );
	
		Context->RSSetState( RasterState );
	}
	
	int Graphics::GetFPS()
	{
		return FPS;
	}
	
	
	void Graphics::Flip()
	{
		hr = SwapChain->Present( VSync, 0 );
		CalculateFrameRate();
		if( FAILED( hr ) ) Log::Error( "SwapChain->Present( 0, 0 )" );


#ifdef _DEBUG
		ID3D11ShaderResourceView *const pSRV[1] = {NULL};
		Context->PSSetShaderResources(0, 1, pSRV);
#endif
		
	}
	
	
	void  Graphics::CalculateFrameRate()
	{
		static float framesPerSecond = 0.0f;
		static float lastTime = 0.0f;		
	
		float currentTime = timeGetTime() * 0.001f;
	
		++framesPerSecond;
	
		if( currentTime - lastTime > 1.0f )
		{
			lastTime = currentTime;
			FPS = ( int )framesPerSecond;
			framesPerSecond = 0;
		}
	
	}
	

	void Graphics::ZeroInit()
	{
		Device				= 0;			
		Context				= 0;		
		SwapChain			= 0;		
		BackBuffer			= 0;
		BlendState			= 0;
		RasterState			= 0;
		WireFrameState		= 0;
		DepthStencilView	= 0;
		isDepthStencilView	= 0;
	}

	
	void  Graphics::Release()
	{
		hr = SwapChain->SetFullscreenState( FALSE, NULL );
		if( FAILED( hr ) )	Log::Error( "SwapChain->SetFullscreenState" );

		_RELEASE(BackBuffer)
		_RELEASE(DepthStencilView)
		_RELEASE(BlendState)
		_RELEASE(RasterState)
		_RELEASE(WireFrameState)
		_RELEASE(SwapChain)
		_RELEASE(Device)
		_RELEASE(Context)

		mReady=false;
	}




}
