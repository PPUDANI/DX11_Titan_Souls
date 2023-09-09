#include "PreCompile.h"
#include "Player.h"

#include <cmath>

void Player::IdleStart()
{
	SetAnimation("Idle");
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
	if (true == GameEngineInput::IsDown('W') && true == GameEngineInput::IsDown('A'))
	{
		CurDir = PLAYER_DIRECTION::LeftUp;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('W') && true == GameEngineInput::IsDown('D'))
	{
		CurDir = PLAYER_DIRECTION::RightUp;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S') && true == GameEngineInput::IsDown('A'))
	{
		CurDir = PLAYER_DIRECTION::LeftDown;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S') && true == GameEngineInput::IsDown('D'))
	{
		CurDir = PLAYER_DIRECTION::RightDown;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('W'))
	{
		CurDir = PLAYER_DIRECTION::Up;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('A'))
	{
		CurDir = PLAYER_DIRECTION::Left;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S'))
	{
		CurDir = PLAYER_DIRECTION::Down;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CurDir = PLAYER_DIRECTION::Right;
		ChangeState(PLAYER_STATE::Run);
		return;
	}
}

void Player::RunUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		CurDir = PLAYER_DIRECTION::LeftUp;
		MovePos = float4::GetUnitVectorFromDeg(45.0f);
		MovePos *= {-PlayerSpeed * _Delta, PlayerSpeed * _Delta};
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		CurDir = PLAYER_DIRECTION::RightUp;
		MovePos = float4::GetUnitVectorFromDeg(45.0f);
		MovePos *= { PlayerSpeed * _Delta , PlayerSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		CurDir = PLAYER_DIRECTION::LeftDown;
		MovePos = float4::GetUnitVectorFromDeg(45.0f);
		MovePos *= { -PlayerSpeed * _Delta , -PlayerSpeed  * _Delta };
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		CurDir = PLAYER_DIRECTION::RightDown;
		MovePos = float4::GetUnitVectorFromDeg(45.0f);
		MovePos *= { PlayerSpeed  * _Delta , -PlayerSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		CurDir = PLAYER_DIRECTION::Up;
		MovePos = { 0.0f, PlayerSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		CurDir = PLAYER_DIRECTION::Left;
		MovePos = { -PlayerSpeed * _Delta , 0.0f };
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		CurDir = PLAYER_DIRECTION::Down;
		MovePos = { 0.0f, -PlayerSpeed * _Delta };
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CurDir = PLAYER_DIRECTION::Right;
		MovePos = { PlayerSpeed * _Delta , 0.0f };
	}
	else
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		MovePos *= 2.0f;
	}

	Transform.AddLocalPosition(MovePos);
	SetAnimation("Run");
}

void Player::RollUpdate(float _Delta)
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

}
