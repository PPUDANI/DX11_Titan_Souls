#include "PreCompile.h"
#include "ColossusBody.h"
#include "Hand.h"

void ColossusBody::SleepStart()
{
	Hand::ModeSwitchIsAbleValue = false;
	Collision->Off();
	HeadRenderer->ChangeAnimation("Sleep");
}

void ColossusBody::WakeUpStart()
{
	CameraManager::CalCameraPosFromArrowOff();

	WakeUpRatio = 0.0f;
	ZoomRatio = 1.0f;
	HeadRenderer->ChangeAnimation("WakeUp");

	ShakingEnd = false;
	ScreenShakingTime = 1.5f;
	ScreenShakingTimer = 0.0f;
	ShakingPerFrame = 0.5f;
	ShakingLerpValue = 10.0f;
}

void ColossusBody::IdleStart()
{
	CameraManager::CalCameraPosFromArrowOn();
	Collision->On();
	HeadRenderer->ChangeAnimation("Idle");

	Speed = 5.0f;
	MovingHeight = 20.0f;
}

void ColossusBody::HitStart()
{

}

void ColossusBody::DeathStart()
{

}



void ColossusBody::SleepUpdate(float _Delta)
{
	if (true == IsBodyHitByArrow)
	{
		BodyCollision2->On();
		BodyCollision->Transform.SetLocalScale({ 64.0f, 32.0f, 1.0f });
		BodyCollision->Transform.SetLocalPosition({ -48.0f, 64.0f });
		ChangeState(BODY_STATE::WakeUp);
	}

	Levitaion(_Delta);
}

void ColossusBody::WakeUpUpdate(float _Delta)
{

	WakeUpRatio = std::lerp(WakeUpRatio, 1.0f, 3.0f * _Delta);
	CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition() + float4{ 0.0f, 20.0f }) * WakeUpRatio;

	if (0.99f < WakeUpRatio)
	{
		if (true == HeadRenderer->IsCurAnimation("Angry") &&
			true == HeadRenderer->IsCurAnimationEnd())
		{
			Hand::ModeSwitchIsAbleValue = true;
			ChangeState(BODY_STATE::Idle);
			return;
		}
		BodyLightRenderer->GetColorData().MulColor.A = 1.0f;
		HeadRenderer->ChangeAnimation("Angry");

		ZoomRatio = std::lerp(ZoomRatio, 0.8f, 5.0f * _Delta);
		CameraManager::AddCameraZoomFromBoss = ZoomRatio;

		ShakingScreen(_Delta);
	}


}

void ColossusBody::IdleUpdate(float _Delta)
{
	Levitaion(_Delta);

	ShakingScreen(_Delta);
}

void ColossusBody::HitUpdate(float _Delta)
{

}

void ColossusBody::DeathUpdate(float _Delta)
{

}

