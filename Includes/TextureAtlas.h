/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Texture Atlas class
Required: <d3d11.h> <d3dx11.h> <d3dx10.h> <xnamath.h>
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include <d3dx11.h>
#include "Log.h"
#include "Engine.h"



namespace Tuxis
{

	class TUXIS_DECLSPEC TextureAtlas
	{	
	public:

		TextureAtlas();
		~TextureAtlas();

		void Release();

		int GetWidth();
		int GetHeight();

		ID3D11SamplerState** GetSamplerState();
		ID3D11ShaderResourceView** GetShaderResourceView();

		void SetShaderResourceView(ID3D11ShaderResourceView* pRes);

		void SetWidth(int pWidth);
		void SetHeight(int pHeight);



		bool LoadFromFile(const WCHAR* ImageName);
		void CreateSampler();


	private:	
		void LoadInfo(const WCHAR* ImageName);

		ID3D11ShaderResourceView *Resource;
		ID3D11SamplerState* SamplerState;
		D3DX11_IMAGE_LOAD_INFO ImageInfo;
		HRESULT hr;
	};

}