/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_

#include "TextureAtlas.h"
#include "EngineBase.h"
#include "Log.h"
#include "Types.h"
#include "vector"

namespace Tuxis
{
	class TUXIS_DECLSPEC TiledTextureRegion
	{
	public:
		TiledTextureRegion();
		~TiledTextureRegion();
		TiledTextureRegion(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2);
		
		void SetAutoTiling(TextureAtlas *pTextureAtlas,float TileWidth, float TileHeight);
		void SetTextureAtlas(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2);
		void AddRegion(float x1,float y1,float x2,float y2);
	
		int GetRegionCount();
	
		void Release();
	
		vector<floatRect*> TileCoordinates;
		TextureAtlas *mTexture;
	
	};
}