/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Scene class
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "SceneObject.h"
#include "Log.h"

#include <vector>
using namespace std;

namespace Tuxis
{

	class TUXIS_DECLSPEC Scene: public SceneObject
	{
	public:
		Scene();
		~Scene();

		void AttachChild(SceneObject *obj);

		void On();
		void Off();

		void Draw();
		void Update();

	protected:
		vector <SceneObject *> ChildObjects;

		bool mVisible;
		bool mIgnored;
	};

}