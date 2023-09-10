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
		RollCheck();
		return;
	}
}

void Player::WalkUpdate(float _Delta)
{
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
		RollCheck();
		return;
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
	static float StopTimer = 0.0f;

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
	
	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		RollCheck();
		return;
	}

	if(0.3f < StopTimer)
	{
		StopTimer = 0.0f;
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		StopTimer += _Delta;
		float4 MovePos = PlayerDirDeg * DefaultSpeed * StopForce * _Delta;
		Transform.AddLocalPosition(MovePos);
	}
}

void Player::RollUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(PLAYER_STATE::Idle);
		IsRollOnCooldown = true;
		return;
	}
	else
	{
		MovePos = PlayerDirDeg * DefaultSpeed * RollForce * _Delta;
	}

	Transform.AddLocalPosition(MovePos);
}

void Player::AimUpdate(float _Delta)
{

}

void Player::ShotUpdate(float _Delta)
{

}

void Player::DeathUpdate(float _Delta)
{

}

void Player::SpawnUpadte(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(PLAYER_STATE::Idle);
	}
}
