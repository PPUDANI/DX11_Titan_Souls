#include "PreCompile.h"
#include "Player.h"

#include <cmath>

void Player::IdleStart()
{
	ChangeDirCoolDownTimer = 0.0f;
	SetAnimation("Idle");
}

void Player::WalkStart()
{
	SetAnimation("Walk");
}

void Player::RunStart()
{
	SetAnimation("Run");
}

void Player::StopStart()
{
	SetAnimation("Walk", BodyRenderer->GetCurIndex());
}

void Player::RollStart()
{
	RollCooldownOn = true;
	SetAnimation("Roll");
}

void Player::AimStart()
{
	SetAnimation("Aim");
}

void Player::ShotStart()
{
	SetAnimation("Shot");
}

void Player::DeathStart()
{
	SetAnimation("Death");
}


void Player::IdleUpdate(float _Delta)
{
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
		ChangeState(PLAYER_STATE::Roll);
		return;
	}
}

void Player::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::LeftUp, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::RightUp, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::LeftDown, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::RightDown, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		SetDir(PLAYER_DIRECTION::Up, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::Left, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		SetDir(PLAYER_DIRECTION::Down, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::Right, _Delta);
		MovePos = PlayerDirDeg * DefaultSpeed * _Delta;
	}
	else
	{
		ChangeState(PLAYER_STATE::Stop);
		return;
	}

	// 구르기
	if (true == GameEngineInput::IsDown(VK_SPACE) && false == RollCooldownOn)
	{
		ChangeState(PLAYER_STATE::Roll);
		return;
	}

	// 달리기
	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		MovePos *= RunForce;
		Transform.AddLocalPosition(MovePos);
		SetAnimation("Run", BodyRenderer->GetCurIndex());
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
		SetAnimation("Walk", BodyRenderer->GetCurIndex());
	}
}

void Player::RunUpdate(float _Delta)
{

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
		ChangeState(PLAYER_STATE::Roll);
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
		RollCooldownOn = true;
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
