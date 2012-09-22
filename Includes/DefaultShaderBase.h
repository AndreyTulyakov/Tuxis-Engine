/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Default shader base. (Mini-Manager)
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "EngineBase.h"
#include "Log.h"
#include "Shader.h"


namespace Tuxis
{
	class TUXIS_DECLSPEC DefaultShaderBase
	{
	private:
		static DefaultShaderBase* mInstance;
		static bool Loaded;

	public:
		DefaultShaderBase();
		~DefaultShaderBase();

		void LoadShaders();
		void ReleaseShaders();

		static DefaultShaderBase* Instance();

		// Shaders
		Shader *mShaderSprite;
		Shader *mShaderSpriteGroup;
		Shader *mShaderText;
		Shader *mShaderTiledSprite;
		Shader *mShaderTiledSpriteGroup;
	};
}