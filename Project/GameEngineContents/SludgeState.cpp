#include "PreCompile.h"
#include "Sludge.h"


void Sludge::IdleStart()
{
	JumpCooldown = 0.0f;
	MaxScale = 316.0f;
	MinScale = 196.0f;
	LerpRange = 0.9f;
}

void Sludge::JumpStart()
{
	JumpStartPos = Transform.GetLocalPosition();
	GravityValue = 600.0f;
	ReadyToJump = false;

	MaxScale = 386.0f;
	MinScale = 126.0f;

	LerpRange = 0.95f;
}

void Sludge::FallStart()
{
	MaxScale = 316.0f;
	MinScale = 196.0f;
}

void Sludge::LandingStart()
{
	MaxScale = 386.0f;
	MinScale = 126.0f;

	LerpRange = 0.95f;
}

void Sludge::DeathStart()
{
}


void Sludge::IdleUpdate(float _Delta)
{

	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(3.0f * _Delta);
	}
	if (SLUDGE_STATE::Decrease == ExpandDir)
	{
		ChangeState(JUMPBOSS_STATE::Jump);
	}
}

void Sludge::JumpUpdate(float _Delta)
{
	if (0.0f > GravityValue)
	{
		ChangeState(JUMPBOSS_STATE::Fall);
		return;
	}

	if (false == ReadyToJump)
	{
		DecreaseY(4.0f * _Delta);
		if (MaxScale * 0.9f < RenderScale.X)
		{
			MaxScale = 346.0f;
			MinScale = 166.0f;
			LerpRange = 0.87f;
			ReadyToJump = true;
		}
	}
	else
	{
		if (SLUDGE_STATE::Increase == ExpandDir)
		{
			IncreaseY(6.0f * _Delta);
		}
		else
		{
			DecreaseY(6.0f * _Delta);
		}
		MoveToPlayer(_Delta);
		Gravity(_Delta);
	}

}

void Sludge::FallUpdate(float _Delta)
{
	if (SLUDGE_STATE::Decrease == ExpandDir)
	{
		DecreaseY(4.0f * _Delta);
	}
	else if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(4.0f * _Delta);
	}

	MoveToPlayer(_Delta);
	Gravity(_Delta);
}

void Sludge::LandingUpdate(float _Delta)
{
	DecreaseY(8.0f * _Delta);
	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		ChangeState(JUMPBOSS_STATE::Idle);
	}
}

void Sludge::DeathUpdate(float _Delta)
{

}
