#include "stdafx.h"
#include "Log.h"
#include "EngineBase.h"

namespace Tuxis
{
	Log* Log::Instance = NULL;
	bool Log::ConsoleLoging = true;
	
	Log::Log()
	{
		FileName = "Log.txt";
		
		if(Instance==NULL)
		{
			Instance = this;
			Instance->Init();
		}
		else
		{
			Warning("Log::Log: Log already exist");
		}
	}
	
	Log::~Log()
	{
		Release();
	}

	void Log::Release()
	{
		Separator();
		Info( "Stop logging" );
		Separator();
		mFile.close();
		Instance=NULL;
	}
	

	void Log::EnableConsoleLoging(bool IsIt)
	{
		ConsoleLoging = IsIt;
	}

	void Log::Init()
	{
		mFile.open( FileName , ios_base::out );
		if(mFile.fail()) exit(-1);
	
		WriteText( "Tuxis Log System\n" );
#ifdef _DEBUG
		WriteText("Debug mode\n");
#else
		WriteText("Release mode\n");
#endif
		Separator();
		Info("Start logging");
		Separator();
	}
	
	
	
	void Log::Info( string Message )
	{
		if( Instance )
		{
			Message.insert(0,"INFO: ");
			Message.append("\n");
			Instance->WriteAll(Message);
		}
	}
	
	
	void Log::WriteText( string Message )
	{
		if( Instance )
		{
			Instance->WriteAll(Message);
		}
	}
	
	
	void Log::Separator()
	{
		if( Instance )
		{
			string Message="-------------------------------------------------------------------------------\n" ;
			Instance->mFile.write( Message.c_str(), Message.size() );
			if(ConsoleLoging) cout<<Message.c_str();
		}
	}
	
	
	void Log::Error( string Message )
	{
		if( Instance )
		{
			Message.insert(0,"ERROR: ");
			Message.append("\n");
			Instance->WriteAll(Message);
			Instance->Release();
		}
			MessageBoxA(0,Message.c_str(),"Error",0);
			exit( -1 );
	}
	
	
	void Log::Warning( string Message )
	{
		if( Instance )
		{
			Message.insert(0,"WARNING: ");
			Message.append("\n");
			Instance->WriteAll(Message);
		}
	}
	
	
	void Log::Success( string Message )
	{
		if( Instance )
		{
			Message.insert(0,"SUCCESS: ");
			Message.append("\n");
			Instance->WriteAll(Message);
		}
	}

	bool Log::operator ! ()
	{
		return Instance==nullptr;
	}

	Log& Log::operator<<( int i )
	{
		if(Instance)
		{
			string Message = IntToString(i);
			Instance->WriteAll(Message);
		}
		return *this;
	}

	Log& Log::operator<<( float i )
	{
		if(Instance)
		{
			string Message = FloatToString(i);
			Instance->WriteAll(Message);
		}
		
		return *this;
	}

	Log& Log::operator<<( string Message )
	{
		if(Instance)
		{
			Instance->WriteAll(Message);
		}
		return *this;
	}

	void Log::WriteAll( string ResultMessage )
	{
		if(mFile.is_open())
		{
			mFile.write( ResultMessage.c_str(), ResultMessage.size() );
			mFile.flush();
		}
		if(ConsoleLoging) cout<<ResultMessage.c_str();
	}


	
}
