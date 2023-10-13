#include "PreCompile.h"
#include "Heart.h"

void Heart::InSludgeStart()
{
	Renderer->ChangeAnimation("InSludge");
}

void Heart::IdleStart()
{
	Renderer->ChangeAnimation("Idle");
}

void Heart::JumpStart()
{
	Renderer->ChangeAnimation("Jump");
	JumpStartPos = Transform.GetLocalPosition();
	GravityValue = 400.0f;
	Collision->Off();
}

void Heart::FallStart()
{
	Collision->Off();
}

void Heart::LandingStart()
{
	Renderer->ChangeAnimation("Landing");
	Collision->On();
}

void Heart::DeathStart()
{
	Renderer->ChangeAnimation("Death");
}


void Heart::InSludgeUpdate(float _Delta)
{

}

void Heart::IdleUpdate(float _Delta)
{
	if (0.5f > JumpCooldown)
	{
		JumpCooldown += _Delta;
	}
	else
	{
		JumpCooldown = 0.0f;
		ChangeState(HEART_STATE::Jump);
	}
}

void Heart::JumpUpdate(float _Delta)
{
	if (0.0f > GravityValue)
	{
		ChangeState(HEART_STATE::Fall);
		return;
	}

	if (1 <= Renderer->GetCurIndex())
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
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(HEART_STATE::Idle);
		return;
	}
}

void Heart::DeathUpdate(float _Delta)
{

}