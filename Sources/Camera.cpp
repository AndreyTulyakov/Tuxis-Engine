#include "stdafx.h"
#include "Camera.h"

namespace Tuxis
{
	
	#define DEGTORAD 0.0174532925199432957f
	
	Camera::Camera()
	{
		mRight		= XMVectorSet( 1.0f, 0.0f, 0.0f, 0.0f );
		mUp			= XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		mForward	= XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f );
		mPosition	= XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
		mTarget		= XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f );
	
		mMoveLeftRight = 0.0f;
		mMoveBackForward = 0.0f;
		mMoveTopDown = 0.0f;
	
		Roll = 0.0f;
		Pitch = 0.0f;
		Yaw = 0.0f;
	
		DefaultRight	= XMVectorSet(1.0f,0.0f,0.0f, 0.0f);
		DefaultUp		= XMVectorSet(0.0f,1.0f,0.0f, 0.0f);
		DefaultForward  = XMVectorSet(0.0f,0.0f,1.0f, 0.0f);
	
		UpdateViewMatrix();
	}
	
	
	float Camera::GetRoll()
	{
		return Roll;
	}
	
	float Camera::GetPitch()
	{
		return Pitch;
	}
	
	float Camera::GetYaw()
	{
		return Yaw;
	}
	
	XMFLOAT3 Camera::GetPosition()
	{
		return XMFLOAT3( mPosition.x, mPosition.y, mPosition.z);
	}
	
	XMFLOAT3 Camera::GetRotation()
	{
		return XMFLOAT3( Roll, Pitch, Yaw);
	}
	
	
	void Camera::SetPosition(float pX, float pY, float pZ)
	{
		mPosition = XMVectorSet( pX, pY, pZ, 0.0f );
	}
	
	void Camera::SetRotation(float pRoll, float pPitch, float pYaw)
	{
		Roll += pRoll;
		Pitch += pPitch;
		Yaw += pYaw;
	}

	void Camera::SetOrthoProjection(float X1, float X2, float Y1, float Y2, float ZNear, float ZFar)
	{
		if(X2>X1 && Y2>Y1 && ZFar>ZNear)
			mProjectionMatrix=XMMatrixOrthographicOffCenterLH(X1,X2,Y2,Y1,ZNear,ZFar);
		else
			Log::Error("Camera::SetOrthoProjection: check parametr's");
	}
	
	void Camera::SetPerspectiveProjection(float FovDEG, float pAspertRatio, float ZNear, float ZFar)
	{
		if(ZNear==0.00f)
		{
			ZNear+=0.01f;
			Log::Warning("Camera::SetPerspectiveProjection: ZNear=0 is bad idea");
		}

		if(FovDEG<1.0f)
			FovDEG=1.0f;
	
		if(FovDEG>179.0f)
			FovDEG=179.0f;
	
		mProjectionMatrix = XMMatrixPerspectiveFovLH( FovDEG*DEGTORAD, pAspertRatio, ZNear, ZFar );
	}
	
	void Camera::UpdateViewMatrix()
	{
		mViewMatrix = XMMatrixLookAtLH( mPosition, mTarget, mUp );
	}
	
	XMMATRIX Camera::GetFinalMatrix()
	{
		return mViewMatrix * mProjectionMatrix;
	}
	
	XMMATRIX Camera::GetProjectionMatrix()
	{
		return mProjectionMatrix;
	}
	
	XMMATRIX Camera::GetViewMatrix()
	{
		return mViewMatrix;
	}
	
	
	void Camera::Move(float pX, float pY, float pZ)
	{
		mMoveLeftRight += pX;
		mMoveTopDown += pY;
		mMoveBackForward += pZ;
	}
	
	void Camera::Turn(float pRoll, float pPitch, float pYaw)
	{
		Roll += pRoll;
		Pitch += pPitch;
		Yaw += pYaw;
	
		Roll = fmod(Roll, XM_2PI);
		
		if(Roll>XM_PI/2.0f)
		{
			Roll=XM_PI/2.0f;
		}
	
		if(Roll<-XM_PI/2.0f)
		{
			Roll=-XM_PI/2.0f;
		}
	}
	


	void Camera::Update()
	{
		mRotationMatrix = XMMatrixRotationRollPitchYaw(Roll, Pitch, Yaw);
		mTarget = XMVector3TransformCoord(DefaultForward, mRotationMatrix );
		mTarget = XMVector3Normalize(mTarget);
	
		XMMATRIX RotateYTempMatrix;
		RotateYTempMatrix = XMMatrixRotationRollPitchYaw(Roll, Pitch, Yaw);
	
		mRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
		mUp = XMVector3TransformCoord(DefaultUp, RotateYTempMatrix);
		mForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);
	
		mPosition += mMoveLeftRight*mRight;
		mPosition += mMoveTopDown*mUp;
		mPosition += mMoveBackForward*mForward;
	
		mMoveLeftRight = 0.0f;
		mMoveTopDown = 0.0f;
		mMoveBackForward = 0.0f;
	
		mTarget = mPosition + mTarget;	
	
		UpdateViewMatrix();
	}
}