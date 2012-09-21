#include "stdafx.h"
#include "SceneObject.h"

namespace Tuxis
{
	SceneObject::SceneObject()
	{	
		mVisible = true;
		mIgnored = false;
		mChanged = true;
	}

	

	
	void SceneObject::SetVisible(bool value)
	{
		mVisible=value;
	}
	
	void SceneObject::SetIgnoreUpdate(bool value)
	{
		mIgnored=value;
	}
	
	void SceneObject::SetChanged(bool value)
	{
		mChanged=value;
	}
	
	
	bool SceneObject::IsVisible()
	{
		return mVisible;
	}
	
	bool SceneObject::IsIgnoreUpdate()
	{
		return mIgnored;
	}
	
	bool SceneObject::IsChanged()
	{
		return mChanged;
	}
}