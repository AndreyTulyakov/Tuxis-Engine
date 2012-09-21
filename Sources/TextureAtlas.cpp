#include "stdafx.h"
#include "TextureAtlas.h"


namespace Tuxis
{
	
	TextureAtlas::TextureAtlas()
	{
		Resource=0;
		SamplerState=0;
		ZeroMemory(&ImageInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	}
	
	TextureAtlas::~TextureAtlas()
	{
		Resource=0;
		SamplerState=0;
	}
	
	
	bool TextureAtlas::LoadFromFile( const WCHAR* ImageName )
	{
		Resource = 0;
		SamplerState = 0;

		CreateSampler();
		LoadInfo( ImageName );

		hr = D3DX11CreateShaderResourceViewFromFileW( Engine::GetDevice(), ImageName, &ImageInfo, NULL, &Resource, NULL );
		if( FAILED( hr ) )
		{
			Log::Error( "D3DX11CreateShaderResourceViewFromFile" );
		}
		return true;
	}
	
	void TextureAtlas::LoadInfo( const WCHAR* ImageName )
	{
		D3DX11_IMAGE_INFO TextureInfo;
		ZeroMemory(&TextureInfo, sizeof(D3DX11_IMAGE_INFO));

		hr = D3DX11GetImageInfoFromFileW( ImageName, NULL, &TextureInfo, NULL );
		if( FAILED( hr ) )
		{
			Log::Error( "D3DX11GetImageInfoFromFile ImageName" );
		}

		ImageInfo.Width = TextureInfo.Width;
		ImageInfo.Height = TextureInfo.Height;
		ImageInfo.Depth = TextureInfo.Depth;
		ImageInfo.FirstMipLevel = 0;
		ImageInfo.MipLevels = 1;
		ImageInfo.Usage = D3D11_USAGE_DEFAULT;
		ImageInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		ImageInfo.CpuAccessFlags = 0;
		ImageInfo.MiscFlags = 0;
		ImageInfo.Format = TextureInfo.Format;
		ImageInfo.Filter = D3DX11_FILTER_LINEAR;
		ImageInfo.MipFilter = D3DX11_FILTER_LINEAR;
	}
	


	void TextureAtlas::CreateSampler()
	{
		if(SamplerState==0)
		{
			D3D11_SAMPLER_DESC sampDesc;
			ZeroMemory( &sampDesc, sizeof( sampDesc ) );

			// Non filtering
			//sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			// Linear Filtering
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
			
			hr = Engine::GetDevice()->CreateSamplerState( &sampDesc, &SamplerState );
			if( FAILED( hr ) )
			{
				Log::Error( "CreateSamplerState" );
			}
		}
	}
	
	
	
	
	ID3D11ShaderResourceView** TextureAtlas::GetShaderResourceView()
	{
		return &Resource;
	}
	
	ID3D11SamplerState** TextureAtlas::GetSamplerState()
	{
		return &SamplerState;
	}
	
	
	void TextureAtlas::SetShaderResourceView(ID3D11ShaderResourceView* pRes)
	{
		Resource = pRes;
	}
	
	
	
	int TextureAtlas::GetWidth()
	{
		return ImageInfo.Width;
	}
	int TextureAtlas::GetHeight()
	{
		return ImageInfo.Height;
	}
	
	void TextureAtlas::SetWidth(int pWidth)
	{
		ImageInfo.Width=pWidth;
	}
	
	void TextureAtlas::SetHeight(int pHeight)
	{
		ImageInfo.Height=pHeight;
	}
	
	void TextureAtlas::Release()
	{
		_RELEASE(SamplerState);
		_RELEASE(Resource);

		ZeroMemory(&ImageInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	}
}
