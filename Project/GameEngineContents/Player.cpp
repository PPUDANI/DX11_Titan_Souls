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
	// Rolling CoolDown Update
	if (true == IsRollingOnCooldown)
	{
		RollingCoolDownUpdate(_Delta);
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

	// Run Check
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
	
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PLAYER_STATE::Aim);
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
	case PLAYER_STATE::Rolling:
		RollingUpdate(_Delta);
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

	TileColCheck();
	BodyColCheck();
	AdjustPosByCol();
	
	if (true == DebugingMode)
	{
		DebugRender();
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetWorldPosition());
}

void Player::ChangeState(PLAYER_STATE _State)
{
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
	case PLAYER_STATE::Rolling:
		RollingStart();
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

bool Player::MoveCheckInIdle()
{
	float4 MoveCheck = float4::ZERO;

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

bool Player::MoveCheck()
{
	float4 MoveCheck = float4::ZERO;
	if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('A'))
	{
		if (false == TileColInfo.LeftCheck)
		{
			if (false == TileColInfo.UpCheck)
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
		else if (false == TileColInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		ChangeState(PLAYER_STATE::Blocked);
		return false;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		if (false == TileColInfo.RightCheck)
		{
			if (false == TileColInfo.UpCheck)
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
		else if (false == TileColInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		ChangeState(PLAYER_STATE::Blocked);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		if (false == TileColInfo.LeftCheck)
		{
			if (false == TileColInfo.DownCheck)
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
		else if (false == TileColInfo.DownCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Down);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		ChangeState(PLAYER_STATE::Blocked);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		if (false == TileColInfo.RightCheck)
		{
			if (false == TileColInfo.DownCheck)
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
		else if (false == TileColInfo.DownCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Down);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::RightDown);
		ChangeState(PLAYER_STATE::Blocked);
		return false;
	}
	else if (true == GameEngineInput::IsPress('W'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		if (false == BodyColInfo.UpCheck)
		{
			return true;
		}

		switch (TileColInfo.UpColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (COLLISION_TYPE::LEFTUP_TRIANGLE == TileColInfo.LeftColType)
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
				return true;
			}
			else if (COLLISION_TYPE::RIGHTUP_TRIANGLE == TileColInfo.RightColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
				return true;
			}
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		if (false == BodyColInfo.LeftCheck)
		{
			return true;
		}

		switch (TileColInfo.LeftColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (COLLISION_TYPE::LEFTUP_TRIANGLE == TileColInfo.UpColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
				return true;
			}
			else if (COLLISION_TYPE::LEFTDOWN_TRIANGLE == TileColInfo.DownColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
				return true;
			}
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		if (false == BodyColInfo.DownCheck)
		{
			return true;
		}

		switch (TileColInfo.DownColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (COLLISION_TYPE::LEFTDOWN_TRIANGLE == TileColInfo.LeftColType)
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
				return true;
			}
			else if (COLLISION_TYPE::RIGHTDOWN_TRIANGLE == TileColInfo.RightColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
				return true;
			}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		if (false == BodyColInfo.RightCheck)
		{
			return true;
		}
		
		switch (TileColInfo.RightColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (COLLISION_TYPE::RIGHTUP_TRIANGLE == TileColInfo.UpColType)
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
				return true;
			}
			else if (COLLISION_TYPE::RIGHTDOWN_TRIANGLE == TileColInfo.DownColType)
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
				return true;
			}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else
	{
		ChangeState(PLAYER_STATE::Stop);
		return false;
	}
	//  Up일 때
	//	위에 1, 4, 5 이 있다면 막혀야함
	//	위에 2가 있다면 방향 바꿔야함
	//	위에 3이 있다면 방향 바꿔야함

	//	Down일 때
	//	아래에 1, 2, 3 이 있다면 막혀야함
	//	아래에 4, 5가 있다면 좌상향 우상향으로 바꿔야함.

	//	Left일 때
	//	왼쪽에 1, 3, 5 이 있다면 막혀야함
	//	왼쪽에 2, 4 있다면 방향 바꿔야함

	//	Right일 때
	//	오른쪽에 1, 2, 4 이 있다면 막혀야함
	//	오른쪽에 3, 5 있다면 방향 바꿔야함

	//	LeftUp일 때
	//	왼쪽에 1, 2, 3, 5, 가 있으면 멈춰야함
	//	좌업에 1 3 5가 있으면 위로 방향전환

	//	RightUp일 때
	//	오른쪽에 1, 2, 3, 5, 가 있으면 멈춰야함
	//	에 1 3 5가 있으면 위로 방향전환

	//	LeftDown일 때
	//	왼쪽에 1, 2, 3, 5, 가 있으면 멈춰야함
	//	좌업에 1 3 5가 있으면 위로 방향전환

	//	RightDown일 때
	//	오른쪽에 1, 2, 3, 5, 가 있으면 멈춰야함
	//	좌업에 1 3 5가 있으면 위로 방향전환
}

void Player::BodyColCheck()
{
	bool LeftCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalLeftPos);
	bool LeftCheck2 = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalLeftPos2);
	bool RightCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalRightPos);
	bool RightCheck2 = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalRightPos2);
	bool UpCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalUpPos);
	bool UpCheck2 = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalUpPos2);
	bool DownCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalDownPos);
	bool DownCheck2 = CurMap->AllColCheck(Transform.GetWorldPosition() + LocalDownPos2);

	BodyColInfo.UpCheck = UpCheck || UpCheck2;
	BodyColInfo.DownCheck = DownCheck || DownCheck2;
	BodyColInfo.LeftCheck = LeftCheck || LeftCheck2;
	BodyColInfo.RightCheck = RightCheck || RightCheck2;
}

void Player::TileColCheck()
{
	bool LeftCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileLeftPos, TileColInfo.LeftColType);
	bool RightCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileRightPos, TileColInfo.RightColType);
	bool UpCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileUpPos, TileColInfo.UpColType);
	bool DownCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileDownPos, TileColInfo.DownColType);

	TileColInfo.UpCheck = UpCheck;
	TileColInfo.DownCheck = DownCheck;
	TileColInfo.LeftCheck = LeftCheck;
	TileColInfo.RightCheck = RightCheck;
}

bool Player::CurDirColCheck()
{
	BodyColCheck();
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		return BodyColInfo.RightCheck;
	case PLAYER_DIRECTION::RightUp:
		return BodyColInfo.RightCheck || BodyColInfo.UpCheck;
	case PLAYER_DIRECTION::Up:
		return BodyColInfo.UpCheck;
	case PLAYER_DIRECTION::LeftUp:
		return BodyColInfo.LeftCheck || BodyColInfo.UpCheck;
	case PLAYER_DIRECTION::Left:
		return BodyColInfo.LeftCheck;
	case PLAYER_DIRECTION::LeftDown:
		return BodyColInfo.LeftCheck || BodyColInfo.DownCheck;
	case PLAYER_DIRECTION::Down:
		return BodyColInfo.DownCheck;
	case PLAYER_DIRECTION::RightDown:
		return BodyColInfo.RightCheck || BodyColInfo.DownCheck;
	default:
		return false;
	}
}


bool Player::AnyDirColCheck()
{
	return true == BodyColInfo.UpCheck   ||
		   true == BodyColInfo.DownCheck ||
		   true == BodyColInfo.LeftCheck ||
		   true == BodyColInfo.RightCheck;
}

bool Player::AllDirColCheck()
{
	return true == BodyColInfo.UpCheck &&
		true == BodyColInfo.DownCheck &&
		true == BodyColInfo.LeftCheck &&
		true == BodyColInfo.RightCheck;
}

void Player::ResolveCollisionSticking()
{
	switch (PrevDir)
	{
	case PLAYER_DIRECTION::Right:
		while (true == BodyColInfo.RightCheck)
		{
			Transform.AddLocalPosition(float4::LEFT);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::RIGHT);
		break;
	case PLAYER_DIRECTION::RightUp:
		while (true == BodyColInfo.RightCheck || true == BodyColInfo.UpCheck)
		{
			Transform.AddLocalPosition(float4::LEFT);
			Transform.AddLocalPosition(float4::DOWN);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::RIGHT);
		Transform.AddLocalPosition(float4::UP);
	case PLAYER_DIRECTION::Up:
		while (true == BodyColInfo.UpCheck)
		{
			Transform.AddLocalPosition(float4::DOWN);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::UP);
		break;
	case PLAYER_DIRECTION::LeftUp:
		while (true == BodyColInfo.LeftCheck || true == BodyColInfo.UpCheck)
		{
			Transform.AddLocalPosition(float4::RIGHT);
			Transform.AddLocalPosition(float4::DOWN);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::LEFT);
		Transform.AddLocalPosition(float4::UP);
		break;
	case PLAYER_DIRECTION::Left:
		while (true == BodyColInfo.LeftCheck)
		{
			Transform.AddLocalPosition(float4::RIGHT);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::LEFT);
		break;
	case PLAYER_DIRECTION::LeftDown:
		while (true == BodyColInfo.LeftCheck || true == BodyColInfo.DownCheck)
		{
			Transform.AddLocalPosition(float4::RIGHT);
			Transform.AddLocalPosition(float4::UP);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::LEFT);
		Transform.AddLocalPosition(float4::DOWN);
		break;
	case PLAYER_DIRECTION::Down:
		while (true == BodyColInfo.DownCheck)
		{
			Transform.AddLocalPosition(float4::UP);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::DOWN);
		break;
	case PLAYER_DIRECTION::RightDown:
		while (true == BodyColInfo.RightCheck || true == BodyColInfo.DownCheck)
		{
			Transform.AddLocalPosition(float4::LEFT);
			Transform.AddLocalPosition(float4::UP);
			BodyColCheck();
		}
		Transform.AddLocalPosition(float4::RIGHT);
		Transform.AddLocalPosition(float4::DOWN);
		break;
	default:
		break;
	}
}
void Player::AdjustPosByCol()
{
	bool AdjustLeft = false;
	bool AdjustRight = false;
	bool AdjustUp = false;
	bool AdjustDown = false;

	if (true == AllDirColCheck())
	{
		ResolveCollisionSticking();
	}
	else
	{
		while (true == AnyDirColCheck())
		{
			if (true == BodyColInfo.LeftCheck)
			{
				Transform.AddLocalPosition(float4::RIGHT);
				AdjustLeft = true;
			}

			if (true == BodyColInfo.RightCheck)
			{
				Transform.AddLocalPosition(float4::LEFT);
				AdjustRight = true;
			}

			if (true == BodyColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				AdjustUp = true;
			}

			if (true == BodyColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				AdjustDown = true;
			}
			BodyColCheck();
		}

		
		if (true == AdjustLeft)
		{
			Transform.AddLocalPosition(float4::LEFT);
		}
		if (true == AdjustRight)
		{
			Transform.AddLocalPosition(float4::RIGHT);
		}
		if (true == AdjustUp)
		{
			Transform.AddLocalPosition(float4::UP);
		}
		if (true == AdjustDown)
		{
			Transform.AddLocalPosition(float4::DOWN);
		}
	}
	

	TileColCheck();
	BodyColCheck();
}

void Player::DirSpecularReflection()
{
	TileColCheck();
	PrevDir = CurDir;
	switch (CurDir)
	{
	case PLAYER_DIRECTION::RightUp:
		if (true == TileColInfo.RightCheck)
		{
			if (true == TileColInfo.UpCheck)
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
			}
			else
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
			}
		}
		else if (true == TileColInfo.UpCheck)
		{
			SetDirection(PLAYER_DIRECTION::RightDown);
		}
		return;
	case PLAYER_DIRECTION::LeftUp:
		if (true == TileColInfo.LeftCheck)
		{
			if (true == TileColInfo.UpCheck)
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
			}
			else
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
			}
		}
		else if (true == TileColInfo.UpCheck)
		{
			SetDirection(PLAYER_DIRECTION::LeftDown);
		}
		return;
	case PLAYER_DIRECTION::RightDown:
		if (true == TileColInfo.RightCheck)
		{
			if (true == TileColInfo.DownCheck)
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
			}
			else
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
			}
		}
		else if (true == TileColInfo.DownCheck)
		{
			SetDirection(PLAYER_DIRECTION::RightUp);
		}
		return;
	case PLAYER_DIRECTION::LeftDown:
		if (true == TileColInfo.LeftCheck)
		{
			if (true == TileColInfo.DownCheck)
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
			}
			else
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
			}
		}
		else if (true == TileColInfo.DownCheck)
		{
			SetDirection(PLAYER_DIRECTION::LeftUp);
		}
		return;
	case PLAYER_DIRECTION::Right:
		switch (TileColInfo.RightColType)
		{
		case COLLISION_TYPE::EMPTY:
			return;
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Up);
			return;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		}
	case PLAYER_DIRECTION::Up:
		switch (TileColInfo.UpColType)
		{
		case COLLISION_TYPE::EMPTY:
			return;
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		}
	case PLAYER_DIRECTION::Left:
		switch (TileColInfo.LeftColType)
		{
		case COLLISION_TYPE::EMPTY:
			return;
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Up);
			return;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		}
	case PLAYER_DIRECTION::Down:
		switch (TileColInfo.DownColType)
		{
		case COLLISION_TYPE::EMPTY:
			return;
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Up);
			return;
		}
	default:
		break;
	}
}

void Player::DebugRender()
{
	GameEngineTransform TData;
	TData.SetWorldRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 1.0f, 1.0f });

	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalRightPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalRightPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalLeftPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalLeftPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalUpPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalUpPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalDownPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + LocalDownPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });


	TData.SetWorldPosition(Transform.GetWorldPosition() + TileRightPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + TileLeftPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + TileUpPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetWorldPosition(Transform.GetWorldPosition() + TileDownPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

}