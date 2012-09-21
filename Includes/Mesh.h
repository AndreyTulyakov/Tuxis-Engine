/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include <istream>

#include "TextureAtlas.h"
#include "Drawable2D.h"
#include "EngineBase.h"
#include "TextureRegion.h"
#include "Shader.h"
#include "Light.h"

namespace Tuxis
{
	struct CBStruct
	{
		XMMATRIX FinalMatrix;
	};
	
	
	#define TEXTURES_COUNT 8
	
	class TUXIS_DECLSPEC Mesh : public Drawable2D
	{
	
	    private:
			CBStruct mCBStruct;
	
			int VertexCount;
			Tuxis::Vertex::VertexTest *vertices;	
			// Half sprite size
			TextureAtlas *mTexture;
		
		public:
			Light *mLight;
	
	        Mesh();
	
			void SetTextureAuto(TextureAtlas *pTexture);
	
			bool LoadModel(const WCHAR* filename);
	
			void SetShader(Shader *pShader);
	
			void Update();
	        void Draw();
			void Release();
	
	
	};
}





