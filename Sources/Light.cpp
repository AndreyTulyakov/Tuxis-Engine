#include "stdafx.h"
#include "Light.h"

namespace Tuxis
{
	Light::Light()
	{
		ZeroMemory(this, sizeof(Light));
	
		ambientColor		= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		diffuseColor		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		lightDirection		= XMFLOAT3(2.0f, -2.0f, 0.0f);
	}
	
	Light::~Light()
	{
	
	}
	
	void Light::Draw()
	{
	
	}
	
	void Light::Update()
	{
	
	}
}