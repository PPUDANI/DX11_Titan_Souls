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

void Player::RollStart()
{
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

}

void Player::WalkUpdate(float _Delta)
{

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::LeftUp, _Delta);
		//CurDir = PLAYER_DIRECTION::LeftUp;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::RightUp, _Delta);
		//CurDir = PLAYER_DIRECTION::RightUp;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::LeftDown, _Delta);
		//CurDir = PLAYER_DIRECTION::LeftDown;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::RightDown, _Delta);
		//CurDir = PLAYER_DIRECTION::RightDown;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		SetDir(PLAYER_DIRECTION::Up, _Delta);
		//CurDir = PLAYER_DIRECTION::Up;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		SetDir(PLAYER_DIRECTION::Left, _Delta);
		//CurDir = PLAYER_DIRECTION::Left;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		SetDir(PLAYER_DIRECTION::Down, _Delta);
		//CurDir = PLAYER_DIRECTION::Down;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		SetDir(PLAYER_DIRECTION::Right, _Delta);
		//CurDir = PLAYER_DIRECTION::Right;
		MovePos = MoveToDir(DefaultSpeed * _Delta);
	}
	else
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	// 구르기
	if (true == GameEngineInput::IsPress(VK_SPACE) && false == IsRollOnCooldown)
	{
		ChangeState(PLAYER_STATE::Roll);
		return;
	}

	// 달리기
	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		MovePos *= SpeedUp;
		Transform.AddLocalPosition(MovePos);
		SetAnimation("Run");
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
		SetAnimation("Walk");
	}
}

void Player::RunUpdate(float _Delta)
{

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
		MovePos = MoveToDir(RollSpeed * _Delta);
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
