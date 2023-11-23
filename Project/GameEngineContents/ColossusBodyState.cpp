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
	CameraMoveRatio = 0.0f;
	HeadRenderer->ChangeAnimation("WakeUp");

}

void ColossusBody::ShoutingStart()
{
	EffectSoundPlay("Roar.ogg");
	HeadRenderer->ChangeAnimation("Shouting");

	ShakingEnd = false;
	ScreenShakingTime = 1.5f;
	ScreenShakingTimer = 0.0f;
	ShakingPerFrame = 0.5f;
	ShakingLerpValue = 10.0f;

	ZoomRatio = 1.0f;
	BodyLightRenderer->GetColorData().MulColor.A = 1.0f;
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
	BodyLightRenderer->GetColorData().MulColor.A = 1.0f;
	HeadRenderer->ChangeAnimation("Shouting");
	LeftHand->ChangeState(HAND_STATE::Hit);
	RightHand->ChangeState(HAND_STATE::Hit);
}

void ColossusBody::DeathStart()
{
	BodyLightRenderer->GetColorData().MulColor.A = 0.0f;
}



void ColossusBody::SleepUpdate(float _Delta)
{
	if (true == IsBodyHitByArrow)
	{
		BodyCollision2->On();
		BodyCollision->Transform.SetLocalScale({ 64.0f, 32.0f, 1.0f });
		BodyCollision->Transform.SetLocalPosition({ -48.0f, 64.0f });
		ChangeState(BODY_STATE::WakeUp);
		return;
	}

	Levitaion(_Delta);
}

void ColossusBody::WakeUpUpdate(float _Delta)
{
	CameraMoveRatio = std::lerp(CameraMoveRatio, 1.0f, 3.0f * _Delta);
	CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition() + float4{ 0.0f, 20.0f }) * CameraMoveRatio;

	if (0.99f < CameraMoveRatio)
	{
		ChangeState(BODY_STATE::Shouting);
		return;
	}
}

void ColossusBody::ShoutingUpdate(float _Delta)
{
	if (true == HeadRenderer->IsCurAnimationEnd())
	{
		Hand::ModeSwitchIsAbleValue = true;
		ChangeState(BODY_STATE::Idle);
		return;
	}

	ZoomRatio = std::lerp(ZoomRatio, 0.8f, 5.0f * _Delta);
	CameraManager::AddCameraZoomFromBoss = ZoomRatio;

	ShakingScreen(_Delta);
}

void ColossusBody::IdleUpdate(float _Delta)
{
	if (true == IsWeaknessHitByArrow)
	{
		ChangeState(BODY_STATE::Hit);
		return;
	}

	Levitaion(_Delta);
	ShakingScreen(_Delta);
}

void ColossusBody::HitUpdate(float _Delta)
{
	if (ARROW_STATE::PickUp == EnymeArrow->GetCurState())
	{
		LeftHand->ChangeState(HAND_STATE::Death);
		RightHand->ChangeState(HAND_STATE::Death);
		ChangeState(BODY_STATE::Death);
	}
}

void ColossusBody::DeathUpdate(float _Delta)
{

}

