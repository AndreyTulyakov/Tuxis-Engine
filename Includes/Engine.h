/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Engine class
Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_

#include "Camera.h"
#include "EngineDescription.h"
#include "Graphics.h"
#include "DefaultShaderBase.h"
#include "Window.h"
#include "Log.h"


namespace Tuxis
{

	class TUXIS_DECLSPEC Engine
	{
	private:
		Window *mWindow;
		Camera *mCamera2D;
		Camera *mCamera3D;
		DefaultShaderBase mDefaultShaderBase;

		// Graphics
		Graphics			*mGraphics;
		ID3D11Device		*Device;			
		ID3D11DeviceContext	*Context;

		// Main scene
		Scene *mRootScene;

		static Engine* Me;


	public:

		static Engine* GetInstance();

		Engine();
		~Engine();

		void Initialize(EngineDescription pEngineOptions);
		void Release();

		void SetRootScene(Scene* pScene);


		//static Graphics*		GetGraphics();
		static Camera*			GetActive2DCamera();
		static Camera*			GetActive3DCamera();
		static ID3D11Device*	GetDevice();
		static ID3D11DeviceContext*	GetContext();

		Window* GetWindow();

		void SetActiveCamera2D(Camera *inCamera);
		void SetActiveCamera3D(Camera *inCamera);

		void SetScene(Scene *pScene);

		void Update();
		void Draw();
	};


}