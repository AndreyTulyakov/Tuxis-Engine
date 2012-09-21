#include "stdafx.h"
#include "DefaultShaderBase.h"

namespace Tuxis
{
	DefaultShaderBase* DefaultShaderBase::mInstance = nullptr;
	bool DefaultShaderBase::Loaded = false;


	DefaultShaderBase::DefaultShaderBase()
	{
		if(mInstance == nullptr)
		{
			mInstance = this;
		}
		else
			Log::Warning("DefaultShaderBase::DefaultShaderBase already created.");

		mShaderSprite			= nullptr;
		mShaderSpriteGroup		= nullptr;
		mShaderText				= nullptr;
		mShaderTiledSprite		= nullptr;
		mShaderTiledSpriteGroup = nullptr;
		
	}

	void DefaultShaderBase::LoadShaders()
	{
		mShaderSprite			= new Shader();
		mShaderSpriteGroup		= new Shader();
		mShaderText				= new Shader();
		mShaderTiledSprite		= new Shader();
		mShaderTiledSpriteGroup = new Shader();

		mShaderSprite			->Load(wstring(Path::DEFAULT_SHADERS+L"TxSprite.fx" ).c_str());
		mShaderSpriteGroup		->Load(wstring(Path::DEFAULT_SHADERS+L"TxSpriteGroup.fx" ).c_str());
		mShaderText				->Load(wstring(Path::DEFAULT_SHADERS+L"TxText.fx" ).c_str());
		mShaderTiledSprite		->Load(wstring(Path::DEFAULT_SHADERS+L"TxTiledSprite.fx" ).c_str());
		mShaderTiledSpriteGroup ->Load(wstring(Path::DEFAULT_SHADERS+L"TxTiledSpriteGroup.fx" ).c_str());

		mShaderSprite			->CreateInputLayout(ShaderLayouts::SpriteLayout,2);
		mShaderSpriteGroup		->CreateInputLayout(ShaderLayouts::SpriteGroupLayout,5);
		mShaderText				->CreateInputLayout(ShaderLayouts::StandartLayout,3);
		mShaderTiledSprite		->CreateInputLayout(ShaderLayouts::SpriteLayout,2);
		mShaderTiledSpriteGroup ->CreateInputLayout(ShaderLayouts::TiledSpriteGroupLayout,5);

		Loaded = true;

		Log::Success("DefaultShaderBase::LoadShaders");
	}

	void DefaultShaderBase::ReleaseShaders()
	{
		if(Loaded)
		{
			_RELEASE_DELETE(mShaderSprite)
			_RELEASE_DELETE(mShaderSpriteGroup)
			_RELEASE_DELETE(mShaderText)
			_RELEASE_DELETE(mShaderTiledSprite)
			_RELEASE_DELETE(mShaderTiledSpriteGroup)
		}
		Loaded = false;
		Log::Success("DefaultShaderBase::ReleaseShaders");
	}
	
	DefaultShaderBase::~DefaultShaderBase()
	{
		if(mInstance)
			if(Loaded)
			{
				ReleaseShaders();
			}
		mInstance = nullptr;
	}

	DefaultShaderBase* DefaultShaderBase::Instance()
	{
		if(mInstance == nullptr)
		{
			Log::Error("DefaultShaderBase::GetInstance: you must create object before.");
			return nullptr;
		}
		else
			return mInstance;
	}
}