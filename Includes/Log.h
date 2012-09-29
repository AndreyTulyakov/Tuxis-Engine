/*
* ===============================================================================
* Tuxis Project
* Copyright (C) 2011-2012, Andrew Tulay
* ===============================================================================
* Log class
* ===============================================================================
*/

#pragma once
#include "_DllExport.h"

#pragma warning( disable : 4251)


#include "fstream"
#include "string"
#include <iostream>
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
		void WriteAll( const char* Result);
	public:

		// Methods
		Log();
		~Log();

		void EnableConsoleLoging(bool IsIt);

		void Separator();

		static void Info( const char* Message );
		static void Error( const char* Message );
		static void Warning( const char* Message );
		static void Success(  const char* Message );
		static void WriteText(  const char* Message );

		bool operator ! ();
		Log& operator << (int i);
		Log& operator << (float i);
		Log& operator << ( const char* Message);
	};

}