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

void Player::RollStart()
{
	IsRollingBlocked = false;
	DecelerationValue = 0.8f;
	SetAnimByDir("Roll");
}

void Player::BlockedStart()
{
}

void Player::StopStart()
{
	if (true == IsRunning)
	{
		DecelerationValue = 1.0f;
	}
	else
	{
		DecelerationValue = 0.5f;
	}

	SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
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
	if (true == MoveCheckInIdle())
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
	if (true == MoveCheck())
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * SpeedUpForce;
		if (true == IsRunning)
		{
			MovePos *= RunForce;
			SetAnimByDir("Run", BodyRenderer->GetCurIndex());
		}
		else
		{
			SetAnimByDir("Walk", BodyRenderer->GetCurIndex());
		}

		Transform.AddLocalPosition(MovePos * _Delta);
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

	if (true == CurDirColCheck())
	{
		IsRollingBlocked = true;
		DirSpecularReflection();
		// 임시 애니메이션
		SetAnimByDir("Roll", 0, true);
	}

	float4 MovePos = PlayerDirDeg * DefaultSpeed * RollForce;

	if (true == IsRollingBlocked)
	{
		// Specular Reflection 추가하기
		MovePos *= DecelerationValue;
		Deceleration(5.0f * _Delta);
	}

	Transform.AddLocalPosition(MovePos * _Delta);
}

void Player::BlockedUpdate(float _Delta)
{
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
	if (true == MoveCheckInIdle())
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
	if (0.0f == DecelerationValue)
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationValue;
		if (false == CurDirColCheck())
		{
			Transform.AddLocalPosition(MovePos * _Delta);
		}
		Deceleration(10.0f * _Delta);
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
	// Deceleration
	if (0.0f != DecelerationValue)
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationValue;
		Transform.AddLocalPosition(MovePos * _Delta);
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
