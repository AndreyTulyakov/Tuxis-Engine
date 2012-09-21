/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include <d3d11.h>
#include "Log.h"
#include "Engine.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC RenderTexture
	{
	public:
		RenderTexture();
	
		bool Initialize(int, int);
		void Release();
	
		ID3D11RenderTargetView** GetRenderTargetView();
		ID3D11ShaderResourceView* GetShaderResourceView();
	
	private:
		ID3D11Texture2D* m_renderTargetTexture;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11ShaderResourceView* m_shaderResourceView;
	};
}
