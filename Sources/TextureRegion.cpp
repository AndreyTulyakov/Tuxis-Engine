#include "stdafx.h"
#include "TextureRegion.h"

namespace Tuxis
{
	TextureRegion::TextureRegion()
	{
		mTexture=0;
	}
	
	TextureRegion::TextureRegion(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2)
	{
		mTexture=pTextureAtlas;
		Region(x1,y1,x2,y2);
	
		if(!pTextureAtlas)
			Log::Warning("TxTextureRegion::TxTextureRegion: Texture Atlas - null");
	}
	
	
	void TextureRegion::SetRegion(float x1,float y1,float x2,float y2)
	{
		Region(x1,y1,x2,y2);
	}
	
	void TextureRegion::SetTextureAtlas(TextureAtlas *pTextureAtlas)
	{
		mTexture=pTextureAtlas;
	}
	
	void TextureRegion::SetFullAtlasRegion(TextureAtlas *pTextureAtlas)
	{
		if(pTextureAtlas)
		{
			mTexture=pTextureAtlas;
			Region.x1=0;
			Region.y1=0;
			Region.x2=(float)mTexture->GetWidth();
			Region.y2=(float)mTexture->GetHeight();
		}
		else
			Log::Warning("TxTextureRegion::SetFullAtlasRegion: Texture Atlas - null");
	}
}