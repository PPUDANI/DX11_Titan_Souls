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
	MaxScale = 366.0f;
	MinScale = 146.0f;
}

void Sludge::LandingStart()
{
	Collision->On();
	MaxScale = 376.0f;
	MinScale = 136.0f;

	LerpRange = 0.95f;
}

void Sludge::DeathStart()
{
}


void Sludge::IdleUpdate(float _Delta)
{
	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY((3.0f + DividedCount) * _Delta);
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
		DecreaseY((3.0f + DividedCount) * _Delta);
		if (MaxScale * 0.9f < RenderScale.X)
		{
			SetMoveDir(JumpStartPos);
			LerpRange = 0.8f;
			ReadyToJump = true;
			Collision->Off();
		}
	}
	else
	{
		if (SLUDGE_STATE::Increase == ExpandDir)
		{
			IncreaseY(5.0f * _Delta);
		}
		else
		{
			DecreaseY(4.0f * _Delta);
		}
		MoveToPlayer(_Delta);
		Gravity(_Delta);
	}
}

void Sludge::FallUpdate(float _Delta)
{
	if (SLUDGE_STATE::Decrease == ExpandDir)
	{
		DecreaseY(2.5f * _Delta);
	}
	else if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(2.5f * _Delta);
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
