#include "stdafx.h"
#include "Scene.h"

namespace Tuxis
{
	Scene::Scene()
	{
		On();
	}
	
	Scene::~Scene()
	{
	
	}
	

	void Scene::On()
	{
		mVisible=true;
		mIgnored=false;
	}
	
	void Scene::Off()
	{
		mVisible=false;
		mIgnored=true;
	}
	
	void Scene::AttachChild(SceneObject *obj)
	{
		if(!obj)
			Log::Error("Scene::AttachChild: obj - null");
		ChildObjects.push_back(obj);
	}
	
	void Scene::Draw()
	{
		if(mVisible)
		{
			int NumberOfObjects=ChildObjects.size();
	
			SceneObject *pObject;
	
			for(int i=0; i<NumberOfObjects; i++)
			{
				pObject=ChildObjects.at(i);
				if(pObject->IsVisible())
				{
					pObject->Draw();
				}
			}
		}
	}
	
	void Scene::Update()
	{
		if(!mIgnored)
		{
			int NumberOfObjects=ChildObjects.size();
			for(int i=0; i<NumberOfObjects; i++)
			{
				ChildObjects.at(i)->Update();
			}
		}
	}
}
