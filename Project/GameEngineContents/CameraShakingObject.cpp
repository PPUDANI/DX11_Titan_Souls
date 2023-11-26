#include "PreCompile.h"
#include "CameraShakingObject.h"

CameraShakingObject::CameraShakingObject()
{
}

CameraShakingObject::~CameraShakingObject()
{
}

void CameraShakingObject::Init(float _ScreenShakingTime, float _ShakingPerFrame, float _ShakingLerpMax)
{
	ScreenShakingTime = _ScreenShakingTime;
	ShakingPerFrame = _ShakingPerFrame;
	ShakingLerpMax = _ShakingLerpMax;
}

void CameraShakingObject::ShakingScreen(float _Delta)
{
	if (true == ShakingEnd)
	{
		return;
	}

	if (ShakingFrame < FrameTimer)
	{
		if (false == ShakingEnd &&
			ScreenShakingTime > ScreenShakingTimer)
		{
			ScreenShakingTimer += FrameTimer;
			Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
			ShakingLerpValue = std::lerp(ShakingLerpValue, 0.0f, (1.0f / ShakingPerFrame) * FrameTimer);
			CameraManager::AddCameraPosFromShaking.X = Inst.RandomInt(-1, 1) * ShakingLerpValue;
			Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
			CameraManager::AddCameraPosFromShaking.Y = Inst.RandomInt(-1, 1) * ShakingLerpValue;
		}
		else
		{
			CameraManager::AddCameraPosFromShaking = float4::ZERO;
			ShakingEnd = true;
		}

		FrameTimer -= ShakingFrame;
	}
	else
	{
		FrameTimer += _Delta;
	}
}