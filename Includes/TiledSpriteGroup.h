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

#include "BasicSprite.h"
#include "TiledTextureRegion.h"
#include "Drawable2D.h"
#include "Log.h"
#include "DefaultShaderBase.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC TiledSpriteGroup : public Drawable2D
	{
	public:
		TiledSpriteGroup();
	
		void Create(int countSize,TiledTextureRegion *pTextureRegion);
	
		BasicSprite* GetSprite(int i);
		void SetPosition2D( float PositionX, float PositionY );
		void Release();
	
		void Animate(int pTimeMillisecond);
		void Update();
		void Draw();
	
	private:
		int mFrameTime,mLastTime;
		TiledTextureRegion *mTiledTextureRegion;
		int CountOfSprites;
	
		floatRect AbsTextureCoordinate;
		Tuxis::Vertex::SpriteGroupVertex *vertices;	
		// Half sprite size
		float HTW,HTH;
		BasicSprite *SpriteBase;
	
	
	};
}