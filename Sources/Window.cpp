#include "stdafx.h"
#include "Window.h"


namespace Tuxis
{
	Window::Window()
	{
		Created=false;
		mClassName=L"TuxisWindowClass";
		mWindowHandler = NULL;

		// Register window class
		hInstance = GetModuleHandle( NULL );

		WNDCLASSEX wc;
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style          = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc    = WndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 0;
		wc.hInstance      = hInstance;
		wc.hIcon          = LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground  = ( HBRUSH )COLOR_GRAYTEXT;
		wc.lpszMenuName   = NULL;
		wc.lpszClassName  = mClassName.c_str();
		wc.hIconSm        = LoadIcon( NULL, IDI_APPLICATION );

		if( !RegisterClassEx( &wc ) )
		{
			Log::Error( "Window::Window: RegisterClassEx(&wc)" );
		}
	}

	Window::~Window()
	{
		Release();
		// UnRegister window class
		if(!mClassName.empty() && !UnregisterClassW(mClassName.c_str(),hInstance))
		{
			Log::Error( "Window::~Window: Could Not Unregister Class." );
		}
	}

	void Window::Create(int pWidth,int pHeight, const WCHAR* pCaption, bool EnableButtonBox )
	{
		if(Created)
		{
			Log::Error( "Window::Create: Window already created!" );
		}

		mWindowHandler	=NULL;
		mWidth			=pWidth;
		mHeight			=pHeight;
		mCaption		=pCaption;


		DWORD WindowStyle;

		if(EnableButtonBox)
			WindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
		else
			WindowStyle = WS_BORDER;


		mWindowHandler = CreateWindowW(
			mClassName.c_str(), 
			mCaption.c_str(), 
			WindowStyle, 
			CW_USEDEFAULT, CW_USEDEFAULT,
			mWidth	+ GetSystemMetrics( SM_CXFIXEDFRAME ) * 2,
			mHeight	+ GetSystemMetrics( SM_CYFIXEDFRAME ) * 2 + GetSystemMetrics( SM_CYCAPTION ),
			NULL,NULL,
			hInstance,	NULL );

		if( !mWindowHandler )
		{
			Log::Error( "Window::Window: Window not created!" );
		}

		ShowWindow( mWindowHandler, SW_SHOW );
		SetForegroundWindow(mWindowHandler);
		SetFocus(mWindowHandler);
		UpdateWindow( mWindowHandler);

		Created=true;

		Log::Success("Window created.");
	}



	bool Window::IsRunning()
	{
		if(Created)
		{
			return IsWindow(mWindowHandler) ? true : false;;
		}
		return false;
	}



	void Window::SetWindow(HWND pHWND,int pWidth, int pHeight)
	{
		mWindowHandler	=pHWND;
		mWidth			=pWidth;
		mHeight			=pHeight;
		mCaption		=L"";

		Log::Success("Window: selected exist by HWND.");
	}


	void Window::Release()
	{
		if(IsWindow(mWindowHandler))
		{
			if(!DestroyWindow(mWindowHandler))
			{
				Log::Error( "Window::Release: Could Not Destroy Window." );
				mWindowHandler=NULL;										
			}

			Created=false;
			Log::Success("Window - Released");
		}
	}


	HWND Window::GetHWND()
	{
		return mWindowHandler;
	}

	int Window::GetWidth()
	{
		return mWidth;
	}

	int Window::GetHeight()
	{
		return mHeight;
	}






	LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)			
	{
		switch (uMsg)								
		{

		case WM_ACTIVATE:							
			{
				return 0;								
			}
		case WM_SYSCOMMAND:							
			{
				switch (wParam)							
				{
				case SC_SCREENSAVE:	
				case SC_MONITORPOWER:
					return 0;
				}
				break;									
			}
		case WM_CLOSE:								
			{
				DestroyWindow(hWnd);
				Log::Success("Window - Released by WndProc");
				return 0;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		// Pass All Unhandled Messages To DefWindowProc
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}

}