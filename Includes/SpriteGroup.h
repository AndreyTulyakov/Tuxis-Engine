/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "BasicSprite.h"
#include "TextureRegion.h"
#include "Drawable2D.h"
#include "Log.h"
#include "DefaultShaderBase.h"


namespace Tuxis
{
	class TUXIS_DECLSPEC SpriteGroup : public Drawable2D
	{
	public:
		SpriteGroup();
		~SpriteGroup();
	
		void Create(int pSpriteCount,TextureRegion *pTextureRegion);
		void Clear();
		BasicSprite* GetSprite(int i);
		void SetPosition2D( float tX, float tY ,bool centered);
		void Release();
	
		void Draw();
		void Update();
	
	private:
		TextureRegion *mTextureRegion;
	
		floatRect AbsTexCoord;
	
		Tuxis::Vertex::SpriteGroupVertex *vertices;
		BasicSprite *SpriteBase;
	
		// Half sprite size
		float HTW,HTH;
	
		
		int SpriteCount;
	};
}