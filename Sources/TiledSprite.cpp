#include "stdafx.h"
#include "TiledSprite.h"


namespace Tuxis
{
	TiledSprite::TiledSprite()
	{
		mChanged=true;
		InitDrawable();

		mFrame=0;
		mFrameTime=0;
		mLastTime=0;
		mTiledTextureRegion=0;

		AbsTextureCoordinate(0.0f,0.0f,1.0f,1.0f);

		VB_Stride = sizeof( vertices[0] );
		VB_Offset = 0;

		D3D11_BUFFER_DESC VertexBufferDesc;
		ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
		VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;//D3D11_USAGE_DEFAULT;
		VertexBufferDesc.ByteWidth = VB_Stride * 4;
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

		mShader = DefaultShaderBase::Instance()->mShaderTiledSprite;
		CreateConstantBuffer(sizeof(CBSprite),D3D11_USAGE_DEFAULT);
	}



	void TiledSprite::SetTiledTextureRegion(TiledTextureRegion *pTiledTextureRegion)
	{
		mTiledTextureRegion=pTiledTextureRegion;

		floatRect *Region=mTiledTextureRegion->TileCoordinates.at(mFrame);

		HTW=( (Region->x2-Region->x1) )/2.0f;
		HTH=( (Region->y2-Region->y1) )/2.0f;

		AbsTextureCoordinate.x1 = Region->x1 / mTiledTextureRegion->mTexture->GetWidth();
		AbsTextureCoordinate.x2 = Region->x2 / mTiledTextureRegion->mTexture->GetWidth();
		AbsTextureCoordinate.y1 = Region->y1 / mTiledTextureRegion->mTexture->GetHeight();
		AbsTextureCoordinate.y2 = Region->y2 / mTiledTextureRegion->mTexture->GetHeight();
	}


	void TiledSprite::SetFrame(int frame)
	{
		if(frame<0) frame=0;
		if((unsigned int)frame>=mTiledTextureRegion->TileCoordinates.size()) frame=0;
		mFrame=frame;
	}

	void TiledSprite::SetNextFrame()
	{
		SetFrame(mFrame+1);
	}


	int TiledSprite::GetFrameCount()
	{
		return mTiledTextureRegion->TileCoordinates.size();
	}


	void TiledSprite::SetPosition2D( float tX, float tY ,bool centered=false)
	{
		if(centered)
			TranslationMatrix = XMMatrixTranslation( tX, tY, 0.0f );		
		else
			TranslationMatrix = XMMatrixTranslation( tX+HTW, tY+HTH, 0.0f );
	}

	void TiledSprite::Animate(int pTimeMillisecond)
	{
		if(pTimeMillisecond>0)
			mFrameTime=pTimeMillisecond;
		else
			mFrameTime=0;
	}

	void TiledSprite::Draw()
	{
		if(!mVisible) return;

		Engine::GetInstance()->GetGraphics()->DisableStencilBuffer();

		// Frame calculation
		floatRect *Region=mTiledTextureRegion->TileCoordinates.at(mFrame);

		HTW=( (Region->x2-Region->x1) )/2.0f;
		HTH=( (Region->y2-Region->y1) )/2.0f;

		AbsTextureCoordinate.x1 = Region->x1 / mTiledTextureRegion->mTexture->GetWidth();
		AbsTextureCoordinate.x2 = Region->x2 / mTiledTextureRegion->mTexture->GetWidth();
		AbsTextureCoordinate.y1 = Region->y1 / mTiledTextureRegion->mTexture->GetHeight();
		AbsTextureCoordinate.y2 = Region->y2 / mTiledTextureRegion->mTexture->GetHeight();

		// Matrix calculation
		XMMATRIX WorldMatrix = CalculateWorldMatrix();
		XMMATRIX FinalMatrix = WorldMatrix*(Engine::GetInstance()->GetActive2DCamera()->GetFinalMatrix() );

		mCBValue.FINAL_MATRIX = XMMatrixTranspose( FinalMatrix );
		mCBValue.COLOR = ColorModulation;

		D3D11_MAPPED_SUBRESOURCE mapResource;
		Engine::GetContext()->Map( VertexBuffer, 0,D3D11_MAP_WRITE_DISCARD, 0, &mapResource );
		{
			Vertex::vtxSprite* pTempVertex=(Vertex::vtxSprite*)mapResource.pData;
			pTempVertex[0].Position = XMFLOAT3(-HTW,   HTH,  0.0f);
			pTempVertex[1].Position = XMFLOAT3(-HTW,  -HTH,  0.0f);
			pTempVertex[2].Position = XMFLOAT3( HTW,   HTH,  0.0f);
			pTempVertex[3].Position = XMFLOAT3( HTW,  -HTH,  0.0f);

			pTempVertex[0].TexCoord = XMFLOAT2( AbsTextureCoordinate.x1, AbsTextureCoordinate.y2 );
			pTempVertex[1].TexCoord = XMFLOAT2( AbsTextureCoordinate.x1, AbsTextureCoordinate.y1 );
			pTempVertex[2].TexCoord = XMFLOAT2( AbsTextureCoordinate.x2, AbsTextureCoordinate.y2 );
			pTempVertex[3].TexCoord = XMFLOAT2( AbsTextureCoordinate.x2, AbsTextureCoordinate.y1 );
		}
		Engine::GetContext()->Unmap( VertexBuffer,0);


		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &VB_Stride, &VB_Offset );
		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );

		Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &mCBValue, 0, 0 );
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );
		Engine::GetContext()->PSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );

		Engine::GetContext()->PSSetShaderResources( 0, 1, mTiledTextureRegion->mTexture->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mTiledTextureRegion->mTexture->GetSamplerState() );
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

		
		Engine::GetContext()->Draw(4,0);

	}


	void TiledSprite::Update()
	{
		if(mFrameTime)
		{
			int tempTime=timeGetTime();
			if(tempTime-mLastTime>mFrameTime)
			{
				mLastTime=tempTime;
				SetNextFrame();
			}
		}
	}

	void TiledSprite::Release()
	{	
		mShader = 0;
		ReleaseDrawable();
	}
}
