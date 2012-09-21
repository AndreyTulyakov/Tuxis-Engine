#include "stdafx.h"
#include "Mesh.h"

namespace Tuxis
{
	Mesh::Mesh()
	{
		InitDrawable();
	
		mShader=new Shader();
		wstring ResPath=Path::DEFAULT_SHADERS+L"TxMesh.fx";
		mShader->Load(ResPath.c_str());
		mShader->CreateInputLayout(ShaderLayouts::TestLayout,2);

		CreateConstantBuffer(sizeof(CBStruct),D3D11_USAGE_DEFAULT);
	}
	
	
	bool Mesh::LoadModel(const WCHAR* filename)
	{
		ifstream fin;
		char input;
		int i;
	
	
		// Open the model file.
		fin.open(filename);
	
		// If it could not open the file then exit.
		if(fin.fail())
		{
			return false;
		}
	
		// Read up to the value of vertex count.
		fin.get(input);
		while(input != ':')
		{
			fin.get(input);
		}
	
		// Read in the vertex count.
		fin >> VertexCount;
	
		// Create the model using the vertex count that was read in.
		vertices = new Tuxis::Vertex::VertexTest[VertexCount];
		if(!vertices)
		{
			return false;
		}
	
		// Read up to the beginning of the data.
		fin.get(input);
		while(input != ':')
		{
			fin.get(input);
		}
		fin.get(input);
		fin.get(input);
	
		// NOT USED
		XMFLOAT3 Normal;
	
		// Read in the vertex data.
		for(i=0; i<VertexCount; i++)
		{
			fin >> vertices[i].Position.x >> vertices[i].Position.y >> vertices[i].Position.z;
			fin >> vertices[i].Texture.x >> vertices[i].Texture.y;
			fin >> Normal.x >> Normal.y >> Normal.z;
		}
	
		// Close the model file.
		fin.close();
	
	
	
	
	
	
	
	
		VB_Stride = sizeof( Tuxis::Vertex::VertexTest );
		VB_Offset = 0;
	
		// Vertex Buffer Creating
		D3D11_BUFFER_DESC VertexBufferDesc;
		ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
		VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		VertexBufferDesc.ByteWidth = sizeof( Tuxis::Vertex::VertexTest ) * VertexCount;
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
	
	
		return true;
	}
	
	
	
	void Mesh::SetShader(Shader *pShader)
	{
	
	}
	
	void Mesh::SetTextureAuto(TextureAtlas *pTexture)
	{
		mTexture=pTexture;
	
	}
	
	
	
	void Mesh::Draw()
	{
		if(!mVisible) return;
	
		if(!VertexBuffer) Log::Error("Primitive::Draw VertexBuffer is null");
	
	
		// Calculate matrices
		XMMATRIX WorldMatrix = CalculateWorldMatrix();
		XMMATRIX FinalMatrix = WorldMatrix*(Engine::GetInstance()->GetActive3DCamera()->GetFinalMatrix() );
		FinalMatrix = XMMatrixTranspose( FinalMatrix );
	
		/*
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		{
			HRESULT result;
			// Lock the constant buffer so it can be written to.
			result = Engine::Context->Map(mShader->ObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			if(FAILED(result))
			{
				TxLog::Error("Primitive::Draw Engine::Context->Map(mShader->ObjectBuffer...");
			}
			// Get a pointer to the data in the constant buffer.
			CBStruct *dataPtr = (CBStruct*)mappedResource.pData;
			*dataPtr=mCBStruct;
	
			// Unlock the constant buffer.
			Engine::Context->Unmap(mShader->ObjectBuffer, 0);
		}
		
		*/
	
	
	
		Engine::GetGraphics()->EnableStencilBuffer();
	
		// Context configuration
		
		Engine::GetContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &VB_Stride, &VB_Offset );
		Engine::GetContext()->VSSetShader( mShader->VertexShader, 0, 0 );
		Engine::GetContext()->PSSetShader( mShader->PixelShader , 0, 0 );
		Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, &FinalMatrix, 0, 0 );
		Engine::GetContext()->VSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );
		Engine::GetContext()->PSSetConstantBuffers( 0, 1, &ShaderConstantBuffer );
	
		Engine::GetContext()->PSSetShaderResources( 0, 1, mTexture->GetShaderResourceView() );
		Engine::GetContext()->PSSetSamplers( 0, 1, mTexture->GetSamplerState() );
	
		Engine::GetContext()->IASetInputLayout( mShader->InputLayout );
		Engine::GetContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	
	
		// Drawing
		
		Engine::GetContext()->Draw(VertexCount,0);
	
	}
	
	void Mesh::Release()
	{	
		if(vertices)
		{
			delete [] vertices;
			vertices = 0;
		}
		ReleaseDrawable();
	}
	
	
	
	void Mesh::Update()
	{
	
	}
}