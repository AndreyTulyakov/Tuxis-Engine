/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Text drawable container
===============================================================================
*/

#pragma once
#include "_DllExport.h"


#define  _XM_NO_INTRINSICS_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "TextureAtlas.h"
#include "Drawable2D.h"
#include "EngineBase.h"
#include "SceneObject.h"
#include "BitmapFont.h"
#include "DefaultShaderBase.h"


namespace Tuxis
{
	#define TEXT_MAX_CHARS 512
	
	class TUXIS_DECLSPEC Text : public Drawable2D
	{
	public:
	
		Text();
		~Text();
	
		
		void Release();
		void Update();
		void Draw();
		void SetFont(BitmapFont* pFont);
		void SetRotate( float tR );
		void SetText(const WCHAR* parText);
		void SetPosition(float xpos, float ypos);

		void SetHorizontalAlign(HorizontalAlign hAlign);
		void SetVerticalAlign(VerticalAlign vAlign);

		void SetMaxLineCount(int count);
		void SetLineSpacing(float space);
	
	private:
		void Initialize();
		int MaxLineCount;
		BitmapFont *mFont;
		Tuxis::Vertex::SpriteVertex vertices[6*TEXT_MAX_CHARS];
		XMFLOAT2 Position;

		HorizontalAlign hAlign;
		VerticalAlign vAlign;

		float mLineSpacing;

		std::vector<wstring> SavedStrings;

		// Allignment offset's position
		float hAlignOffset;
		float vAlignOffset;

		void CalculateHorizontalAlignOffset(int LineNum);
		void CalculateVerticalAlignOffset();
		void WriteStringToConstantBuffer(Vertex::SpriteVertex* pTempVertex,int prOffset,wstring prString,int LineNum);
		void DrawVertexBuffer(int prVertexCount);
		
	};
}