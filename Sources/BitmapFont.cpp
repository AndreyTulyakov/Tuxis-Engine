#include "stdafx.h"
#include "BitmapFont.h"

namespace Tuxis
{
	sCharset* BitmapFont::GetCharset()
	{
		return &Charset;
	}

	TextureAtlas *BitmapFont::GetTextureAtlas()
	{
		return &mTexture;
	}


	void BitmapFont::LoadCharMap( const WCHAR* FileName )
	{
		fstream Stream;
		Stream.open( FileName, ios::in | ios::binary );

		if(Stream.fail())
		{
			Log::Error("BitmapFont::Load: font not found");
		}

		string Line;
		string Read, Key, Value;

		std::size_t i;

		while( !Stream.eof() )
		{
			std::stringstream LineStream;
			std::getline( Stream, Line );
			LineStream << Line;

			//read the line's type
			LineStream >> Read;

			if( Read == "common" )
			{
				//this holds common data
				while( !LineStream.eof() )
				{
					std::stringstream Converter;
					LineStream >> Read;
					i = Read.find( '=' );
					Key = Read.substr( 0, i );
					Value = Read.substr( i + 1 );

					//assign the correct value
					Converter << Value;
					if( Key == "lineHeight" )
					{
						Converter >> Charset.LineHeight;
					}
					else if( Key == "base" )
					{
						Converter >> Charset.Base;
					}
					else if( Key == "scaleW" )
					{
						Converter >> Charset.Width;
					}
					else if( Key == "scaleH" )
					{
						Converter >> Charset.Height;
					}
					else if( Key == "pages" )
					{
						Converter >> Charset.Pages;
					}
				}
			}
			else 
				if( Read == "page" )
				{
					
					//this holds common data
					while( !LineStream.eof() )
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find( '=' );
						Key = Read.substr( 0, i );
						Value = Read.substr( i + 1 );

						//assign the correct value
						Converter << Value;

						if( Key == "file" )
						{
							std::wstring wStr;
							std::string aStr;
							Converter >> aStr;
							if(!aStr.empty())
							{
								wStr.assign(aStr.begin()+1,aStr.end()-1);
							}

							TextureName.append(wStr);
							
							break;
						}
					}
				}
				else 
					if( Read == "char" )
					{
						//this is data for a specific char
						unsigned short CharID = 0;

						while( !LineStream.eof() )
						{
							std::stringstream Converter;
							LineStream >> Read;
							i = Read.find( '=' );
							Key = Read.substr( 0, i );
							Value = Read.substr( i + 1 );

							//assign the correct value
							Converter << Value;
							if( Key == "id" )
							{
								Converter >> CharID;
							}
							else if( Key == "x" )
							{
								Converter >> Charset.Chars[CharID].x;
							}
							else if( Key == "y" )
							{
								Converter >> Charset.Chars[CharID].y;
							}
							else if( Key == "width" )
							{
								Converter >> Charset.Chars[CharID].Width;
							}
							else if( Key == "height" )
							{
								Converter >> Charset.Chars[CharID].Height;
							}
							else if( Key == "xoffset" )
							{
								Converter >> Charset.Chars[CharID].XOffset;
							}
							else if( Key == "yoffset" )
							{
								Converter >> Charset.Chars[CharID].YOffset;
							}
							else if( Key == "xadvance" )
							{
								Converter >> Charset.Chars[CharID].XAdvance;
							}
							else if( Key == "page" )
							{
								Converter >> Charset.Chars[CharID].Page;
							}
						}
					}
		}

	}



	void BitmapFont::Load( const WCHAR* FontName )
	{
		// Extract path for texture  || FontPath.find_last_of(L'/') == -1
		wstring FontPath = FontName;

		int state=0;

		// if finded slash
		if(FontPath.find_last_of(L'\\') != -1)
		{
			TextureName = FontPath.substr(0,FontPath.find_last_of(L'\\')+1);
		}
		else
		{
			if(FontPath.find_last_of(L'/') != -1)
				TextureName = FontPath.substr(0,FontPath.find_last_of(L'/')+1);
			else
				TextureName = L"";
		}

		LoadCharMap( FontName );
		mTexture.LoadFromFile(TextureName.c_str());
	}



	void BitmapFont::Release()
	{

		mTexture.Release();
	}
}