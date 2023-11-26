#include "PreCompile.h"
#include "Hand.h"


void Hand::SleepStart()
{
	ModeSwitchIsAbleValue = false;
	FloorCheckPos = Transform.GetLocalPosition();

	if (HAND_STATE::Death != PrevState)
	{
		ChangeAnimaion("Idle");
	}
}

void Hand::HideStart()
{
	Radian = GameEngineMath::PI;
	SetHideCollision();

	MoveRatio = 0.0f;
	if ("InHover" == BodyRenderer->CurAnimation()->AnimationName ||
		"Idle" == BodyRenderer->CurAnimation()->AnimationName)
	{
		ChangeAnimaion("InHide");
	}

	ShadowStandardScale = { 176.0f, 176.0f , 1.0f };
	ShadowScaleConstant = 10.0f;

	MoveSpeed = 10.0f;
}

void Hand::HoverStart()
{
	AllCollisionOff();

	MoveRatio = 0.0f;
	HoverTimer = 0.0f;
	ModeSwitchIsAbleValue = false;
	if ("InHide" == BodyRenderer->CurAnimation()->AnimationName)
	{
		ChangeAnimaion("InHover");
	}

	ShadowStandardScale = { 128.0f, 128.0f , 1.0f };
	ShadowScaleConstant = 3.0f;

	MoveSpeed = 20.0f;
}

void Hand::FallStart()
{
	GravityValue = -1000.0f;
}

void Hand::LandStart()
{
	CSObj.Reset();

	FistAttackPlayer.RandomPlay();
	SetLandCollision();
	LandTimer = 0.0f;
}


void Hand::HitStart()
{
}

void Hand::DeathStart()
{
	Collision->On();
	GravityValue = 0.0f;
	GravityForce = 1200.0f;
	ShadowStandardScale = { 128.0f, 128.0f , 1.0f };
	ShadowScaleConstant = 3.0f;
}


void Hand::SleepUpdate(float _Delta)
{

}

void Hand::HideUpdate(float _Delta)
{
	if (MinHeignt + FloorCheckPos.Y > Transform.GetLocalPosition().Y)
	{
		Transform.AddLocalPosition({ 0.0f, 100.0f * _Delta });
	}
	else if (false == Collision->IsUpdate())
	{
		Collision->On();
	}

	Levitaion(_Delta);
	SetMoveDir(FloorCheckPos, HidePos);
	MoveToPlayer(_Delta, HidePos);
}

void Hand::HoverUpdate(float _Delta)
{
	if (HoverCoolTime < HoverTimer)
	{
		ChangeState(HAND_STATE::Fall);
		float4 CurPos = Transform.GetLocalPosition();
		CurPos.Y = MaxHeight + FloorCheckPos.Y;
		Transform.SetLocalPosition(CurPos);
	}

	HoverTimer += _Delta;

	if (MaxHeight + FloorCheckPos.Y > Transform.GetLocalPosition().Y)
	{
		Transform.AddLocalPosition({ 0.0f, 250.0f * _Delta });
	}

	HoverRotationUpdate(_Delta);
	SetMoveDir(FloorCheckPos);
	MoveToPlayer(_Delta, EnymePlayer->Transform.GetLocalPosition() + float4{0.0f, -8.0f});

	CSObj.ShakingScreen(_Delta);
}

void Hand::FallUpdate(float _Delta)
{
	FallRotationUpdate(_Delta);
	Gravity(_Delta);
}

void Hand::LandUpdate(float _Delta)
{
	if (LandCoolTime < LandTimer)
	{
		ModeSwitchIsAbleValue = true;

		if (false == AttackModeIsSwitch)
		{
			ChangeState(HAND_STATE::Hover);
			return;
		}
	}
	else
	{
		LandTimer += _Delta;
	}
	CSObj.ShakingScreen(_Delta);
}

void Hand::HitUpdate(float _Delta)
{

}

void Hand::DeathUpdate(float _Delta)
{
	if (FloorCheckPos.Y > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = FloorCheckPos.Y;
		Transform.SetLocalPosition(MovePos);

		ChangeState(HAND_STATE::Sleep);
		return;
	}

	FallRotationUpdate(_Delta);
	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);

}
