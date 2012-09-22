/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Log Module
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#pragma warning( disable : 4251)


#include "fstream"
#include "string"
#include <iostream>
//#include <Windows.h>
using namespace std;

namespace Tuxis
{

	class TUXIS_DECLSPEC Log
	{
	private:
		static bool ConsoleLoging;
		static Log* Instance;
		string FileName;
		ofstream mFile;

		void Init();
		void Release();
		void WriteAll(string Result);
	public:

		// Methods
		Log();
		~Log();

		void EnableConsoleLoging(bool IsIt);

		void Separator();

		static void Info( string Message );
		static void Error( string Message );
		static void Warning( string Message );
		static void Success( string Message );
		static void WriteText( string Message );

		bool operator ! ();
		Log& operator << (int i);
		Log& operator << (float i);
		Log& operator << (string Message);
	};

}