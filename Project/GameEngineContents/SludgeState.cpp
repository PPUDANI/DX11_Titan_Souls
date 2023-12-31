#include "PreCompile.h"
#include "Sludge.h"


void Sludge::IdleStart()
{
	JumpCooldown = 0.0f;
	MaxScale = 306.0f;
	MinScale = 206.0f;
	LerpRange = 0.95f;
	MoveSpeed = DefaultMoveSpeed * (1.0f + DividedCount * 0.2f);
}

void Sludge::JumpStart()
{
	JumpStartPos = Transform.GetLocalPosition();
	ReadyToJump = false;
	MaxScale = 386.0f;
	MinScale = 126.0f;
	LerpRange = 0.96f;
	GravityValue = 600.0f;

	GameEngineRandom Inst;
	static int Count = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
	JumpChargeTime = Inst.RandomFloat(0.87f, 0.93f);
}

void Sludge::FallStart()
{
	MaxScale = 366.0f;
	MinScale = 146.0f;
}

void Sludge::LandingStart()
{
	switch (DividedCount)
	{
	case 0:
		Division0LandPlayer.RandomPlay();
		break;
	case 1:
		Division1LandPlayer.RandomPlay();
		break;
	case 2:
		Division2LandPlayer.RandomPlay();
		break;
	case 3:
		Division3LandPlayer.RandomPlay();
		break;
	default:
		break;
	}
	Collision->On();

	MaxScale = 366.0f;
	MinScale = 146.0f;

	LerpRange = 0.97f;

	CSObj.Reset();
	CSObj.SetLerpMax(10.0f - DividedCount);
}

void Sludge::DivisionStart()
{
	SlicePlayer.RandomPlay();

	Collision->Off();

	MaxScale = 346.0f;
	MinScale = 166.0f;
	MoveSpeed = DefaultMoveSpeed * (1.0f - DividedCount * 0.1f);
	LerpRange = 0.92f;
	BodyRenderer->ChangeAnimation("Hit", true);

	GameEngineRandom Inst;
	static int Count = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
	GravityValue = Inst.RandomFloat(400.0f, 600.0f);
}


void Sludge::IdleUpdate(float _Delta)
{
	GameEngineRandom Inst;
	static int Count = 0;

	if (2 >= DividedCount)
	{
		CSObj.ShakingScreen(_Delta);
	}

	if (SLUDGE_STATE::Increase == ExpandDir)
	{
		IncreaseY((5.0f + static_cast<float>(DividedCount)) * _Delta);
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
		DecreaseY((3.0f + static_cast<float>(DividedCount)) * _Delta);
		if (MaxScale * JumpChargeTime < RenderScale.X)
		{
			if (false == FindPlayer)
			{
				if (0 == DividedCount)
				{
					SetMoveDirRandom(JumpStartPos, 180.0f);
				}
				else
				{
					SetMoveDirRandom(JumpStartPos, 70.0f);
				}
				
			}
			else
			{
				GameEngineRandom Inst;
				static int Count = 0;
				Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
				int RandonNum = Inst.RandomInt(0, 1);

				if (0 == RandonNum)
				{
					SetMoveDirRandom(JumpStartPos, 30.0f);
				}
				else if (1 == RandonNum)
				{
					SetMoveDir(JumpStartPos);
				}
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

	if (2 >= DividedCount)
	{
		CSObj.ShakingScreen(_Delta);
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
