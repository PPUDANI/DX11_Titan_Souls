#include "PreCompile.h"
#include "Hand.h"


void Hand::SleepStart()
{
	FloorCheckPos = Transform.GetLocalPosition();
	Renderer->ChangeAnimation("Idle");
}

void Hand::HideStart()
{
	Renderer->ChangeAnimation("InHide");
}

void Hand::HoverStart()
{
	CollisionOff();
	HoverTimer = 0.0f;
	ModeSwitchIsAbleValue = false;
	if (HAND_STATE::Hide == PrevState)
	{
		Renderer->ChangeAnimation("InHover");
	}
}

void Hand::FallStart()
{
	GravityValue = -700.0f;
}

void Hand::LandStart()
{
	CollisionOn();
	LandTimer = 0.0f;
}


void Hand::SleepUpdate(float _Delta)
{

}

void Hand::HideUpdate(float _Delta)
{
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
		Transform.AddLocalPosition({ 0.0f, 300.0f * _Delta });
	}

	SetMoveDir(FloorCheckPos);
	MoveToPlayer(_Delta, EnymePlayer->Transform.GetLocalPosition());
}

void Hand::FallUpdate(float _Delta)
{
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
