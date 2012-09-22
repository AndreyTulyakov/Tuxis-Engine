#include "stdafx.h"
#include "SpriteGroup.h"

namespace Tuxis
{
	SpriteGroup::SpriteGroup()
	{
		mChanged=true;
		InitDrawable();
	
		SpriteBase=0;
		SpriteCount=0;
	
		mTextureRegion=0;
	
		AbsTexCoord(0.0f,0.0f,1.0f,1.0f);
		HalfTexSize(0,0);
	
		VB_Stride = sizeof( Tuxis::Vertex::SpriteGroupVertex );
		VB_Offset = 0;
	
		mShader = DefaultShaderBase::Instance()->mShaderSpriteGroup;
		CreateConstantBuffer(sizeof(XMMATRIX),D3D11_USAGE_DEFAULT);
	}
	
	SpriteGroup::~SpriteGroup()
	{
		Release();
	}
	
	
	void SpriteGroup::Create(int pSpriteCount,TextureRegion *pTextureRegion)
	{
		if(SpriteCount==0)
		{
			if(pSpriteCount>0 && pSpriteCount<=10000)
			{
				SpriteCount=pSpriteCount;
				SpriteBase=new BasicSprite[SpriteCount];
				vertices=new Tuxis::Vertex::SpriteGroupVertex[6*SpriteCount];
	
				// Vertex Buffer Creating
				D3D11_BUFFER_DESC VertexBufferDesc;
				ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
				VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
				VertexBufferDesc.ByteWidth = sizeof( Tuxis::Vertex::SpriteGroupVertex ) * 6 * SpriteCount;
				VertexBufferDesc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
				VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
				D3D11_SUBRESOURCE_DATA VertexBufferData;
				ZeroMemory( &VertexBufferData, sizeof( D3D11_SUBRESOURCE_DATA ) );
				VertexBufferData.pSysMem = vertices;
				VertexBufferData.SysMemPitch             = sizeof( vertices );
				VertexBufferData.SysMemSlicePitch        = sizeof( vertices );
	
				hr = Engine::GetDevice()->CreateBuffer( &VertexBufferDesc, &VertexBufferData, &VertexBuffer );
				if(FAILED(hr))	
					Log::Error("TxSpriteGroup:CreateBuffer vertexBufferDesc");
			}
			else
				Log::Error("TxSpriteGroup::Create - strange count size (only >0 & <10001)");
		}
		else
			Log::Error("TxSpriteGroup::Create - already created");
	
	
		if(pTextureRegion)
		{
			mTextureRegion=pTextureRegion;
	
			HalfTexSize.x=( (mTextureRegion->Region.x2-mTextureRegion->Region.x1) )/2.0f;
			HalfTexSize.y=( (mTextureRegion->Region.y2-mTextureRegion->Region.y1) )/2.0f;

			AbsTexCoord.x1 = mTextureRegion->Region.x1 / mTextureRegion->mTexture->GetWidth();
			AbsTexCoord.x2 = mTextureRegion->Region.x2 / mTextureRegion->mTexture->GetWidth();
			AbsTexCoord.y1 = mTextureRegion->Region.y1 / mTextureRegion->mTexture->GetHeight();
			AbsTexCoord.y2 = mTextureRegion->Region.y2 / mTextureRegion->mTexture->GetHeight();
		}
		else
			Log::Error("SpriteGroup::Create - null region");
		
		mChanged=true;
	}
	
	
	void SpriteGroup::Draw()
	{
		if(!mVisible) return;
	
		if(!mTextureRegion)
			Log::Error("Sprite::Draw - Not set Texture Region.");
	
		Graphics::Instance()->DisableStencilBuffer();
	
		int RealDrawCount=SpriteCount;
	
		if(mChanged)
		{
			// Calculate matrices
			XMMATRIX WorldMatrix = CalculateWorldMatrix();
			XMMATRIX FinalMatrix = WorldMatrix*(Engine::GetInstance()->GetActive2DCamera()->GetFinalMatrix() );
			FinalMatrix = XMMatrixTranspose( FinalMatrix );
			Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &FinalMatrix, 0, 0 );
	
			// Modify the vertex buffer
			D3D11_MAPPED_SUBRESOURCE mapResource;
			Engine::GetContext()->Map( VertexBuffer, 0,D3D11_MAP_WRITE_DISCARD, 0, &mapResource );
			{
				Tuxis::Vertex::SpriteGroupVertex* pTempVertex=(Tuxis::Vertex::SpriteGroupVertex*)mapResource.pData;
	
				int BufferCounter=0;
	
				for(int i=0;i<SpriteCount*6;i+=6)
				{
					if(SpriteBase[i/6].Visible==false)
					{
						RealDrawCount--;
						continue;
					}
	
					float xPos			=SpriteBase[i/6].Position.x;
					float yPos			=SpriteBase[i/6].Position.y;
					float scale			=SpriteBase[i/6].Scale;
					float rotation		=SpriteBase[i/6].Rotation;
					XMFLOAT4 color		=SpriteBase[i/6].Color;
	
					// Vertex Position.
	
					// First triangle
					pTempVertex[BufferCounter + 0].Position = XMFLOAT3( -HalfTexSize.x,  -HalfTexSize.y, 0.0f );
					pTempVertex[BufferCounter + 1].Position = XMFLOAT3(  HalfTexSize.x,   HalfTexSize.y, 0.0f );
					pTempVertex[BufferCounter + 2].Position = XMFLOAT3( -HalfTexSize.x,   HalfTexSize.y, 0.0f );
	
					// Second triangle
					pTempVertex[BufferCounter + 3].Position = XMFLOAT3(  HalfTexSize.x,  -HalfTexSize.y, 0.0f );
					pTempVertex[BufferCounter + 4].Position = XMFLOAT3(  HalfTexSize.x,   HalfTexSize.y, 0.0f );
					pTempVertex[BufferCounter + 5].Position = XMFLOAT3( -HalfTexSize.x,  -HalfTexSize.y, 0.0f );
	
	
					// Center pos
					// First triangle
					pTempVertex[BufferCounter + 0].Rotation = XMFLOAT3( xPos,  yPos, rotation );
					pTempVertex[BufferCounter + 1].Rotation = XMFLOAT3( xPos,  yPos, rotation );
					pTempVertex[BufferCounter + 2].Rotation = XMFLOAT3( xPos,  yPos, rotation );
	
					// Second triangle
					pTempVertex[BufferCounter + 3].Rotation = XMFLOAT3( xPos,  yPos, rotation );
					pTempVertex[BufferCounter + 4].Rotation = XMFLOAT3( xPos,  yPos, rotation );
					pTempVertex[BufferCounter + 5].Rotation = XMFLOAT3( xPos,  yPos, rotation );
	

					// Texture Position.
	
					// First triangle
					pTempVertex[BufferCounter + 0].TexCoord = XMFLOAT2( AbsTexCoord.x1, AbsTexCoord.y1 );
					pTempVertex[BufferCounter + 1].TexCoord = XMFLOAT2( AbsTexCoord.x2, AbsTexCoord.y2 );
					pTempVertex[BufferCounter + 2].TexCoord = XMFLOAT2( AbsTexCoord.x1, AbsTexCoord.y2 );
	
					// Second triangle
					pTempVertex[BufferCounter + 3].TexCoord = XMFLOAT2( AbsTexCoord.x2, AbsTexCoord.y1 );
					pTempVertex[BufferCounter + 4].TexCoord = XMFLOAT2( AbsTexCoord.x2, AbsTexCoord.y2 );
					pTempVertex[BufferCounter + 5].TexCoord = XMFLOAT2( AbsTexCoord.x1, AbsTexCoord.y1 );
	
					// Set color modulation
					pTempVertex[BufferCounter + 0].Color = color;
					pTempVertex[BufferCounter + 1].Color = color;
					pTempVertex[BufferCounter + 2].Color = color;
					pTempVertex[BufferCounter + 3].Color = color;
					pTempVertex[BufferCounter + 4].Color = color;
					pTempVertex[BufferCounter + 5].Color = color;

					// Set scale
					pTempVertex[BufferCounter + 0].Scale = scale;
					pTempVertex[BufferCounter + 1].Scale = scale;
					pTempVertex[BufferCounter + 2].Scale = scale;
					pTempVertex[BufferCounter + 3].Scale = scale;
					pTempVertex[BufferCounter + 4].Scale = scale;
					pTempVertex[BufferCounter + 5].Scale = scale;
	
					BufferCounter+=6;
				}
			}
			Engine::GetContext()->Unmap( VertexBuffer,0);
		}
	
		
		// Context configuration
		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &VB_Stride, &VB_Offset );
		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );
		
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );
		Engine::GetContext()->PSSetShaderResources( 0, 1, mTextureRegion->mTexture->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mTextureRegion->mTexture->GetSamplerState() );
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
		// Drawing RealDrawCount
		Engine::GetContext()->Draw(6*RealDrawCount,0);
		mChanged=false;
	}
	
	void SpriteGroup::Update()
	{
		
	}
	
	
	
	
	void SpriteGroup::SetPosition2D( float pX, float pY ,bool centered=false)
	{
		mChanged=true;
		if(centered)
			TranslationMatrix = XMMatrixTranslation( pX, pY, 0.0f );		
		else
			TranslationMatrix = XMMatrixTranslation( pX+HalfTexSize.x, pY+HalfTexSize.y, 0.0f );
	}
	
	void SpriteGroup::Clear()
	{
		mChanged=true;
		SpriteCount=0;
		if(SpriteBase)
			delete[] SpriteBase;
		SpriteBase=0;
	}
	
	BasicSprite* SpriteGroup::GetSprite(int i)
	{
		mChanged=true;
	
		if(SpriteBase)
			if( i<SpriteCount && i>=0 )
				return &SpriteBase[i];
			else
			{
				Log::Error("SpriteGroup::GetSprite - parameter is out of range");
				return 0;
			}
		else
		{
			Log::Error("SpriteGroup::GetSprite - group is empty");
			return 0;
		}
	}
	
	void SpriteGroup::Release()
	{
		mShader = 0;
		mChanged=true;
		Clear();
		ReleaseDrawable();
	}
}