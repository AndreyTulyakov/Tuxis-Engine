/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Light object
-Uncompleted
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_
#pragma warning(disable:4251)

#include <d3d11.h>
#include <xnamath.h>

#include "SceneObject.h"

namespace Tuxis
{
	class TUXIS_DECLSPEC Light : public SceneObject
	{
	public:
		Light();
		~Light();
	
		void Draw();
		void Update();
	
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;
	};
}