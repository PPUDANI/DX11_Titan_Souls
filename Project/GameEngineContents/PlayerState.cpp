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
	SetAnimByDir("Walk");
}

void Player::StopStart()
{
	DecelerationValue = 0.5f;
	SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
}

void Player::RollStart()
{
	SetAnimByDir("Roll");
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
	DecelerationValue = 0.5f;
	SetAnimByDir("Death");
}

void Player::SpawnStart()
{
	SetDirection(PLAYER_DIRECTION::Up);
	BodyRenderer->ChangeAnimation("Spawn");
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
		ChangeState(PLAYER_STATE::Walk);
		return;
	}

	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCheck())
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

	// Walk Controll
	float4 MovePos = float4::ZERO;
	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightDown);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else
	{
		ChangeState(PLAYER_STATE::Stop);
		return;
	}

	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCheck())
		{
			return;
		}
	}

	// Run Check
	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		MovePos *= RunForce;
		Transform.AddLocalPosition(MovePos);
		SetAnimByDir("Run", BodyRenderer->GetCurIndex());
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
		SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
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
		ChangeState(PLAYER_STATE::Walk);
		return;
	}
	
	// Roll Check
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (true == RollCheck())
		{
			return;
		}
	}

	// Deceleration
	if (0.0f == DecelerationValue)
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationValue * _Delta;
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
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		MovePos = PlayerDirDeg * DefaultSpeed * RollForce * _Delta;
		Transform.AddLocalPosition(MovePos);
	}
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
		ChangeState(PLAYER_STATE::Spawn);
		return;
	}

	// Deceleration
	if (0.0f != DecelerationValue)
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationValue * _Delta;
		Transform.AddLocalPosition(MovePos);
		Deceleration(5.0f * _Delta);
	}
}

void Player::SpawnUpadte(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(PLAYER_STATE::Idle);
	}
}
