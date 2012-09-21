/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "TextureAtlas.h"
#include "EngineBase.h"
#include "Types.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC TextureRegion
	{
	public:
		TextureRegion();
		TextureRegion(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2);
	
		void SetRegion(float x1,float y1,float x2,float y2);
		void SetTextureAtlas(TextureAtlas *pTextureAtlas);
		void SetFullAtlasRegion(TextureAtlas *pTextureAtlas);
	
		TextureAtlas *mTexture;
		floatRect Region;
	};
}