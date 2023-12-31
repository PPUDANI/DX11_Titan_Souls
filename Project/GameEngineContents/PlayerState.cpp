#include "PreCompile.h"
#include "Player.h"

#include <cmath>

///////  Start  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::IdleStart()
{
	PrevStepInex = 0;
	BodyCollision->On();
	SetAnimByDir("Idle");
}

void Player::MoveStart()
{
	SetAnimByDir("Walk");
}

void Player::RollingStart()
{
	EffectSoundPlay("Roll.ogg");

	IsRollingBlocked = false;
	DecelerationValue = 1.0f;
	SetAnimByDir("Rolling");
}

void Player::BlockedStart()
{
	SetAnimByDir("Blocked", BodyRenderer->GetCurIndex());
}

void Player::StopStart()
{
	DecelerationValue = 1.0f;
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
	DecelerationValue = 1.0f;
	SetAnimByDir("Death");
}

void Player::StandUpStart()
{
	SetDirection(PLAYER_DIRECTION::Up);
	BodyRenderer->ChangeAnimation("StandUp");
	BowRenderer->ChangeAnimation("StandUp");
	ArrowInBagRenderer->ChangeAnimation("StandUp");
}

void Player::EnterLevelStart()
{
	EnterTimer = 0.0f;
	BodyCollision->Off();
	BodyRenderer->ChangeAnimation("EnterLevel");
	BowRenderer->ChangeAnimation("EnterLevel");
	ArrowInBagRenderer->ChangeAnimation("EnterLevel");
	
	SetDirection(PLAYER_DIRECTION::Up);
}

void Player::ExitLevelStart()
{
	ExitTimer = 0.0f;
	BodyCollision->Off();
	BodyRenderer->ChangeAnimation("ExitLevel");
	BowRenderer->ChangeAnimation("ExitLevel");
	ArrowInBagRenderer->ChangeAnimation("ExitLevel");

	SetDirection(PLAYER_DIRECTION::Down);
}


void Player::EndingLevelStart()
{
	EnterTimer = 0.0f;
	BodyCollision->Off();
	BodyRenderer->ChangeAnimation("EnterLevel");
	BowRenderer->ChangeAnimation("EnterLevel");
	ArrowInBagRenderer->ChangeAnimation("EnterLevel");

	SetDirection(PLAYER_DIRECTION::Up);
}

///////  Update  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::IdleUpdate(float _Delta)
{
	// Death Check
	if (true == GameEngineInput::IsPress('K', this))
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
	if (true == GameEngineInput::IsPress(VK_SPACE, this))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	AimCheck();
}

void Player::MoveUpdate(float _Delta)
{
	StepSoundPlay();
	// Death Check
	if (true == GameEngineInput::IsPress('K', this))
	{
		ChangeState(PLAYER_STATE::Death);
		return;
	}

	// Rolling Check
	if (true == GameEngineInput::IsPress(VK_SPACE, this))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	AimCheck();

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
	if (true == GameEngineInput::IsPress('K', this))
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
		EffectSoundStop();
		EffectSoundPlay("Roll_bash.ogg");
		IsRollingBlocked = true;
		DirSpecularReflection();
		// 임시 애니메이션
		SetAnimByDir("Rolling", BodyRenderer->GetCurIndex(), true);
	}

	float4 MovePos = PlayerDirDeg * DefaultSpeed * RollingForce;

	if (true == IsRollingBlocked)
	{
		// Specular Reflection 추가하기
		DecelerationValue = std::lerp(DecelerationValue, 0.0f, 1.0f - std::pow(0.5f, 5.0f * _Delta));
		MovePos *= DecelerationValue;
	}

	Transform.AddLocalPosition(MovePos * _Delta);

	if (RollingDustCoolTime < RollingDustCoolTimer)
	{
		RollingDustCoolTimer -= RollingDustCoolTime;
		DustPatricle();
	}
	else
	{
		RollingDustCoolTimer += _Delta;
	}
}

void Player::BlockedUpdate(float _Delta)
{
	if (true == MoveCheck())
	{
		ChangeState(PLAYER_STATE::Move);
	}

	// Aim Check
	AimCheck();

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
	if (true == GameEngineInput::IsPress('K', this))
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
	if (true == GameEngineInput::IsPress(VK_SPACE, this))
	{
		if (true == RollingCollDownCheck())
		{
			return;
		}
	}

	// Aim Check
	AimCheck();

	// Deceleration
	if (0.1f > DecelerationValue)
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}
	else
	{
		if (true == IsRunning)
		{
			DecelerationValue = std::lerp(DecelerationValue, 0.0f, 1.0f - std::pow(0.5f, 3.0f * _Delta));
		}
		else
		{
			DecelerationValue = std::lerp(DecelerationValue, 0.0f, 1.0f - std::pow(0.5f, 10.0f * _Delta));
		}

		float4 MovePos = PlayerDirDeg * DefaultSpeed * DecelerationValue;
		if (false == CurDirColCheck())
		{
			Transform.AddLocalPosition(MovePos * _Delta);
		}
	}

}

void Player::AimUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RBUTTON, this))
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON, this))
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	AimDirectionUpdate();
	SetAnimByDir("Aim");
}

void Player::ReturningUpdate(float _Delta)
{
	if (true == GameEngineInput::IsUp(VK_LBUTTON, this))
	{
		ChangeState(PLAYER_STATE::Idle);
		return;
	}

	if (ARROW_STATE::PickUp == MyArrow->GetCurState())
	{
		ChangeState(PLAYER_STATE::Idle);
		ArrowInBagRenderer->On();
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
		DecelerationValue = std::lerp(DecelerationValue, 0.0f, 1.0f - std::pow(0.5f, 8.0f * _Delta));
	}
}

void Player::StandUpUpdate(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(PLAYER_STATE::Idle);
	}
}

void Player::EnterLevelUpdate(float _Delta)
{
	StepSoundPlay();
	if (1.5f < EnterTimer)
	{
		EnterTimer = 0.0f;
		ChangeState(PLAYER_STATE::Idle);
	}
	else
	{
		EnterTimer += _Delta;
	}

	float4 MovePos = float4::ZERO;
	MovePos.Y = 40.0f * _Delta;
	Transform.AddLocalPosition(MovePos);
}

void Player::ExitLevelUpdate(float _Delta)
{
	StepSoundPlay();
	if (1.5f < ExitTimer)
	{
		ExitTimer = 0.0f;
		ChangeState(PLAYER_STATE::Idle);
	}
	else
	{
		ExitTimer += _Delta;
	}

	float4 MovePos = float4::ZERO;
	MovePos.Y = -40.0f * _Delta;
	Transform.AddLocalPosition(MovePos);
}

void Player::EndingLevelUpdate(float _Delta)
{
	StepSoundPlay();
	if (5.0f < EnterTimer)
	{
		EnterTimer = 0.0f;
		ChangeState(PLAYER_STATE::Idle);
	}
	else
	{
		EnterTimer += _Delta;
	}

	float4 MovePos = float4::ZERO;
	MovePos.Y = 60.0f * _Delta;
	Transform.AddLocalPosition(MovePos);
}
