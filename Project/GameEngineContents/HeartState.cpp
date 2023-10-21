#include "PreCompile.h"
#include "Heart.h"
#include "Sludge.h"

void Heart::InSludgeStart()
{
	BodyRenderer->ChangeAnimation("InSludge");
	Collision->Off();
}

void Heart::IdleStart()
{
	BodyRenderer->ChangeAnimation("Idle");
}

void Heart::JumpStart()
{
	BodyRenderer->ChangeAnimation("Jump");
	JumpStartPos = Transform.GetLocalPosition();
	GravityValue = 300.0f;
	Collision->Off();
}

void Heart::FallStart()
{
	Collision->Off();
}

void Heart::LandingStart()
{
	BodyRenderer->ChangeAnimation("Landing");
	Collision->On();
}

void Heart::DeathStart()
{
	BodyRenderer->ChangeAnimation("Death");
}


void Heart::InSludgeUpdate(float _Delta)
{
	if (nullptr == OwnerSludge)
	{
		ChangeState(JUMPBOSS_STATE::Idle);
		return;
	}
	Transform.SetLocalPosition(OwnerSludge->Transform.GetWorldPosition() + OwnerSludge->GetHeartPos());
}

void Heart::IdleUpdate(float _Delta)
{
	if (0.1f > JumpCooldown)
	{
		JumpCooldown += _Delta;
	}
	else
	{
		JumpCooldown = 0.0f;
		ChangeState(JUMPBOSS_STATE::Jump);
	}
}

void Heart::JumpUpdate(float _Delta)
{
	if (0.0f > GravityValue)
	{
		ChangeState(JUMPBOSS_STATE::Fall);
		return;
	}

	if (1 <= BodyRenderer->GetCurIndex())
	{
		MoveToPlayer(_Delta);
		Gravity(_Delta);
	}
}

void Heart::FallUpdate(float _Delta)
{
	MoveToPlayer(_Delta);
	Gravity(_Delta);
}

void Heart::LandingUpdate(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(JUMPBOSS_STATE::Idle);
		return;
	}
}

void Heart::DeathUpdate(float _Delta)
{

}

