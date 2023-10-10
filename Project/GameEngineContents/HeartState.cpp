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
	StartYPos = Transform.GetLocalPosition().Y;
	GravityValue = 500.0f;
}

void Heart::FallStart()
{
}

void Heart::LandingStart()
{
	Renderer->ChangeAnimation("Landing");
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
	Gravity(_Delta);
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(HEART_STATE::Fall);
		return;
	}
}

void Heart::FallUpdate(float _Delta)
{
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