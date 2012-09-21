#include "stdafx.h"
#include "RenderTexture.h"


namespace Tuxis
{
	RenderTexture::RenderTexture()
	{
		m_renderTargetTexture = 0;
		m_renderTargetView = 0;
		m_shaderResourceView = 0;
	}

	
	bool RenderTexture::Initialize(int textureWidth, int textureHeight)
	{
		HRESULT result;
		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	
		// Initialize the render target texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	
		// Setup the render target texture description.
		textureDesc.Width = textureWidth;
		textureDesc.Height = textureHeight;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
	
		// Create the render target texture.
		result = Engine::GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTexture);
		if(FAILED(result))
		{
			Log::Error("RenderTextureClass::Initialize: CreateTexture2D");
		}
	
		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
	
		// Create the render target view.
		result = Engine::GetDevice()->CreateRenderTargetView(m_renderTargetTexture, &renderTargetViewDesc, &m_renderTargetView);
		if(FAILED(result))
		{
			Log::Error("RenderTextureClass::Initialize: CreateRenderTargetView");
		}
	
		// Setup the description of the shader resource view.
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
	
		// Create the shader resource view.
		result = Engine::GetDevice()->CreateShaderResourceView(m_renderTargetTexture, &shaderResourceViewDesc, &m_shaderResourceView);
		if(FAILED(result))
		{
			Log::Error("RenderTextureClass::Initialize: CreateShaderResourceView");
		}
	
		if(!m_shaderResourceView || !m_renderTargetView || !m_renderTargetTexture)
		{
			Log::Error("RenderTextureClass::Initialize: bad");
		}
	
		return true;
	}
	
	
	void RenderTexture::Release()
	{
		if(m_shaderResourceView)
		{
			//m_shaderResourceView->Release();
			m_shaderResourceView = 0;
		}


		if(m_renderTargetView)
		{
			m_renderTargetView->Release();
			m_renderTargetView = 0;
		}


		if(m_renderTargetTexture)
		{
			m_renderTargetTexture->Release();
			m_renderTargetTexture = 0;
		}
	}
	
	
	ID3D11RenderTargetView**  RenderTexture::GetRenderTargetView()
	{
		return &m_renderTargetView;
	}
	
	ID3D11ShaderResourceView* RenderTexture::GetShaderResourceView()
	{
		return m_shaderResourceView;
	}
}