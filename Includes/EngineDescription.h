/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Engine Start Description
Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "Camera.h"
#include "Window.h"
#include "Scene.h"


namespace Tuxis
{

	class EngineDescription
	{

	public:

		bool _Windowed;
		bool _VSync;

		Camera *_Camera2D;
		Camera *_Camera3D;
		Window *_Window;
		


		EngineDescription()
		{
			_VSync			= false;
			_Windowed		= false;
			_Window			= 0;
			_Camera2D		= 0;
			_Camera3D		= 0;
		}

		bool Test()
		{
			// Must have 1-2 start camera
			if( !(_Camera2D||_Camera3D))
				return false;
			if(!_Window)	return false;
			return true;
		}
	};

}