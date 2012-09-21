/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "Drawable2D.h"
#include "TextureAtlas.h"
#include "EngineBase.h"
#include "TextureRegion.h"
#include "DefaultShaderBase.h"




namespace Tuxis
{

	class TUXIS_DECLSPEC Sprite : public Drawable2D
	{
	private:
		TextureAtlas *mTexture;
		Vertex::vtxSprite vertices[4];

		floatRect AbsTexCoord;
		float HTW,HTH;
		CBSprite mCBValue;

		void Initialize();

	public:

		Sprite();
		

		void SetPosition2D( float tX, float tY ,bool centered);
		void SetTextureRegion(TextureRegion *pTextureRegion);
		void SetTextureAtlas(TextureAtlas *pTexture);
		void SetShader(Shader *pShader);

		void Draw();
		void Update();
		void Release();
	};

}

