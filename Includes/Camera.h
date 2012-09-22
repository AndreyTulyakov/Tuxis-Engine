/*
===============================================================================
Project Tuxis. 2011-2012.
===============================================================================
Camera class
Required: <d3d11.h> <xnamath.h>
===============================================================================
*/

#pragma once
#include "_DllExport.h"

#include "Log.h"

#define _XM_NO_INTRINSICS_
#include <d3d11.h>
#pragma warning(disable:4251)
#include <xnamath.h>


namespace Tuxis
{

	class TUXIS_DECLSPEC Camera
	{
	private:
		float mMoveLeftRight, mMoveBackForward, mMoveTopDown;

		XMMATRIX mViewMatrix;
		XMMATRIX mProjectionMatrix;
		XMMATRIX mRotationMatrix;

		XMVECTOR mPosition;
		XMVECTOR mTarget;
		XMVECTOR mUp;
		XMVECTOR mRight;
		XMVECTOR mForward;

		XMVECTOR DefaultRight;
		XMVECTOR DefaultUp;
		XMVECTOR DefaultForward;

		float Roll, Pitch, Yaw;


	public:

		Camera();

		void SetOrthoProjection(float X1, float X2, float Y1, float Y2, float ZNear, float ZFar);
		void SetPerspectiveProjection(float FovDEG, float pAspertRatio, float ZNear, float ZFar);

		void Turn(float pRoll, float pPitch, float pYaw);
		void Move(float pX, float pY, float pZ);

		void SetPosition(float pX, float pY, float pZ);
		void SetRotation(float pRoll, float pPitch, float pYaw);

		void UpdateViewMatrix();
		void Update();

		float GetRoll();
		float GetPitch();
		float GetYaw();

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();

		XMMATRIX GetFinalMatrix();
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjectionMatrix();	
	};

}