#include "PreCompile.h"
#include "Player.h"

#include <cmath>

///////  Start  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::IdleStart()
{
	SetAnimByDir("Idle");
}

void Player::MoveStart()
{
}

void Player::StopStart()
{
	if (true == IsRunning)
	{
		DecelerationRatio = 1.0f;
	}
	else
	{
		DecelerationRatio = 0.5f;
	}
	
	SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
}

void Player::RollStart()
{
	IsRollingBlocked = false;
	DecelerationRatio = 0.8f;
	SetAnimByDir("Roll");
}

void Player::BlockedStart()
{
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
		ChangeState(PLAYER_STATE::Move);
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

void Player::MoveUpdate(float _Delta)
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

	// Move Check
	if(true == MoveCheck())
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
		if (true == IsRunning)
		{
			MovePos *= RunForce;
			SetAnimByDir("Run", BodyRenderer->GetCurIndex());
		}
		else
		{
			SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
		}

		if (true == DebugingMode)
		{
			MovePos *= DebugModeForce;
		}

		Transform.AddLocalPosition(MovePos);
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
		ChangeState(PLAYER_STATE::Move);
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
		if (false == CurDirColCheck())
		{
			Transform.AddLocalPosition(MovePos);
		}
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

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		IsRollOnCooldown = true;
		ChangeState(PLAYER_STATE::Stop);
		return;
	}

	float4 MovePos = PlayerDirDeg * DefaultSpeed * RollForce * _Delta;
	if (false == IsRollingBlocked &&
		true == CurDirColCheck())
	{
		IsRollingBlocked = true;
		SetAnimByDir("Roll", 0, true);
	}

	if (true == IsRollingBlocked)
	{
		// incidence, reflection 추가하기
		MovePos = -MovePos * DecelerationRatio;
		Deceleration(5.0f * _Delta);
	}

	Transform.AddLocalPosition(MovePos);
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
