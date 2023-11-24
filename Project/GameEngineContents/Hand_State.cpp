#include "PreCompile.h"
#include "Hand.h"


void Hand::SleepStart()
{
	ModeSwitchIsAbleValue = false;
	FloorCheckPos = Transform.GetLocalPosition();
	ChangeAnimaion("Idle");
}

void Hand::HideStart()
{
	Collision->On();
	MoveRatio = 0.0f;
	ChangeAnimaion("InHide");

	MoveSpeed = 0.03f;
}

void Hand::HoverStart()
{
	MoveRatio = 0.0f;
	AllCollisionOff();
	HoverTimer = 0.0f;
	ModeSwitchIsAbleValue = false;
	if (HAND_STATE::Hide == PrevState)
	{
		ChangeAnimaion("InHover");
	}
	MoveSpeed = 0.05f;
}

void Hand::FallStart()
{
	AllCollisionOn();
	GravityValue = -1000.0f;
}

void Hand::LandStart()
{
	AllCollisionOff();
	LandTimer = 0.0f;
}


void Hand::HitStart()
{
	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
}

void Hand::DeathStart()
{
	GravityValue = 0.0f;
	GravityForce = 1200.0f;
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
		Transform.AddLocalPosition({ 0.0f, 200.0f * _Delta });
	}

	HoverRotation(_Delta);
	SetMoveDir(FloorCheckPos);
	MoveToPlayer(_Delta, EnymePlayer->Transform.GetLocalPosition());
}

void Hand::FallUpdate(float _Delta)
{
	FallRotation(_Delta);
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
		}
	}
	else
	{
		LandTimer += _Delta;
	}
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

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);

}
