#include "PreCompile.h"
#include "ColossusBody.h"
#include "Hand.h"

void ColossusBody::SleepStart()
{
	Hand::ModeSwitchIsAbleValue = false;
	IsBodyHitByArrow = false;

	BodyCollision->Transform.SetLocalScale({ 128.0f, 64.0f, 1.0f });
	BodyCollision->Transform.SetLocalPosition({ 0.0f, 32.0f });
	Collision->Off();

	HeadRenderer->ChangeAnimation("Sleep");

	Speed = 2.0f;
	MovingHeight = 10.0f;
}

void ColossusBody::WakeUpStart()
{
	GameEngineInput::InputObjectOff(EnymePlayer);
	CameraManager::CalCameraPosFromArrowOff();
	CameraManager::CalCameraZoomFromArrowOff();
	CameraMoveRatio = 0.0f;
	HeadRenderer->ChangeAnimation("WakeUp");
}

void ColossusBody::ShoutingStart()
{
	EffectSoundPlay("Roar.ogg");
	HeadRenderer->ChangeAnimation("Shouting");

	CSObj.Reset();

	ZoomRatio = 1.0f;
	BodyLightRenderer->GetColorData().MulColor.A = 1.0f;
}

void ColossusBody::IdleStart()
{
	GameEngineInput::InputObjectOn(EnymePlayer);
	CameraManager::CalCameraPosFromArrowOn();
	CameraManager::CalCameraZoomFromArrowOn();


	BodyCollision->Transform.SetLocalPosition({ 0.0f, 80.0f });

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
	BodyCollision->Transform.SetLocalScale({ 128.0f, 64.0f, 1.0f });
	BodyCollision->Transform.SetLocalPosition({ 0.0f, 32.0f });
	Collision->Off();
	BodyLightRenderer->GetColorData().MulColor.A = 0.0f;
	HeadRenderer->ChangeAnimation("Death");
}

void ColossusBody::SleepUpdate(float _Delta)
{
	if (true == IsBodyHitByArrow)
	{
		ChangeState(BODY_STATE::WakeUp);
		return;
	}

	Breathing(_Delta);
}

void ColossusBody::WakeUpUpdate(float _Delta)
{
	CameraMoveRatio = std::lerp(CameraMoveRatio, 1.0f, 3.0f * _Delta);
	CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition() + float4{ 0.0f, 20.0f }) * CameraMoveRatio;

	if (0.999f < CameraMoveRatio)
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
	CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition() + float4{ 0.0f, 20.0f });
	CSObj.ShakingScreen(_Delta);
}

void ColossusBody::IdleUpdate(float _Delta)
{
	if (true == IsWeaknessHitByArrow)
	{
		ChangeState(BODY_STATE::Hit);
		return;
	}

	Breathing(_Delta);
	CSObj.ShakingScreen(_Delta);
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

