#include "stdafx.h"
#include "TiledTextureRegion.h"

namespace Tuxis
{
	TiledTextureRegion::TiledTextureRegion()
	{
		mTexture=0;
	}
	
	TiledTextureRegion::~TiledTextureRegion()
	{
		Release();
	}
	
	
	TiledTextureRegion::TiledTextureRegion(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2)
	{
		SetTextureAtlas(pTextureAtlas,x1,y1,x2,y2);
	}
	
	void TiledTextureRegion::SetTextureAtlas(TextureAtlas *pTextureAtlas,float x1,float y1,float x2,float y2)
	{
		if(mTexture)
		{
			if(mTexture==pTextureAtlas)
			{
				floatRect *temp=new floatRect( x1, y1, x2, y2 );
				TileCoordinates.push_back(temp);
			}
			else
				Log::Warning("TiledTextureRegion::SetManualTiling: using different textures");
		}
		else
		{
			mTexture=pTextureAtlas;
		}
	}
	
	
	int TiledTextureRegion::GetRegionCount()
	{
		return TileCoordinates.size();
	}
	
	void TiledTextureRegion::AddRegion(float x1,float y1,float x2,float y2)
	{
		if(mTexture)
		{
			floatRect *temp=new floatRect( x1, y1, x2, y2 );
			TileCoordinates.push_back(temp);
		}
		else
		{
			Log::Warning("TiledTextureRegion::AddTileCordinates: Set Atlas at first");
		}
	}
	
	void TiledTextureRegion::Release()
	{
		for(int i=0; i<(int)TileCoordinates.size(); i++)
			delete TileCoordinates.at(i);
		TileCoordinates.clear();
	}
	
	
	void TiledTextureRegion::SetAutoTiling(TextureAtlas *pTextureAtlas,float TileWidth, float TileHeight)
	{
		mTexture=pTextureAtlas;
	
		int TileCountX = (int)(mTexture->GetWidth() / TileWidth);
		int TileCountY = (int)(mTexture->GetHeight() / TileHeight);
	
		for(int y=0; y<TileCountY; y++)
		{
			for(int x=0; x<TileCountX; x++)
			{
				floatRect *temp=new floatRect( x*TileWidth, y*TileHeight, (x+1)*TileWidth, (y+1)*TileHeight );
				TileCoordinates.push_back(temp);
			}
		}

	}
}