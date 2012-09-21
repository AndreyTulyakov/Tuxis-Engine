/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Drawable interface
Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_

#include "Engine.h"
#include "EngineBase.h"
#include "Shader.h"
#include "SceneObject.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC Drawable2D : public SceneObject
	{
	protected:
	
		// Shader
		Shader *mShader;
		ID3D11Buffer		*ShaderConstantBuffer;

		// Vertex Buffer
		ID3D11Buffer *VertexBuffer;
		UINT VB_Stride;
		UINT VB_Offset;
	
		// Matrix
		float2 RotationCenter;
		XMMATRIX RotationMatrix;
		XMMATRIX ScaleMatrix;
		XMMATRIX TranslationMatrix;
	
		XMFLOAT4 ColorModulation;
	
		// Methods
		void InitDrawable();
		void ReleaseDrawable();

	
	public:
		void CreateConstantBuffer(int pBufferSize,D3D11_USAGE pD3D11_USAGE);
		void UpdateConstantBufferData(const void* Data);

		void SetColorModulation( float r, float g, float b );
		void SetAlpha( float a );
	
		void SetRotation(float Pitch,float Yaw,float Roll);
		void SetPosition(float x,float y,float z);
		void SetScale(float x,float y, float z);
	
		XMMATRIX CalculateWorldMatrix();
	
	};
}