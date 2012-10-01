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

	void Scene::DetachChild( SceneObject *obj )
	{
		if(!obj)
			Log::Error("Scene::AttachChild: obj - null");

		for(int i=0;i<ChildObjects.size(); i++)
		{
			if( ChildObjects.at(i) == obj )
			{
				ChildObjects.erase (ChildObjects.begin() + i);
				break;
			}
		}
	}

	void Scene::DetachAllChilds()
	{
		ChildObjects.clear();
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
			SceneObject *pObject;

			for(int i=0; i<NumberOfObjects; i++)
			{
				pObject=ChildObjects.at(i);

				if(!pObject->IsIgnoreUpdate())
				{
					ChildObjects.at(i)->Update();
				}
			}
		}
	}



}
