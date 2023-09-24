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
		DebugingModeSwitch();
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

	TileColCheck();

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

	if (PLAYER_STATE::Move == CurState)
	{
		AdjustPosByCol();
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
	float4 MoveCheck = float4::ZERO;

	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		if (false == ColInfo.LeftCheck)
		{
			if (false == ColInfo.UpCheck)
			{
				ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
				return true;
			}
			else
			{
				ChangeDirCheck(PLAYER_DIRECTION::Left);
				return true;
			}
		}
		else if (false == ColInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		return false;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		if (false == ColInfo.RightCheck)
		{
			if (false == ColInfo.UpCheck)
			{
				ChangeDirCheck(PLAYER_DIRECTION::RightUp);
				return true;
			}
			else
			{
				ChangeDirCheck(PLAYER_DIRECTION::Right);
				return true;
			}
		}
		else if (false == ColInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		if (false == ColInfo.LeftCheck)
		{
			if (false == ColInfo.DownCheck)
			{
				ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
				return true;
			}
			else
			{
				ChangeDirCheck(PLAYER_DIRECTION::Left);
				return true;
			}
		}
		else if (false == ColInfo.DownCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Down);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		if (false == ColInfo.RightCheck)
		{
			if (false == ColInfo.DownCheck)
			{
				ChangeDirCheck(PLAYER_DIRECTION::RightDown);
				return true;
			}
			else
			{
				ChangeDirCheck(PLAYER_DIRECTION::Right);
				return true;
			}
		}
		else if (false == ColInfo.DownCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Down);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::RightDown);
		return false;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		if (false == ColInfo.UpCheck)
		{
			return true;
		}
		return false;
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		if (false == ColInfo.LeftCheck)
		{
			return true;
		}
		return false;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		if (false == ColInfo.DownCheck)
		{
			return true;
		}
		return false;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		if (false == ColInfo.RightCheck)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

void Player::TileColCheck()
{
	ColInfo.LeftCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalLeftPos, ColInfo.LeftColType);
	ColInfo.RightCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalRightPos, ColInfo.RightColType);
	ColInfo.UpCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalUpPos, ColInfo.UpColType);
	ColInfo.DownCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalDownPos, ColInfo.DownColType);
	//TriangleColCheck();
}

void Player::TileColCheckNormal()
{
	ColNormalInfo.LeftCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalLeftPos + float4::LEFT, ColInfo.LeftColType);
	ColNormalInfo.RightCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalRightPos + float4::RIGHT, ColInfo.RightColType);
	ColNormalInfo.UpCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalUpPos + float4::UP, ColInfo.UpColType);
	ColNormalInfo.DownCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalDownPos + float4::DOWN, ColInfo.DownColType);
}

void Player::TriangleColCheck()
{
	/*if (true == ColInfo.LeftCheck)
	{
		switch (ColInfo.LeftColType)
		{
		case COLLISION_TYPE::LEFTUP_TRIANGLE:

			break;
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:

			break;
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:

			break;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:

			break;
		case COLLISION_TYPE::EMPTY:
		case COLLISION_TYPE::RECT:
		default:
			return;
		}
	}*/
}


bool Player::CurDirColCheck()
{
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		return ColInfo.RightCheck;
	case PLAYER_DIRECTION::RightUp:
		return ColInfo.RightCheck || ColInfo.UpCheck;
	case PLAYER_DIRECTION::Up:
		return ColInfo.UpCheck;
	case PLAYER_DIRECTION::LeftUp:
		return ColInfo.LeftCheck || ColInfo.UpCheck;
	case PLAYER_DIRECTION::Left:
		return ColInfo.LeftCheck;
	case PLAYER_DIRECTION::LeftDown:
		return ColInfo.LeftCheck || ColInfo.DownCheck;
	case PLAYER_DIRECTION::Down:
		return ColInfo.DownCheck;
	case PLAYER_DIRECTION::RightDown:
		return ColInfo.RightCheck || ColInfo.DownCheck;
	default:
		return false;
	}
}

void Player::AdjustPosByCol()
{
	TileColCheckNormal();
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		// Adjust Right
		if (true == ColNormalInfo.RightCheck)
		{
			while (true == ColInfo.RightCheck)
			{
				Transform.AddLocalPosition(float4::LEFT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::RIGHT);
		}
		break;

	case PLAYER_DIRECTION::RightUp:
		// Adjust Up
		if (true == ColNormalInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}

		// Adjust Right
		if (true == ColNormalInfo.RightCheck)
		{
			while (true == ColInfo.RightCheck)
			{
				Transform.AddLocalPosition(float4::LEFT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::RIGHT);
		}
		break;

	case PLAYER_DIRECTION::Up:
		// Adjust Up
		if (true == ColNormalInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}
		break;

	case PLAYER_DIRECTION::LeftUp:
		// Adjust Up
		if (true == ColNormalInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}

		// Adjust Left
		if (true == ColNormalInfo.LeftCheck)
		{
			while (true == ColInfo.LeftCheck)
			{
				Transform.AddLocalPosition(float4::RIGHT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::LEFT);
		}
		break;

	case PLAYER_DIRECTION::Left:
		// Adjust Left
		if (true == ColNormalInfo.LeftCheck)
		{
			while (true == ColInfo.LeftCheck)
			{
				Transform.AddLocalPosition(float4::RIGHT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::LEFT);
		}
		break;

	case PLAYER_DIRECTION::LeftDown:
		// Adjust Down
		if (true == ColNormalInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}

		// Adjust Left
		if (true == ColNormalInfo.LeftCheck)
		{
			while (true == ColInfo.LeftCheck)
			{
				Transform.AddLocalPosition(float4::RIGHT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::LEFT);
		}
		break;

	case PLAYER_DIRECTION::Down:
		// Adjust Down
		if (true == ColNormalInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}
		break;

	case PLAYER_DIRECTION::RightDown:
		// Adjust Down
		if (true == ColNormalInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}

		// Adjust Right
		if (true == ColNormalInfo.RightCheck)
		{
			while (true == ColInfo.RightCheck)
			{
				Transform.AddLocalPosition(float4::LEFT);
				TileColCheck();
			}
			Transform.AddLocalPosition(float4::RIGHT);
		}
		break;

	default:
		break;
	}

	TileColCheck();
}

void Player::DirSpecularReflection()
{
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		if (true == ColInfo.RightCheck)
		{
			SetDirection(PLAYER_DIRECTION::Left);
		}
		
		break;
	case PLAYER_DIRECTION::RightUp:
		break;
	case PLAYER_DIRECTION::Up:
		break;
	case PLAYER_DIRECTION::LeftUp:
		break;
	case PLAYER_DIRECTION::Left:
		break;
	case PLAYER_DIRECTION::LeftDown:
		break;
	case PLAYER_DIRECTION::Down:
		break;
	case PLAYER_DIRECTION::RightDown:
		break;
	default:
		break;
	}
}