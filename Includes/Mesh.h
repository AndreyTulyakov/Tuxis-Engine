/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

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

	class TUXIS_DECLSPEC Mesh : public Drawable2D
	{
		struct CBStruct
		{
			XMMATRIX FinalMatrix;
		};
	
	    private:
			CBStruct mCBStruct;
	
			int VertexCount;
			Tuxis::Vertex::VertexTest *vertices;
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





