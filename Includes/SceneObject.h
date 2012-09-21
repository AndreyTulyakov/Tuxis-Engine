/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Scene Object
Required:
===============================================================================
*/

#pragma once
#include "_DllExport.h"

namespace Tuxis
{

	class TUXIS_DECLSPEC SceneObject
	{
	protected:
		bool mChanged;
		bool mVisible;
		bool mIgnored;

	public:
		SceneObject();

		void SetVisible(bool value);
		void SetIgnoreUpdate(bool value);
		void SetChanged(bool value);

		bool IsChanged();
		bool IsVisible();
		bool IsIgnoreUpdate();

		virtual void Draw()=0;
		virtual void Update()=0;
		//virtual ~SceneObject();


	};

}