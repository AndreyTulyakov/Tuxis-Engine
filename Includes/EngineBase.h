/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Base class
Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_

#include <d3dx11.h>
#include <xnamath.h>
#include <string>
using namespace std;


#define _RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define _RELEASE_DELETE(p)	{ if(p){(p)->Release(); delete (p); (p)=nullptr;} }

namespace Tuxis
{
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


#pragma once

#include <string>
	using namespace std;

	/*
	** Common math constants
	*/
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#ifndef M_PI
#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f
#endif







	extern TUXIS_DECLSPEC HRESULT hr;

	namespace ShaderLayouts
	{
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC SpriteLayout[];
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC StandartLayout[];
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC SpriteGroupLayout[];
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC TiledSpriteGroupLayout[];
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC PrimitiveLayout[];
		extern TUXIS_DECLSPEC D3D11_INPUT_ELEMENT_DESC TestLayout[];
	}



	namespace Path
	{
		extern TUXIS_DECLSPEC wstring  DEFAULT_SHADERS;
	}

	// Sprite constant buffer value
	struct CBSprite
	{
		CBSprite()
		{
			COLOR	= XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );	
		}

		XMMATRIX FINAL_MATRIX;
		XMFLOAT4 COLOR;
	};


	namespace Vertex
	{
		struct vtxSprite
		{
			vtxSprite()
			{
				Position	=XMFLOAT3( 0.0f, 0.0f, 0.0f );
				TexCoord	=XMFLOAT2( 0.0f, 0.0f );

			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;
		};

		struct SpriteVertex
		{
			SpriteVertex()
			{
				Position	=XMFLOAT3( 0.0f, 0.0f, 0.0f );
				TexCoord	=XMFLOAT2( 0.0f, 0.0f );
				Color		=XMFLOAT4( 0.0f, 0.0f, 0.0f, 0.0f );
			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;
			XMFLOAT4 Color;

		};

		struct TiledSpriteVertex
		{
			TiledSpriteVertex()
			{
				Position = XMFLOAT3( 0.0f, 0.0f, 0.0f );
				TexCoord = XMFLOAT2( 0.0f, 0.0f );	
			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;

		};


		struct SpriteGroupVertex
		{
			SpriteGroupVertex()
			{
				Position	= XMFLOAT3( 0.0f, 0.0f, 0.0f );
				Rotation	= XMFLOAT3( 0.0f, 0.0f, 0.0f );
				Scale		= 1.0f;
				TexCoord	= XMFLOAT2( 0.0f, 0.0f );
				Color		= XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f );
			}

			XMFLOAT3 Position;
			XMFLOAT3 Rotation;
			float Scale;
			XMFLOAT2 TexCoord;
			XMFLOAT4 Color;

		};

		struct PrimitiveVertex
		{
			PrimitiveVertex()
			{
				Position	=XMFLOAT3( 0.0f, 0.0f, 0.0f );
				Color		=XMFLOAT4( 0.0f, 0.0f, 0.0f, 0.0f );
			}

			XMFLOAT3 Position;
			XMFLOAT4 Color;

		};

		struct VertexTest
		{
			XMFLOAT3 Position;
			XMFLOAT2 Texture;
		};
	}




	/*
	===============================================================================
	Functions
	===============================================================================
	*/
	TUXIS_DECLSPEC const char*  IntToString(int val);
	TUXIS_DECLSPEC const char*  FloatToString(float val);

	TUXIS_DECLSPEC const wchar_t* IntToWString(int val);
	TUXIS_DECLSPEC const wchar_t* FloatToWString(float val);


	typedef 
		enum HorizontalAlign
	{	
		HLEFT,
		HCENTER,
		HRIGHT,
	} 	HorizontalAlign;


	typedef 
		enum VerticalAlign
	{	
		VTOP,
		VCENTER,
		VBOTTOM
	} 	VerticalAlign;



}