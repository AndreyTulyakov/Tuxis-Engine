/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Input Module
Required: dinput.h , dinput8.lib, dxguid.lib
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include "InputBase.h"
#include "Types.h"
#include "Log.h"

namespace Tuxis
{

	class TUXIS_DECLSPEC Input
	{
	public:
		static Input* GetInstance();

		
		Input(HWND);
		Input();
		void Input::Initialize(HWND theHWND);

		void Release();

		// For Manual Input Update
		void Update();


		bool KeyDown( BYTE in_kb );		
		bool KeyHit( BYTE in_kb );	
		bool MouseDown( BYTE in_mb ); 
		bool MouseHit( BYTE in_mb );	

		int GetMouseX();
		int GetMouseY();

		static void SetMousePosition( int, int,HWND phWindow );
		int2 GetMousePosition();
		int2 GetGlobalMousePosition();

		float MouseSpeedX( void );
		float MouseSpeedY( void );
		float MouseSpeedZ( void );

	private:
		MSG msg;
		POINT CursorPosition;
		LPDIRECTINPUT8 lpDI;					
		LPDIRECTINPUTDEVICE8 KeyboardDevice,MouseDevice;		

		BYTE Buttons[256];
		bool KeyHits[256];

		DIMOUSESTATE2 MouseState;	
		bool MouseHits[8];	

		HWND hWindow;

		static Input* mInstance;
	};

}