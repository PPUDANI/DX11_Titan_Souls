#include "PreCompile.h"
#include "Sludge.h"


void Sludge::IdleStart()
{
	JumpCooldown = 0.0f;
	MaxScale = 300.0f;
}

void Sludge::JumpStart()
{
	JumpStartPos = Transform.GetLocalPosition();
	GravityValue = 600.0f;
	GravityMaxValue = 600.0f;
	ReadyToJump = false;

	MaxScale = 340.0f;
}

void Sludge::FallStart()
{
	MaxScale = 300.0f;
}

void Sludge::LandingStart()
{
	MaxScale = 340.0f;
}

void Sludge::DeathStart()
{
}


void Sludge::IdleUpdate(float _Delta)
{
	if (0.5f > JumpCooldown)
	{
		JumpCooldown += _Delta;
	}
	else
	{
		ChangeState(JUMPBOSS_STATE::Jump);
	}

	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(1.2f * _Delta);
	}
	if (SLUDGE_STATE::Decrease == ExpandDir)
	{
	    DecreaseY(1.2f * _Delta);
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
		DecreaseY(1.5f * _Delta);
		if (MaxScale < RenderScale.X)
		{
			ReadyToJump = true;
		}
	}
	else
	{
		if (SLUDGE_STATE::Increase == ExpandDir)
		{
			IncreaseY(3.0f * _Delta);
		}
		else
		{
			DecreaseY(3.0f * _Delta);
		}
		MoveToPlayer(_Delta);
		Gravity(_Delta);
	}

}

void Sludge::FallUpdate(float _Delta)
{
	if (SLUDGE_STATE::Decrease == ExpandDir)
	{
		DecreaseY(1.5f * _Delta);
	}
	else if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(1.5f * _Delta);
	}

	MoveToPlayer(_Delta);
	Gravity(_Delta);
}

void Sludge::LandingUpdate(float _Delta)
{
	DecreaseY(4.0f * _Delta);
	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		ChangeState(JUMPBOSS_STATE::Idle);
	}
}

void Sludge::DeathUpdate(float _Delta)
{

}
