#include "stdafx.h"
#include "Input.h"

namespace Tuxis
{
	Input* Input::mInstance=0;
	
	int Input::GetMouseX()
	{
		GetCursorPos( &CursorPosition );
		ScreenToClient( hWindow, &CursorPosition );
		return CursorPosition.x;
	}
	
	int Input::GetMouseY()
	{
		GetCursorPos( &CursorPosition );
		ScreenToClient( hWindow, &CursorPosition );
		return  CursorPosition.y;
	}
	
	
	void Input::SetMousePosition( int X, int Y ,HWND phWindow)
	{
		POINT CurPos;
		CurPos.x = X;
		CurPos.y = Y;
		ClientToScreen( phWindow, &CurPos );
		SetCursorPos( CurPos.x, CurPos.y );
	}
	
	int2 Input::GetGlobalMousePosition()
	{
		int2 pos;
		GetCursorPos( &CursorPosition );
		pos.x=CursorPosition.x;
		pos.y=CursorPosition.y;
		return pos;
	}
	
	int2 Input::GetMousePosition()
	{
		int2 pos;
		GetCursorPos( &CursorPosition );
		ScreenToClient( hWindow, &CursorPosition );
		pos.x=CursorPosition.x;
		pos.y=CursorPosition.y;
		return pos;
	}
	
	Input::Input()
	{
		mInstance=0;
	}

	Input::Input(HWND pHWND)
	{
		mInstance=0;
		Initialize(pHWND);
	}

	void Input::Initialize(HWND theHWND)
	{
		mInstance=this;
		hWindow=theHWND;
		
		MSG msg = {0};
	
		ZeroMemory( &Buttons, sizeof( BYTE ) * 256 );
		for( unsigned short i = 0; i < 256; i++ )
		{
			KeyHits[i] = true;
		}
	
		ZeroMemory( &MouseState, sizeof( DIMOUSESTATE2 ) );
		for( int i = 0; i < 8; i++ )
		{
			MouseHits[i] = true;
		}
	
		if( FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, ( void ** )&lpDI, NULL ) ) )
			Log::Error("Input: DirectInput8Create");
	
		// Keyboard
	
		if( FAILED( lpDI->CreateDevice( GUID_SysKeyboard, &KeyboardDevice, NULL ) ) )
			Log::Error("Input: Can't create Keyboard device");
	
		if( FAILED( KeyboardDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
			Log::Error("Input: Can't Set Data Format for Keyboard device");
	
		if( FAILED( KeyboardDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
			Log::Error("Input: Can't Set Cooperative Level for Keyboard");
	
	
		// Mouse
	
		if( FAILED( lpDI->CreateDevice( GUID_SysMouse, &MouseDevice, NULL ) ) )
			Log::Error("Input: Can't create Mouse device");
	
		if( FAILED( MouseDevice->SetDataFormat( &c_dfDIMouse2 ) ) )
			Log::Error("Input: Can't Set Data Format for Mouse device");
	
		if( FAILED( MouseDevice->SetCooperativeLevel( hWindow, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )
			Log::Error("Input: Can't Set Cooperative Level for mouse");
	
		Log::Success("Input Initialized.");
		
	}
	

	Input* Input::GetInstance()
	{
		if(!mInstance)
			Log::Error("Input::GetInstance: instance is null");
		return mInstance;
	}
	
	
	void Input::Update()
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		HRESULT hr;
	
		hr = KeyboardDevice->GetDeviceState( sizeof( BYTE ) * 256, &Buttons ); // Данные с клавиатуры
		if( FAILED( hr ) )
		{
			//Log::Write()->Warning("Input: Keyboard lost. Acquire...");
			do
			{
				hr = KeyboardDevice->Acquire();
			}
			while( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED );
		}
	
		hr = MouseDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), &MouseState ); // Данные с мышки
		if( FAILED( hr ) )
		{
			//Log::Write()->Warning("Input: Mouse lost. Acquire...");
			do
			{
				hr = MouseDevice->Acquire();
			}
			while( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED );
		}
	
	}
	
	
	
	
	float Input::MouseSpeedX( void )
	{
		return (float)MouseState.lX;
	}
	
	float Input::MouseSpeedY( void )
	{
		return (float)MouseState.lY;
	}
	
	float Input::MouseSpeedZ( void )
	{
		return (float)MouseState.lZ;
	}
	
	bool Input::KeyDown( BYTE in_kb )
	{
		if( Buttons[in_kb] & 0x80 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool Input::KeyHit( BYTE in_kb )
	{
		if( Buttons[in_kb] & 0x80 )
		{
			if( KeyHits[in_kb] )
			{
				KeyHits[in_kb] = false;
				return true;
			}
		}
		else
		{
			KeyHits[in_kb] = true;
		}
	
		return false;
	}
	
	
	bool Input::MouseDown( BYTE in_mb )
	{
		if( MouseState.rgbButtons[in_mb] & 0x80 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	
	bool Input::MouseHit( BYTE in_mb )
	{
		if( MouseState.rgbButtons[in_mb] & 0x80 )
		{
			if( MouseHits[in_mb] )
			{
				MouseHits[in_mb] = false;
				return true;
			}
		}
		else
		{
			MouseHits[in_mb] = true;
		}
	
		return false;
	}
	
	
	void Input::Release( void )
	{
		if( KeyboardDevice )
			KeyboardDevice->Unacquire();
	
		if( MouseDevice )
			MouseDevice->Unacquire();
	
		if( KeyboardDevice )
		{
			KeyboardDevice->Release();
			KeyboardDevice = nullptr;
		}
	
		if( MouseDevice )
		{
			MouseDevice->Release();
			MouseDevice = nullptr;
		}
	
		if( lpDI )
			lpDI->Release();
		
		
		mInstance = nullptr;
	
		Log::Success("Input - Released");
	}
	
}
