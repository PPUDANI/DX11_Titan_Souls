#include "PreCompile.h"
#include "Player.h"

#include <cmath>

///////  Start  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::IdleStart()
{
	SetAnimByDir("Idle");
}

void Player::WalkStart()
{

}

void Player::RunStart()
{
	KeepRunCoolDownTimer = 0.0f;
}

void Player::StopStart()
{
	if (PLAYER_STATE::Run == PrevState ||
		PLAYER_STATE::Roll == PrevState)
	{
		DecelerationRatio = 1.0f;
	}
	else if(PLAYER_STATE::Walk == PrevState)
	{
		DecelerationRatio = 0.5f;
	}
	
	SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
}

void Player::RollStart()
{
	SetAnimByDir("Roll");
}

void Player::BlockedStart()
{
	SetAnimByDir("Blocked");
}

void Player::AimStart()
{
	SetAnimByDir("Aim");
}

void Player::ShotStart()
{
	SetAnimByDir("Shot");
}

void Player::DeathStart()
{
	DecelerationRatio = 0.5f;
	SetAnimByDir("Death");
}

void Player::StandUpStart()
{
	SetDirection(PLAYER_DIRECTION::Up);
	BodyRenderer->ChangeAnimation("StandUp");
	BowRenderer->ChangeAnimation("StandUp");
	ArrowInBagRenderer->ChangeAnimation("StandUp");
}


///////  Update  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::IdleUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	// Walk Check
	if (true == GameEngineInput::IsPress('W') ||
		true == GameEngineInput::IsPress('A') ||
		true == GameEngineInput::IsPress('S') ||
		true == GameEngineInput::IsPress('D'))
	{
		if (true == GameEngineInput::IsPress(VK_SHIFT))
		{
			ChangeState(PLAYER_STATE::Run);
		}
		else
		{
			ChangeState(PLAYER_STATE::Walk);
		}
		return;
	}

	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCollDownCheck())
		{
			return;
		}
	}
}

void Player::WalkUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	// Run Check
	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		ChangeState(PLAYER_STATE::Run);
	}

	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCollDownCheck())
		{
			return;
		}
	}

	// Move Check
	if(true == MoveCheck())
	{
		float4 MovePos = float4::ZERO;
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
		Transform.AddLocalPosition(MovePos);
		SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
	}
	else
	{
		ChangeState(PLAYER_STATE::Stop);
		return;
	}
}

void Player::RunUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCollDownCheck())
		{
			return;
		}
	}

	// Keep Run Check
	if (false == GameEngineInput::IsPress(VK_SHIFT))
	{
		if (KeepRunCoolTime <= KeepRunCoolDownTimer)
		{
			KeepRunCoolDownTimer = 0.0f;
			ChangeState(PLAYER_STATE::Walk);
			return;
		}

		KeepRunCoolDownTimer += _Delta;
	}

	// Move Check
	if (true == MoveCheck())
	{
		float4 MovePos = float4::ZERO;
		MovePos = PlayerDirDeg * DefaultSpeed * RunForce * _Delta;
		Transform.AddLocalPosition(MovePos);
		SetAnimByDir("Run", BodyRenderer->GetCurIndex());
	}
	else
	{
		ChangeState(PLAYER_STATE::Stop);
		return;
	}
}

void Player::StopUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	// Walk Check
	if (true == GameEngineInput::IsPress('W') ||
		true == GameEngineInput::IsPress('A') ||
		true == GameEngineInput::IsPress('S') ||
		true == GameEngineInput::IsPress('D'))
	{
		if (true == GameEngineInput::IsPress(VK_SHIFT))
		{
			ChangeState(PLAYER_STATE::Run);
		}
		else
		{
			ChangeState(PLAYER_STATE::Walk);
		}
		return;
	}
	
	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCollDownCheck())
		{
			return;
		}
	}
	
	// Deceleration
	if (0.0f == DecelerationRatio)
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationRatio * _Delta;
		Transform.AddLocalPosition(MovePos);
		Deceleration(10.0f * _Delta);
	}
}

void Player::RollUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	float4 MovePos = float4::ZERO;
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		IsRollOnCooldown = true;
		ChangeState(PLAYER_STATE::Stop);
		return;
	}
	else
	{
		MovePos = PlayerDirDeg * DefaultSpeed * RollForce * _Delta;
		Transform.AddLocalPosition(MovePos);
	}
}

void Player::BlockedUpdate(float _Delta)
{

}

void Player::AimUpdate(float _Delta)
{

}

void Player::ShotUpdate(float _Delta)
{

}

void Player::DeathUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('R'))
	{
		Transform.SetLocalPosition({0.0f, 0.0f});
		ChangeState(PLAYER_STATE::StandUp);
		return;
	}

	// Deceleration
	if (0.0f != DecelerationRatio)
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationRatio * _Delta;
		Transform.AddLocalPosition(MovePos);
		Deceleration(5.0f * _Delta);
	}
}

void Player::StandUpUpadte(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(PLAYER_STATE::Idle);
	}
}
