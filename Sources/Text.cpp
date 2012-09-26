#include "stdafx.h"
#include "Text.h"


namespace Tuxis
{
	Text::Text()
	{
		mChanged=true;
		mFont=nullptr;
		VB_Stride = sizeof( Tuxis::Vertex::SpriteVertex );
		VB_Offset = 0;	
	
		InitDrawable();
	
		MaxLineCount = 10;
		mLineSpacing = 28;

		hAlign = HLEFT;
		vAlign = VTOP;
	
		Position.x=0;
		Position.y=0;

		hAlignOffset=0.0f;
		vAlignOffset=0.0f;

		Initialize();
	}
	
	Text::~Text()
	{
		Release();
	}

	void Text::Initialize()
	{
		mShader = DefaultShaderBase::Instance()->mShaderText;
		CreateConstantBuffer(sizeof(XMMATRIX),D3D11_USAGE_DEFAULT);
		SavedStrings.clear();
	}
	
	void Text::Update()
	{
	
	}
	
	void Text::SetFont(BitmapFont* pFont)
	{
		mChanged=true;
		mFont=pFont;
		mLineSpacing = mFont->GetCharset()->LineHeight;

		D3D11_BUFFER_DESC VertexBufferDesc;
		ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
		VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		VertexBufferDesc.ByteWidth = sizeof( Tuxis::Vertex::SpriteVertex ) *6*TEXT_MAX_CHARS;
		VertexBufferDesc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
		D3D11_SUBRESOURCE_DATA VertexBufferData;
		ZeroMemory( &VertexBufferData, sizeof( D3D11_SUBRESOURCE_DATA ) );
		VertexBufferData.pSysMem = vertices;
		VertexBufferData.SysMemPitch             = sizeof( vertices );
		VertexBufferData.SysMemSlicePitch        = sizeof( vertices );
	
		hr = Engine::GetDevice()->CreateBuffer( &VertexBufferDesc, &VertexBufferData, &VertexBuffer );
		if(FAILED(hr))	Log::Error("CreateBuffer vertexBufferDesc");
	
		
	}
	
	void Text::SetText(const WCHAR* parText)
	{
		wstring inText = parText;
		SavedStrings.clear();
		
		if(!inText.empty())
		{
			int s=0,e=0,l=0;

			while(e!=string::npos)
			{
				e=inText.find(L'\n',e+1);

				if(e==string::npos)
				{
					l = inText.size()-s;
					SavedStrings.push_back(inText.substr(s,l));
				}
				else
				{
					l = (e-s); 
					SavedStrings.push_back(inText.substr(s,l));
					s=e+1;
				}
			}
		}
		

		mChanged=true;
	}
	
	void Text::SetPosition(float xpos, float ypos)
	{
		mChanged=true;

		Position.x=xpos;
		Position.y=ypos;
	}
	
	void Text::SetHorizontalAlign(HorizontalAlign hAlign)
	{
		mChanged=true;
		this->hAlign=hAlign;
	}


	void Text::SetVerticalAlign( VerticalAlign vAlign )
	{
		mChanged=true;
		this->vAlign=vAlign;
	}


	void Text::CalculateHorizontalAlignOffset(int LineNum)
	{
		if(mFont==nullptr)
		{
			Log::Error("Text class: you must ::SetFont(...) before.");
			return;
		}
		sCharset* mCharset=mFont->GetCharset();

		// Allignment offset calculations
		hAlignOffset=0.0f;
		int token; // Symbol

		int strLength;
		if(!SavedStrings.empty())
		{
			strLength = SavedStrings.at(LineNum).length();

			for( int i = 0; i < strLength; i++ )
			{
				token = ( int )SavedStrings.at(LineNum).at( i );
				hAlignOffset += ( float )mCharset->Chars[token].Width;
			}

		}
		else
		{
			strLength = 0;
		}


		
		switch(hAlign)
		{
		case HLEFT:
			hAlignOffset=0;
			break;

		case HCENTER:
			hAlignOffset=-hAlignOffset/2.0f;
			break;

		case HRIGHT:
			hAlignOffset=-hAlignOffset;
			break;

		}

	
	}

	void Text::CalculateVerticalAlignOffset()
	{
		if(mFont==nullptr)
		{
			Log::Error("Text class: you must ::SetFont(...) before.");
			return;
		}
		sCharset* mCharset=mFont->GetCharset();
		float vSize= (float)((int)SavedStrings.size()*(int)mCharset->LineHeight);

		switch(vAlign)
		{
		case VTOP:
			vAlignOffset = 0;
			break;

		case VCENTER:
			vAlignOffset = -(vSize/2.0f);
			break;

		case VBOTTOM:
			vAlignOffset = -vSize;
			break;

		}

	}



	
	void Text::Draw()
	{

		if(!mVisible) return;
	
		if(mFont)
		{	
			
			CalculateVerticalAlignOffset();
			int DataSize=0;

			// String parser
			
			


			// Vertex Buffer Modification
			D3D11_MAPPED_SUBRESOURCE mapResource;
			hr = Engine::GetContext()->Map( VertexBuffer, 0,D3D11_MAP_WRITE_DISCARD, 0, &mapResource );
			if(FAILED(hr))	
				Log::Error("Context->Map");
			{
				Tuxis::Vertex::SpriteVertex* pTempVertex=(Tuxis::Vertex::SpriteVertex*)mapResource.pData;

				// Loop by text lines
				for(int i=0;i<(int)SavedStrings.size();i++)
				{
					CalculateHorizontalAlignOffset(i);
					WriteStringToConstantBuffer(pTempVertex,DataSize,SavedStrings.at(i),i);
					DataSize += SavedStrings.at(i).size();
				}
				
				

				
			}
			Engine::GetContext()->Unmap( VertexBuffer,0);
			TranslationMatrix = XMMatrixTranslation( Position.x, Position.y, 0.0f );	
	
		

			DrawVertexBuffer(6 * DataSize);
		}
	}



	
	
	void Text::Release()
	{
		mShader = 0;
		ReleaseDrawable();
	}


	void Text::SetMaxLineCount( int count )
	{
		if(count>0) 
			MaxLineCount = count;
		else
			throw L"Text::SetLineMaxCount: invalid argument";
	}

	void Text::SetLineSpacing( float space )
	{
		mLineSpacing = space;
	}

	void Text::WriteStringToConstantBuffer(Vertex::SpriteVertex* pTempVertex,int prOffset,wstring prString,int LineNum)
	{
		TextureAtlas *mTexture=mFont->GetTextureAtlas();
		float TexW = ( float )mTexture->GetWidth();
		float TexH = ( float )mTexture->GetHeight();

		sCharset* mCharset=mFont->GetCharset();
		
		int token;
		int index;

		float xOffset= 0.0f, xsOffset= 0.0f, yOffset, ysOffset;

		for( int i = 0; i < (int)prString.length(); i++ )
		{
			token = ( int )prString.at( i );

			yOffset = ( float )mCharset->Chars[token].YOffset;
			xsOffset = xOffset+hAlignOffset;
			ysOffset = yOffset+vAlignOffset+LineNum*mLineSpacing;

			index=(prOffset+i)*6;

			// Vertex Position.
			{
				// First triangle
				pTempVertex[index + 0].Position 
					= XMFLOAT3( xsOffset, ysOffset + ( float )mCharset->Chars[token].Height,  0.0f );

				pTempVertex[index + 1].Position 
					= XMFLOAT3( xsOffset, ysOffset, 0.0f );

				pTempVertex[index + 2].Position 
					= XMFLOAT3( xsOffset + ( float )mCharset->Chars[token].Width, ysOffset,  0.0f );

				// Second triangle
				pTempVertex[index + 3].Position 
					= XMFLOAT3( xsOffset, ysOffset + ( float )mCharset->Chars[token].Height,  0.0f );

				pTempVertex[index + 4].Position 
					= XMFLOAT3( xsOffset + ( float )mCharset->Chars[token].Width, ysOffset,  0.0f );

				pTempVertex[index + 5].Position 
					= XMFLOAT3( xsOffset + ( float )mCharset->Chars[token].Width, ysOffset + ( float )mCharset->Chars[token].Height,  0.0f );
			}

			// Texture Position.
			{
				// First triangle
				pTempVertex[index + 0].TexCoord =
					XMFLOAT2( ( float )mCharset->Chars[token].x / TexW, ( float )( mCharset->Chars[token].y + mCharset->Chars[token].Height ) / TexH );
				pTempVertex[index + 1].TexCoord =
					XMFLOAT2( ( float )mCharset->Chars[token].x / TexW, ( float )mCharset->Chars[token].y / TexH );
				pTempVertex[index + 2].TexCoord =
					XMFLOAT2( ( float )( mCharset->Chars[token].x + mCharset->Chars[token].Width )	/ TexW, ( float )( mCharset->Chars[token].y ) / TexH );

				// Second triangle
				pTempVertex[index + 3].TexCoord =
					XMFLOAT2( ( float )mCharset->Chars[token].x / TexW, ( float )( mCharset->Chars[token].y + mCharset->Chars[token].Height ) / TexH );
				pTempVertex[index + 4].TexCoord =
					XMFLOAT2( ( float )( mCharset->Chars[token].x + mCharset->Chars[token].Width )	/ TexW, ( float )( mCharset->Chars[token].y ) / TexH );
				pTempVertex[index + 5].TexCoord =
					XMFLOAT2( ( float )( mCharset->Chars[token].x + mCharset->Chars[token].Width )	/ TexW, ( float )( mCharset->Chars[token].y + mCharset->Chars[token].Height ) / TexH );
			}

			// Vertex Color Modulation
			{
				pTempVertex[index + 0].Color=ColorModulation;
				pTempVertex[index + 1].Color=ColorModulation;
				pTempVertex[index + 2].Color=ColorModulation;
				pTempVertex[index + 3].Color=ColorModulation;
				pTempVertex[index + 4].Color=ColorModulation;
				pTempVertex[index + 5].Color=ColorModulation;
			}

			xOffset += ( float )mCharset->Chars[token].Width;// + 2.0f;
		}
	}


	void Text::DrawVertexBuffer( int prVertexCount )
	{
		UINT stride = sizeof( Tuxis::Vertex::SpriteVertex );
		UINT offset = 0;
		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &stride, &offset );
		XMMATRIX WorldMatrix = CalculateWorldMatrix();
		XMMATRIX FinalMatrix = WorldMatrix * (Engine::GetInstance()->GetActive2DCamera()->GetFinalMatrix())  ;
		FinalMatrix = XMMatrixTranspose( FinalMatrix );

		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );

		Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &FinalMatrix, 0, 0 );
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );

		Engine::GetContext()->PSSetShaderResources( 0, 1, mFont->GetTextureAtlas()->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mFont->GetTextureAtlas()->GetSamplerState() );
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		Graphics::Instance()->DisableStencilBuffer();
		Engine::GetContext()->Draw( prVertexCount, 0 );
	}



}