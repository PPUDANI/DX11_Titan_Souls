#include "PreCompile.h"
#include "Player.h"
#include "Arrow.h"
std::shared_ptr<Player> Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// Load Textures & Create Animations
	CreatePlayerbodyAnimation();
	CreateBowAnimation();
	CreateArrowInBagAnimation();

	ChangeState(PLAYER_STATE::StandUp);


}

void Player::Update(float _Delta)
{
	// Roll CoolDown Update
	if (true == IsRollOnCooldown)
	{
		RollCoolDownUpdate(_Delta);
	}

	// Change Diretion CoolDown Update
	if (true == IsChangeDirOnCooldown)
	{
		ChangeDirCoolDownUpdate(_Delta);
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		DebugMode = true;
	}

	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		KeepRunCoolDownTimer = 0.0f;
		IsRunning = true;
	}
	else
	{
		if (true == IsRunning)
		{
			KeepRunCoolDownUpdate(_Delta);
		}
	}
	

	// State Update
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case PLAYER_STATE::Move:
		MoveUpdate(_Delta);
		break;
	case PLAYER_STATE::Stop:
		StopUpdate(_Delta);
		break;
	case PLAYER_STATE::Roll:
		RollUpdate(_Delta);
		break;
	case PLAYER_STATE::Blocked:
		BlockedUpdate(_Delta);
		break;
	case PLAYER_STATE::Aim:
		AimUpdate(_Delta);
		break;
	case PLAYER_STATE::Shot:
		ShotUpdate(_Delta);
		break;
	case PLAYER_STATE::Death:
		DeathUpdate(_Delta);
		break;
	case PLAYER_STATE::StandUp:
		StandUpUpadte(_Delta);
		break;
	default:
		break;
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetWorldPosition());
}

void Player::ChangeState(PLAYER_STATE _State)
{
	PrevState = CurState;
	CurState = _State;
	
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleStart();
		break;
	case PLAYER_STATE::Move:
		MoveStart();
		break;
	case PLAYER_STATE::Stop:
		StopStart();
		break;
	case PLAYER_STATE::Roll:
		RollStart();
		break;
	case PLAYER_STATE::Blocked:
		BlockedStart();
		break;
	case PLAYER_STATE::Aim:
		AimStart();
		break;
	case PLAYER_STATE::Shot:
		ShotStart();
		break;
	case PLAYER_STATE::Death:
		DeathStart();
		break;
	case PLAYER_STATE::StandUp:
		StandUpStart();
		break;
	default:
		break;
	}
}

void Player::SetAnimByDir(std::string_view _AnimName, int _Frame /*= 0*/, bool _Force /*= false*/)
{
	std::string AnimationName = "";

	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		AnimationName += "Right_";
		break;
	case PLAYER_DIRECTION::RightUp:
		AnimationName += "RightUp_";
		break;
	case PLAYER_DIRECTION::Up:
		AnimationName += "Up_";
		break;
	case PLAYER_DIRECTION::LeftUp:
		AnimationName += "LeftUp_";
		break;
	case PLAYER_DIRECTION::Left:
		AnimationName += "Left_";
		break;
	case PLAYER_DIRECTION::LeftDown:
		AnimationName += "LeftDown_";
		break;
	case PLAYER_DIRECTION::Down:
		AnimationName += "Down_";
		break;
	case PLAYER_DIRECTION::RightDown:
		AnimationName += "RightDown_";
		break;
	default:
		break;
	}

	AnimationName += _AnimName;
	
	if (0 != _Frame)
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force, _Frame);
		BowRenderer->ChangeAnimation(AnimationName, _Force, _Frame);
		ArrowInBagRenderer->ChangeAnimation(AnimationName, _Force, _Frame);
	}
	else
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force);
		BowRenderer->ChangeAnimation(AnimationName, _Force);
		ArrowInBagRenderer->ChangeAnimation(AnimationName, _Force);
	}
}

void Player::SetDirection(PLAYER_DIRECTION _Dir)
{
	CurDir = _Dir;
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(0.0f);
		break;
	case PLAYER_DIRECTION::RightUp:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(45.0f);
		break;
	case PLAYER_DIRECTION::Up:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(90.0f);
		break;
	case PLAYER_DIRECTION::LeftUp:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(135.0f);
		break;
	case PLAYER_DIRECTION::Left:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(180.0f);
		break;
	case PLAYER_DIRECTION::LeftDown:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(225.0f);
		break;
	case PLAYER_DIRECTION::Down:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(270.0f);
		break;
	case PLAYER_DIRECTION::RightDown:
		PlayerDirDeg = float4::GetUnitVectorFromDeg(315.0f);
		break;
	default:
		break;
	}
}

bool Player::MoveCheck()
{
	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		return true;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightDown);
		return true;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		return true;
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		return true;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::TileColCheck()
{
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalRightPos))
		{
			PosNormalization(LocalRightPos);
			return true;
		}
	case PLAYER_DIRECTION::RightUp:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalRightUpPos))
		{
			PosNormalization(LocalRightUpPos);
			return true;
		}
	case PLAYER_DIRECTION::Up:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalUpPos))
		{
			PosNormalization(LocalUpPos);
			return true;
		}
	case PLAYER_DIRECTION::LeftUp:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalLeftUpPos))
		{
			PosNormalization(LocalLeftUpPos);
			return true;
		}
	case PLAYER_DIRECTION::Left:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalLeftPos))
		{
			PosNormalization(LocalLeftPos);
			return true;
		}
	case PLAYER_DIRECTION::LeftDown:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalLeftDownPos))
		{
			PosNormalization(LocalLeftDownPos);
			return true;
		}
	case PLAYER_DIRECTION::Down:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalDownPos))
		{
			PosNormalization(LocalDownPos);
			return true;
		}
	case PLAYER_DIRECTION::RightDown:
		if (true == CurMap->ColCheck(Transform.GetWorldPosition() + LocalRightDownPos))
		{
			PosNormalization(LocalRightDownPos);
			return true;
		}
	default:
		break;
	}
	
	return false;
}

void Player::PosNormalization(float4 _Pos)
{
	while (true == CurMap->ColCheck(Transform.GetWorldPosition() + _Pos))
	{
		float4 MovePos = -PlayerDirDeg;
		Transform.AddLocalPosition(MovePos);
	}
}
