#include "stdafx.h"
#include "BasicSprite.h"

namespace Tuxis
{
	BasicSprite::BasicSprite()
	{
		Visible=true;
		Frame=0;
	
		Position.x=0.0f;
		Position.y=0.0f;
		Position.z=0.0f;
	
		Color.x=1.0f;
		Color.y=1.0f;
		Color.z=1.0f;
		Color.w=1.0f;
	
		Scale=1.0f;
	
		Rotation=0.0f;
	}
	
	void BasicSprite::SetPosition(float px, float py)
	{
		Position.x=px;
		Position.y=py;
		Position.z=0.0f;
	}
	
	void BasicSprite::SetRotation(float pRotation)
	{
		Rotation=pRotation;
	}
	
	void BasicSprite::SetScale(float pScale)
	{
		Scale=pScale;
	
	}
	
	void BasicSprite::SetFrame(int pFrame)
	{
		Frame=pFrame;
	}
	
	void BasicSprite::SetVisible(bool pVisible)
	{
		Visible=pVisible;
	}
	
	void BasicSprite::SetColor(XMFLOAT4 pColor)
	{
		Color=pColor;
	}
}