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
	SetAnimByDir("Walk");
}

void Player::RollingStart()
{
	IsRollingingBlocked = false;
	DecelerationValue = 1.0f;
	SetAnimByDir("Rolling");
}

void Player::BlockedStart()
{
	SetAnimByDir("Blocked", BodyRenderer->GetCurIndex());
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
}

void Player::ReturningStart()
{
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

	// Rolling Check
	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		if (true == HasArrow())
		{
			ChangeState(PLAYER_STATE::Aim);
			return;
		}
		else
		{
			ChangeState(PLAYER_STATE::Returning);
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

	// Rolling Check
	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		if (true == HasArrow())
		{
			ChangeState(PLAYER_STATE::Aim);
			return;
		}
		else
		{
			ChangeState(PLAYER_STATE::Returning);
			return;
		}
	}

	// Move Check
	if (true == MoveCheck())
	{
		float4 MovePos = PlayerDirDeg * DefaultSpeed;
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

void Player::RollingUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K'))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		IsRollingOnCooldown = true;
		ChangeState(PLAYER_STATE::Stop);
		return;
	}

	if (true == CurDirColCheck())
	{
		IsRollingingBlocked = true;
		DirSpecularReflection();
		// 임시 애니메이션
		SetAnimByDir("Rolling", BodyRenderer->GetCurIndex(), true);
	}

	float4 MovePos = PlayerDirDeg * DefaultSpeed * RollingForce;

	if (true == IsRollingingBlocked)
	{
		// Specular Reflection 추가하기
		MovePos *= DecelerationValue;
		Deceleration(5.0f * _Delta);
	}

	Transform.AddLocalPosition(MovePos * _Delta);
}

void Player::BlockedUpdate(float _Delta)
{
	if (true == MoveCheck())
	{
		ChangeState(PLAYER_STATE::Move);
	}

	// Aim Check
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		if (true == HasArrow())
		{
			ChangeState(PLAYER_STATE::Aim);
			return;
		}
		else
		{
			ChangeState(PLAYER_STATE::Returning);
			return;
		}
	}

	if (true == MoveCheckInIdle())
	{
		SetAnimByDir("Blocked");
	}
	else
	{
		ChangeState(PLAYER_STATE::Idle);
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
	if (true == MoveCheckInIdle())
	{
		ChangeState(PLAYER_STATE::Move);
		return;
	}

	// Rolling Check
	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		if (true == HasArrow())
		{
			ChangeState(PLAYER_STATE::Aim);
			return;
		}
		else
		{
			ChangeState(PLAYER_STATE::Returning);
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
	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	AimDirectionUpdate();
	SetAnimByDir("Aim");
}

void Player::ReturningUpdate(float _Delta)
{
	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	if (true == HasArrow())
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	AimDirectionUpdate();
	SetAnimByDir("Returning");
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
