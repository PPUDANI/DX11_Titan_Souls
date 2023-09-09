#include "PreCompile.h"
#include "Player.h"

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


void Player::IdleUpdate()
{
	if (true == GameEngineInput::IsDown('W') && true == GameEngineInput::IsDown('A'))
	{
		CurDir = PlayerDir::LeftUp;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('W') && true == GameEngineInput::IsDown('D'))
	{
		CurDir = PlayerDir::RightUp;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S') && true == GameEngineInput::IsDown('A'))
	{
		CurDir = PlayerDir::LeftDown;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S') && true == GameEngineInput::IsDown('D'))
	{
		CurDir = PlayerDir::RightDown;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('W'))
	{
		CurDir = PlayerDir::Up;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('A'))
	{
		CurDir = PlayerDir::Left;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('S'))
	{
		CurDir = PlayerDir::Down;
		ChangeState(PlayerState::Run);
		return;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CurDir = PlayerDir::Right;
		ChangeState(PlayerState::Run);
		return;
	}
}

void Player::RunUpdate()
{
	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		CurDir = PlayerDir::LeftUp;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		CurDir = PlayerDir::RightUp;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		CurDir = PlayerDir::LeftDown;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		CurDir = PlayerDir::RightDown;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		CurDir = PlayerDir::Up;
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		CurDir = PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		CurDir = PlayerDir::Down;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CurDir = PlayerDir::Right;
	}
	else
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	SetAnimation("Run");
}

void Player::RollUpdate()
{

}

void Player::AimUpdate()
{

}

void Player::ShotUpdate()
{

}

void Player::DeathUpdate()
{

}
