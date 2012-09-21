#include "stdafx.h"
#include "Drawable2D.h"

namespace Tuxis
{
	XMMATRIX Drawable2D::CalculateWorldMatrix()
	{
		return ScaleMatrix * RotationMatrix * TranslationMatrix;
	}
	
	void Drawable2D::SetScale(float sx,float sy, float sz=1.0f)
	{
		mChanged=true;
		ScaleMatrix = XMMatrixScaling( sx, sy, sz );
	}
	
	void Drawable2D::SetRotation(float Pitch,float Yaw,float Roll)
	{
		mChanged=true;
		RotationMatrix = XMMatrixRotationRollPitchYaw(Pitch*DEGTORAD, Yaw*DEGTORAD, Roll*DEGTORAD);
	}

	
	void Drawable2D::SetPosition(float x,float y,float z=0.0f)
	{
		mChanged=true;
		TranslationMatrix = XMMatrixTranslation(x,y,z);
	}
	
	
	void Drawable2D::InitDrawable()
	{
		mChanged=true;
		VB_Stride=0;
		VB_Offset=0;
		mShader = nullptr;
		VertexBuffer = nullptr;
		ShaderConstantBuffer = nullptr;
	
		// Matrix Default Configuration
		ScaleMatrix = XMMatrixScaling( 1.0f, 1.0f, 1.0f );
		TranslationMatrix = XMMatrixTranslation( 0.0f, 0.0f, 0.0f );
		RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f,0.0f,0.0f);
	
		ColorModulation = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );

		RotationCenter(0.0f,0.0f);
	}
	
	void Drawable2D::ReleaseDrawable()
	{
		_RELEASE(ShaderConstantBuffer);
		_RELEASE(VertexBuffer);
		mShader = nullptr;
	}
	
	void Drawable2D::SetColorModulation( float r, float g, float b )
	{
		mChanged=true;
		ColorModulation.x = r;
		ColorModulation.y = g;
		ColorModulation.z = b;
	}
	
	void Drawable2D::SetAlpha( float a )
	{
		mChanged=true;
		ColorModulation.w = a;
	}


	void Drawable2D::CreateConstantBuffer(int pBufferSize,D3D11_USAGE pD3D11_USAGE)
	{
		_RELEASE(ShaderConstantBuffer);
		
		//Create the buffer to send to the cbuffer in effect file
		D3D11_BUFFER_DESC ConstantBufferDescribes;
		ZeroMemory( &ConstantBufferDescribes, sizeof( D3D11_BUFFER_DESC ) );
		ConstantBufferDescribes.ByteWidth = pBufferSize;
		ConstantBufferDescribes.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDescribes.MiscFlags = 0;
		ConstantBufferDescribes.Usage = (D3D11_USAGE)pD3D11_USAGE;

		if(pD3D11_USAGE==D3D11_USAGE_DYNAMIC)
			ConstantBufferDescribes.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		else
			ConstantBufferDescribes.CPUAccessFlags = 0;

		hr = Graphics::Instance()->GetDevice()->CreateBuffer( &ConstantBufferDescribes, NULL, &ShaderConstantBuffer );
		if(FAILED(hr))	
			Log::Error("TxShader::CreateConstantBuffer CreateBuffer ");
	}


	void Drawable2D::UpdateConstantBufferData(const void* Data)
	{
		if(ShaderConstantBuffer == nullptr)
			Log::Warning("Drawable2D::UpdateConstantBufferData: Constant buffer not exist");
		else
			Engine::GetContext()->UpdateSubresource( ShaderConstantBuffer, 0, NULL, Data, 0, 0 );
	}

}