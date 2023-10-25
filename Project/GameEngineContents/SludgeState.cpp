#include "PreCompile.h"
#include "Sludge.h"


void Sludge::IdleStart()
{
	JumpCooldown = 0.0f;
	MaxScale = 306.0f;
	MinScale = 206.0f;
	LerpRange = 0.95f;
}

void Sludge::JumpStart()
{
	JumpStartPos = Transform.GetLocalPosition();
	ReadyToJump = false;
	MaxScale = 386.0f;
	MinScale = 126.0f;
	GravityValue = 600.0f;
	LerpRange = 0.96f;
}

void Sludge::FallStart()
{
	MaxScale = 366.0f;
	MinScale = 146.0f;
}

void Sludge::LandingStart()
{
	if (false == Collision->IsDeath())
	{
		Collision->On();
	}

	MaxScale = 366.0f;
	MinScale = 146.0f;

	LerpRange = 0.97f;
}

void Sludge::DivisionStart()
{
	if (false == Collision->IsDeath())
	{
		Collision->Off();
	}
	GravityValue = 500.0f;
	
	MaxScale = 346.0f;
	MinScale = 166.0f;

	LerpRange = 0.92f;
}


void Sludge::IdleUpdate(float _Delta)
{
	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY((5.0f + DividedCount) * _Delta);
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
			if (false == FindPlayer)
			{
				SetMoveDirRandom(JumpStartPos, 90.0f);
			}
			else
			{
				SetMoveDirRandom(JumpStartPos, 40.0f);
			}
			ReadyToJump = true;
			LerpRange = 0.8f;
			Collision->Off();
			return;
		}
	}
	else
	{
		if (SLUDGE_STATE::Increase == ExpandDir)
		{
			IncreaseY(4.0f * _Delta);
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

void Sludge::DivisionUpdate(float _Delta)
{
	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY(8.0f * _Delta);
	}
	else
	{
		DecreaseY(8.0f * _Delta);
	}

	MoveToPlayer(_Delta);
	Gravity(_Delta);
}
