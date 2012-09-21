#include "stdafx.h"
#include "TiledSpriteGroup.h"


namespace Tuxis
{
	TiledSpriteGroup::TiledSpriteGroup()
	{
		
		InitDrawable();
	
		CountOfSprites=0;
		SpriteBase=0;
		
		mTiledTextureRegion=0;
	
		vertices=0;
	
		HTW=0;
		HTH=0;
	
		AbsTextureCoordinate.x1 = 0.0f;
		AbsTextureCoordinate.x2 = 1.0f;
		AbsTextureCoordinate.y1 = 0.0f;
		AbsTextureCoordinate.y2 = 1.0f;
	
		VB_Stride = sizeof( Tuxis::Vertex::SpriteGroupVertex );
		VB_Offset = 0;
	
		mShader = DefaultShaderBase::Instance()->mShaderTiledSpriteGroup;
		CreateConstantBuffer(sizeof(XMMATRIX),D3D11_USAGE_DEFAULT);
	}
	
	void TiledSpriteGroup::Update()
	{
		if(mFrameTime && mTiledTextureRegion)
		{
			int tempTime=timeGetTime();
			if(tempTime-mLastTime>mFrameTime)
			{
				mLastTime=tempTime;
				int framesCount=mTiledTextureRegion->GetRegionCount();
	
				for(int i=0; i<CountOfSprites; i++)
				{
					GetSprite(i)->Frame++;
					if(GetSprite(i)->Frame>=framesCount)
					{
						GetSprite(i)->Frame=0;
					}	
				}
				
			}
		}
	}
	
	void TiledSpriteGroup::Create(int countSize,TiledTextureRegion *pTextureRegion)
	{
		mTiledTextureRegion = pTextureRegion;
	
		if(CountOfSprites==0)
		{
			if(countSize>0 && countSize<=10000)
			{
			
				CountOfSprites=countSize;
				SpriteBase=new BasicSprite[CountOfSprites];
				vertices=new Tuxis::Vertex::SpriteGroupVertex[6*CountOfSprites];
	
				// Vertex Buffer Creating
				D3D11_BUFFER_DESC VertexBufferDesc;
				ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
				VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;//D3D11_USAGE_DEFAULT;
				VertexBufferDesc.ByteWidth = sizeof( Tuxis::Vertex::SpriteGroupVertex ) * 6 * CountOfSprites;
				VertexBufferDesc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
				VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
				D3D11_SUBRESOURCE_DATA VertexBufferData;
				ZeroMemory( &VertexBufferData, sizeof( D3D11_SUBRESOURCE_DATA ) );
				VertexBufferData.pSysMem = vertices;
				VertexBufferData.SysMemPitch             = sizeof( vertices );
				VertexBufferData.SysMemSlicePitch        = sizeof( vertices );
	
	
				hr = Engine::GetDevice()->CreateBuffer( &VertexBufferDesc, &VertexBufferData, &VertexBuffer );
				if(FAILED(hr))	
					Log::Error("CreateBuffer vertexBufferDesc");
			}
			else
			{
				Log::Error("TxTiledSpriteGroup::Create - strange count size (only >0 & <10001)");
			}
		}
		else
		{
			Log::Error("TxTiledSpriteGroup::Create - already created");
		}
		
		if(!pTextureRegion)
		{
			Log::Error("TxTiledSpriteGroup::Create - null region");
		}
		
	}
	
	
	
	void TiledSpriteGroup::Draw()
	{
		if(!mVisible) return;
		
	
		if(!mTiledTextureRegion)
			Log::Error("TxTiledSpriteGroup::Draw - Not set Texture Region.");
	
		Engine::GetInstance()->GetGraphics()->DisableStencilBuffer();
	
		// Calculate matrices
		XMMATRIX WorldMatrix = CalculateWorldMatrix();
		XMMATRIX FinalMatrix = WorldMatrix*(Engine::GetInstance()->GetActive2DCamera()->GetFinalMatrix() );
		FinalMatrix = XMMatrixTranspose( FinalMatrix );
	
		int RealDrawCount=CountOfSprites;
	
	
		// Modify the vertex buffer
		D3D11_MAPPED_SUBRESOURCE mapResource;
		Engine::GetContext()->Map( VertexBuffer, 0,D3D11_MAP_WRITE_DISCARD, 0, &mapResource );
		{
			Tuxis::Vertex::SpriteGroupVertex* pTempVertex=(Tuxis::Vertex::SpriteGroupVertex*)mapResource.pData;
	
			int BufferCounter=0;
	
			for(int i=0;i<CountOfSprites*6;i+=6)
			{	
				if(SpriteBase[i/6].Visible==false)
				{
					RealDrawCount--;
					continue;
				}
	
				floatRect *Region=mTiledTextureRegion->TileCoordinates.at(SpriteBase[i/6].Frame);
	
				HTW=( (Region->x2-Region->x1) )/2.0f;
				HTH=( (Region->y2-Region->y1) )/2.0f;
	
				AbsTextureCoordinate.x1 = Region->x1 / (int)mTiledTextureRegion->mTexture->GetWidth();
				AbsTextureCoordinate.x2 = Region->x2 / (int)mTiledTextureRegion->mTexture->GetWidth();
				AbsTextureCoordinate.y1 = Region->y1 / (int)mTiledTextureRegion->mTexture->GetHeight();
				AbsTextureCoordinate.y2 = Region->y2 / (int)mTiledTextureRegion->mTexture->GetHeight();
	
				float xPos=SpriteBase[i/6].Position.x;
				float yPos=SpriteBase[i/6].Position.y;
	
				// Vertex Position.
				pTempVertex[BufferCounter + 0].Position = XMFLOAT3( -HTW,  -HTH, 0.0f );
				pTempVertex[BufferCounter + 1].Position = XMFLOAT3(  HTW,   HTH, 0.0f );
				pTempVertex[BufferCounter + 2].Position = XMFLOAT3( -HTW,   HTH, 0.0f );
	
				pTempVertex[BufferCounter + 3].Position = XMFLOAT3(  HTW,  -HTH, 0.0f );
				pTempVertex[BufferCounter + 4].Position = XMFLOAT3(  HTW,   HTH, 0.0f );
				pTempVertex[BufferCounter + 5].Position = XMFLOAT3( -HTW,  -HTH, 0.0f );
	
				// Texture Position.
				pTempVertex[BufferCounter + 0].TexCoord = XMFLOAT2( AbsTextureCoordinate.x1, AbsTextureCoordinate.y1 );
				pTempVertex[BufferCounter + 1].TexCoord = XMFLOAT2( AbsTextureCoordinate.x2, AbsTextureCoordinate.y2 );
				pTempVertex[BufferCounter + 2].TexCoord = XMFLOAT2( AbsTextureCoordinate.x1, AbsTextureCoordinate.y2 );
	
				pTempVertex[BufferCounter + 3].TexCoord = XMFLOAT2( AbsTextureCoordinate.x2, AbsTextureCoordinate.y1 );
				pTempVertex[BufferCounter + 4].TexCoord = XMFLOAT2( AbsTextureCoordinate.x2, AbsTextureCoordinate.y2 );
				pTempVertex[BufferCounter + 5].TexCoord = XMFLOAT2( AbsTextureCoordinate.x1, AbsTextureCoordinate.y1 );
	
	
				XMFLOAT4 CurrentColor=SpriteBase[i/6].Color;
	
				pTempVertex[BufferCounter + 0].Color = CurrentColor;
				pTempVertex[BufferCounter + 1].Color = CurrentColor;
				pTempVertex[BufferCounter + 2].Color = CurrentColor;
				pTempVertex[BufferCounter + 3].Color = CurrentColor;
				pTempVertex[BufferCounter + 4].Color = CurrentColor;
				pTempVertex[BufferCounter + 5].Color = CurrentColor;
	
				float Rotation=SpriteBase[i/6].Rotation;
	
				pTempVertex[BufferCounter + 0].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
				pTempVertex[BufferCounter + 1].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
				pTempVertex[BufferCounter + 2].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
				pTempVertex[BufferCounter + 3].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
				pTempVertex[BufferCounter + 4].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
				pTempVertex[BufferCounter + 5].Rotation = XMFLOAT3( xPos ,  yPos , Rotation );
	
				float Scale=SpriteBase[i/6].Scale;
	
				pTempVertex[BufferCounter + 0].Scale = Scale;
				pTempVertex[BufferCounter + 1].Scale = Scale;
				pTempVertex[BufferCounter + 2].Scale = Scale;
				pTempVertex[BufferCounter + 3].Scale = Scale;
				pTempVertex[BufferCounter + 4].Scale = Scale;
				pTempVertex[BufferCounter + 5].Scale = Scale;
	
				BufferCounter+=6;
			}
		}
		Engine::GetContext()->Unmap( VertexBuffer,0);
	
		//FinalMatrix=XMMatrixTranspose(FinalMatrix);
	
		// Context configuration
		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &VB_Stride, &VB_Offset );
		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );

		Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &FinalMatrix, 0, 0 );
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );

		Engine::GetContext()->PSSetShaderResources( 0, 1, mTiledTextureRegion->mTexture->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mTiledTextureRegion->mTexture->GetSamplerState() );
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
		// Drawing
		Engine::GetContext()->Draw(6*RealDrawCount,0);
	}
	
	
	void TiledSpriteGroup::SetPosition2D( float PositionX, float PositionY )
	{
		TranslationMatrix = XMMatrixTranslation(PositionX, PositionY, 0.0f );			
	}
	
	
	void TiledSpriteGroup::Animate(int pTimeMillisecond)
	{
		if(pTimeMillisecond>0)
			mFrameTime=pTimeMillisecond;
		else
			mFrameTime=0;
	}
	
	BasicSprite* TiledSpriteGroup::GetSprite(int i)
	{
		if(SpriteBase)
			if( i>=CountOfSprites || i<0 )
			{
				Log::Error("SpriteGroup::GetSprite - parameter is out of range");
				return 0;
			}
			else
			{
				return &SpriteBase[i];
			}
		else
		{
			Log::Error("SpriteGroup::GetSprite - group is empty");
			return 0;
		}
	}
	
	void TiledSpriteGroup::Release()
	{

		CountOfSprites=0;
		if(SpriteBase)
			delete[] SpriteBase;
		SpriteBase=0;
		
		mShader = 0;
		ReleaseDrawable();
	}
}