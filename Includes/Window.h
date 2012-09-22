/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Window Module
Required: dinput.h , dinput8.lib, dxguid.lib
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Log.h"

#include "string"
using namespace std;


namespace Tuxis
{
	class Window;

	typedef LRESULT (CALLBACK Window::*WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	//typedef void (Window::*FunctionPointer)()const;
	

	class TUXIS_DECLSPEC Window
	{
	private:
		
		bool Created;

		int mWidth, mHeight;
		HWND mWindowHandler;

		wstring mCaption;
		wstring mClassName;

		HINSTANCE hInstance;

	public:

		Window();
		~Window();

		void Create(int pWidth, int pHeight, const WCHAR* pCaption, bool EnableButtonBox);
		void SetWindow(HWND pHWND,int pWidth, int pHeight);

		bool IsRunning();

		void Release();
		
		HWND GetHWND();
		int GetWidth();
		int GetHeight();
	};



	TUXIS_DECLSPEC LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

}


