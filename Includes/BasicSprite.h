/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================

Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#pragma warning(disable:4251)

#include "EngineBase.h"
#include "Types.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC BasicSprite
	{
	public:
	
		BasicSprite();
	
		void SetRotation(float pRotation);
		void SetPosition(float px, float py);
		void SetFrame(int pFrame);
		void SetVisible(bool pVisible);
		void SetScale(float pScale);
		void SetColor(XMFLOAT4 pColor);
	
		
	
		bool Visible;
		int Frame;
		XMFLOAT3 Position;
		float Scale;
		float Rotation;
		XMFLOAT4 Color;
	
	};
}