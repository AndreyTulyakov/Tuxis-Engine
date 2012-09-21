/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"


#include <fstream>
#include <sstream>
using namespace std;

#include "EngineBase.h"
#include "TextureAtlas.h"

namespace Tuxis
{


	struct CharDescriptor
	{
		//clean 16 bytes
		short int x, y;
		short int Width, Height;
		short int XOffset, YOffset;
		short int XAdvance;
		short int Page;

		CharDescriptor()
		{
			x=0;
			y=0;
			Width=0;
			Height=0;
			XOffset=0;
			YOffset=0;
			XAdvance=0;
			Page=0;
		}
	};

	struct sCharset
	{
		short int LineHeight;
		short int Base;
		short int Width, Height;
		short int Pages;
		CharDescriptor Chars[2048];
	};





	class TUXIS_DECLSPEC BitmapFont
	{
	public:
	
		
		void Load( const WCHAR* FontName );
	
		TextureAtlas* GetTextureAtlas();
		sCharset* GetCharset();
	
		void Release();
	
		TextureAtlas mTexture;
		sCharset Charset;
	
	private:
		wstring TextureName;
		void LoadCharMap( const WCHAR* FileName );
	
	};
}