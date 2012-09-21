#include "stdafx.h"
#include "Engine.h"



namespace Tuxis
{
	Engine*	Engine::Me = NULL;
	
	
	Engine* Engine::GetInstance()
	{
		if(Me)
		{
			return Me;
		}
		else
		{
			Log::Error("Engine::GetMe() - engine not created");
		}
		return NULL;
	}
	
	
	Window* Engine::GetWindow()
	{
		return mWindow;
	}
	
	
	Engine::Engine() 
	{

		mGraphics	= nullptr;
		Context		= nullptr;
		Device		= nullptr;	
		mWindow		= nullptr;
		mCamera2D	= nullptr;
		mCamera3D	= nullptr;
		mRootScene	= nullptr;


		if(Me) Log::Error("Engine::Engine: Engine already exist");
		Me=this;
	}
	

	void Engine::Initialize(EngineDescription pEngineOptions)
	{
		mWindow		= pEngineOptions._Window;
		mCamera2D	= pEngineOptions._Camera2D;
		mCamera3D	= pEngineOptions._Camera3D;

		if(!pEngineOptions.Test())
			Log::Error("Engine::Initialize: EngineDescription Failed");

		// Graphics block
		
		mGraphics = new Graphics();
		mGraphics->Initialize( mWindow, pEngineOptions._Windowed, pEngineOptions._VSync);
		Context=mGraphics->GetContext();
		Device=mGraphics->GetDevice();

		mDefaultShaderBase.LoadShaders();

		Log::Success("Engine::Initialized.");
	}
	
	Camera* Engine::GetActive2DCamera()
	{
		if(Me)
		{
			if(Me->mCamera2D)
			{
				return Me->mCamera2D;
			}
			else
			{
				Log::Error("Engine::GetActive2DCamera - Camera2D is null");
			}
		}
		else
			Log::Error("Engine::GetActive2DCamera - engine is not created.");

		return NULL;
	}
	

	
	Camera* Engine::GetActive3DCamera()
	{
		if(Me)
		{
			if(Me->mCamera3D)
			{
				return Me->mCamera3D;
			}
			else
			{
				Log::Error("Engine::GetActive3DCamera - Camera3D is null");
			}
		}
		else
			Log::Error("Engine::GetActive3DCamera - engine is not created.");

		return NULL;
	}
	

	Graphics* Engine::GetGraphics()
	{
		if(Me)
		{
			if(Me->mGraphics)
			{
				if(Me->mGraphics->isReady())
					return Me->mGraphics;
				else
					Log::Error("Engine::GetGraphics - Graphics not initialized.");
			}
			else
			{
				Log::Error("Engine::GetGraphics - Graphics is null");
			}
		}
		else
			Log::Error("Engine::GetGraphics - engine is not created.");

		return NULL;
	}
	

	ID3D11Device* Engine::GetDevice()
	{
		if(Me)
		{
			if(Me->Device)
			{
				return Me->Device;
			}
			else
			{
				Log::Error("Engine::GetDevice - Device is null");
			}
		}
		else
			Log::Error("Engine::GetDevice - engine is not created.");

		return NULL;
	}



	ID3D11DeviceContext* Engine::GetContext()
	{
		if(Me)
		{
			if(Me->Context)
			{
				return Me->Context;
			}
			else
			{
				Log::Error("Engine::GetContext - Context is null");
			}
		}
		else
			Log::Error("Engine::GetContext - engine is not created.");

		return NULL;
	}


	
	void Engine::SetActiveCamera2D(Camera *inCamera)
	{
		mCamera2D=inCamera;
	}
	
	
	void Engine::SetActiveCamera3D(Camera *inCamera)
	{
		mCamera3D=inCamera;
	}
	
	
	void Engine::Draw()
	{
		if(mCamera2D)
			mCamera2D->Update();
	
		if(mCamera3D)
			mCamera3D->Update();
	
		if(mRootScene)
			mRootScene->Draw();
	}
	
	
	void Engine::Update()
	{
		if(mRootScene)
			mRootScene->Update();
	}
	
	
	void Engine::Release()
	{
		
		mDefaultShaderBase.ReleaseShaders();

		_RELEASE_DELETE(mGraphics);

		Context		= nullptr;
		Device		= nullptr;	
		mWindow		= nullptr;
		mCamera2D	= nullptr;
		mCamera3D	= nullptr;
		mRootScene = nullptr;

		Log::Success("Engine - Released");
	}

	Engine::~Engine()
	{	
		Me=nullptr;
	}

	void Engine::SetRootScene( Scene* pScene )
	{
		mRootScene=pScene;
	}

}