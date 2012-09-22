/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "Drawable2D.h"
#include "TextureAtlas.h"
#include "EngineBase.h"
#include "TiledTextureRegion.h"
#include "Engine.h"
#include "DefaultShaderBase.h"



namespace Tuxis
{

	class TUXIS_DECLSPEC TiledSprite : public Drawable2D
	{
	private:
		TiledTextureRegion *mTiledTextureRegion;
		Vertex::vtxSprite vertices[4];
		CBSprite mCBValue;

		int mFrameTime,mLastTime;
		int mFrame;	
		floatRect AbsTextureCoordinate;
		float2 HalfTexSize;


	public:

		TiledSprite();

		void Animate(int pTimeMillisecond);
		int GetFrameCount();

		void SetFrame(int frame);
		void SetNextFrame();
		void SetPosition2D( float tX, float tY ,bool centered);
		void SetTiledTextureRegion(TiledTextureRegion *pTiledTextureRegion);
		void Draw();
		void Update();
		void Release();


	};


}
