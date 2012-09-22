#include "stdafx.h"
#include "Sprite.h"


namespace Tuxis
{
	Sprite::Sprite()
	{
		mChanged=true;
		InitDrawable();
	
		AbsTexCoord(0.0f,0.0f,1.0f,1.0f);
		HalfTexSize(0,0);

		VB_Stride = sizeof(vertices[0]);
		VB_Offset = 0;

		Initialize();
	}

	void Sprite::Initialize()
	{
		// Vertex Buffer Creating
		D3D11_BUFFER_DESC VertexBufferDesc;
		ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
		VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		VertexBufferDesc.ByteWidth = VB_Stride * 4;
		VertexBufferDesc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA VertexBufferData;
		ZeroMemory( &VertexBufferData, sizeof( D3D11_SUBRESOURCE_DATA ) );
		VertexBufferData.pSysMem			= vertices;
		VertexBufferData.SysMemPitch		= sizeof( vertices );
		VertexBufferData.SysMemSlicePitch	= sizeof( vertices );


		hr = Engine::GetDevice()->CreateBuffer( &VertexBufferDesc, &VertexBufferData, &VertexBuffer );
		if(FAILED(hr))	
			Log::Error("TxSprite::TxSprite: CreateBuffer VertexBuffer");

		mShader = DefaultShaderBase::Instance()->mShaderSprite;
		CreateConstantBuffer(sizeof(CBSprite),D3D11_USAGE_DEFAULT);
	}
	
	void Sprite::SetShader(Shader *pShader)
	{
		mChanged=true;
		mShader=pShader;
	}
	
	
	void Sprite::SetTextureRegion(TextureRegion *pTextureRegion)
	{
		mChanged=true;
		mTexture=pTextureRegion->mTexture;
	
		HalfTexSize.x=( (pTextureRegion->Region.x2-pTextureRegion->Region.x1) )/2.0f;
		HalfTexSize.y=( (pTextureRegion->Region.y2-pTextureRegion->Region.y1) )/2.0f;
		
		AbsTexCoord.x1 = pTextureRegion->Region.x1 / pTextureRegion->mTexture->GetWidth();
		AbsTexCoord.x2 = pTextureRegion->Region.x2 / pTextureRegion->mTexture->GetWidth();
		AbsTexCoord.y1 = pTextureRegion->Region.y1 / pTextureRegion->mTexture->GetHeight();
		AbsTexCoord.y2 = pTextureRegion->Region.y2 / pTextureRegion->mTexture->GetHeight();
	}
	
	void Sprite::SetTextureAtlas(TextureAtlas *pTexture)
	{
		mChanged=true;
		mTexture=pTexture;
	
		HalfTexSize.x=pTexture->GetWidth() / 2.0f;
		HalfTexSize.y=pTexture->GetHeight() / 2.0f;
	
		AbsTexCoord.x1 = 0.0f;
		AbsTexCoord.x2 = 1.0f;
		AbsTexCoord.y1 = 0.0f;
		AbsTexCoord.y2 = 1.0f;
	}
	
	void Sprite::SetPosition2D( float pX, float pY ,bool centered=false)
	{
		mChanged=true;
	
		if(centered)
			TranslationMatrix = XMMatrixTranslation( pX, pY, 0.0f );		
		else
			TranslationMatrix = XMMatrixTranslation( pX+HalfTexSize.x, pY+HalfTexSize.y, 0.0f );
	}
	
	void Sprite::Draw()
	{
		
		if(!mVisible) return;
		
		if(!mTexture)
			Log::Error("Sprite::Draw - Not set Texture.");
		if(!mShader)
			Log::Error("Sprite::Draw - Not set Shader.");
	
		if(mChanged)
		{
			Log::Warning("Sprite::Class - Is changed between Update-Draw.");
			Update();
		}
		
		Graphics::Instance()->DisableStencilBuffer();
	
		// Context configuration
		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &VB_Stride, &VB_Offset );
		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );	
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );
		Engine::GetContext()->PSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );	
		Engine::GetContext()->PSSetShaderResources( 0, 1, mTexture->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mTexture->GetSamplerState() );
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	
		// Drawing
		Engine::GetContext()->Draw(4,0);
	}


	
	void Sprite::Update()
	{	

		if(mChanged)
		{
			// Update Vertex Buffer
			D3D11_MAPPED_SUBRESOURCE mapResource;
			Engine::GetContext()->Map( VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource );
			{
				Vertex::vtxSprite* pTempVertex=(Vertex::vtxSprite*)mapResource.pData;
	
				pTempVertex[0].Position = XMFLOAT3(-HalfTexSize.x,   HalfTexSize.y,  0.0f);
				pTempVertex[1].Position = XMFLOAT3(-HalfTexSize.x,  -HalfTexSize.y,  0.0f);
				pTempVertex[2].Position = XMFLOAT3( HalfTexSize.x,   HalfTexSize.y,  0.0f);
				pTempVertex[3].Position = XMFLOAT3( HalfTexSize.x,  -HalfTexSize.y,  0.0f);
	
				pTempVertex[0].TexCoord = XMFLOAT2( AbsTexCoord.x1, AbsTexCoord.y2 );
				pTempVertex[1].TexCoord = XMFLOAT2( AbsTexCoord.x1, AbsTexCoord.y1 );
				pTempVertex[2].TexCoord = XMFLOAT2( AbsTexCoord.x2, AbsTexCoord.y2 );
				pTempVertex[3].TexCoord = XMFLOAT2( AbsTexCoord.x2, AbsTexCoord.y1 );

			}
			Engine::GetContext()->Unmap( VertexBuffer,0);
		
			// Calculate matrices
			XMMATRIX WorldMatrix = CalculateWorldMatrix();
			XMMATRIX FinalMatrix = WorldMatrix*(Engine::GetInstance()->GetActive2DCamera()->GetFinalMatrix() );

			mCBValue.FINAL_MATRIX = XMMatrixTranspose( FinalMatrix );
			mCBValue.COLOR = ColorModulation;
	
			// Update Constant buffer
			Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &mCBValue, 0, 0 );
	
			mChanged=false;
		}
	}
	
	
	void Sprite::Release()
	{	
		mShader = 0;
		ReleaseDrawable();
	}

}
