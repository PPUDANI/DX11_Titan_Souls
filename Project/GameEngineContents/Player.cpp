#include "PreCompile.h"
#include "Player.h"
#include "Arrow.h"

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

	BodyCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Player);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetLocalScale({ 24.0f, 24.0f, 1.0f });
	BodyCollision->Transform.SetLocalPosition({ 0.0f, -5.0f, 1.0f });

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetSprite("Player.png", 63);
	ShadowRenderer->Transform.SetLocalPosition(DefaultRendererPos);
	ShadowRenderer->SetImageScale(GlobalValue::StandardTextureScale);

	ChangeState(PLAYER_STATE::StandUp);

	GameEngineInput::AddInputObject(this);
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

	// Run Check
	if (true == GameEngineInput::IsPress(VK_SHIFT, this))
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

	// InvincibilityMode switch
	if (true == GameEngineInput::IsDown('9', this))
	{
		InvincibilityMode = !InvincibilityMode;
	}

	if (false == InvincibilityMode)
	{
		if (true == BodyCollision->Collision(COLLISION_TYPE::Sludge))
		{
			ChangeState(PLAYER_STATE::Death);
		}

		if (true == BodyCollision->Collision(COLLISION_TYPE::BossBody))
		{
			ChangeState(PLAYER_STATE::Death);
		}

		if (true == BodyCollision->Collision(COLLISION_TYPE::Weakness))
		{
			ChangeState(PLAYER_STATE::Death);
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
	case PLAYER_STATE::Rolling:
		RollingUpdate(_Delta);
		break;
	case PLAYER_STATE::Blocked:
		BlockedUpdate(_Delta);
		break;
	case PLAYER_STATE::Aim:
		AimUpdate(_Delta);
		break;
	case PLAYER_STATE::Returning:
		ReturningUpdate(_Delta);
		break;
	case PLAYER_STATE::Death:
		DeathUpdate(_Delta);
		break;
	case PLAYER_STATE::StandUp:
		StandUpUpdate(_Delta);
		break;
	case PLAYER_STATE::EnterLevel:
		EnterLevelUpdate(_Delta);
		break;
	case PLAYER_STATE::ExitLevel:
		ExitLevelUpdate(_Delta);
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

	CameraManager::AddCameraPosFromPlayer = Transform.GetWorldPosition();
}

void Player::ChangeState(PLAYER_STATE _State)
{
	if (_State == CurState)
	{
		return;
	}

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
	case PLAYER_STATE::Returning:
		ReturningStart();
		break;
	case PLAYER_STATE::Death:
		DeathStart();
		break;
	case PLAYER_STATE::StandUp:
		StandUpStart();
		break;
	case PLAYER_STATE::EnterLevel:
		EnterLevelStart();
		break;
	case PLAYER_STATE::ExitLevel:
		ExitLevelStart();
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

void Player::AimDirectionUpdate()
{
	int DividedAngleIndex = static_cast<int>(ArrowAngleDeg / 22.5f);

	switch (DividedAngleIndex)
	{
	case 0:
	case 15:
		SetDirection(PLAYER_DIRECTION::Right);
		break;
	case 1:
	case 2:
		SetDirection(PLAYER_DIRECTION::RightUp);
		break;
	case 3:
	case 4:
		SetDirection(PLAYER_DIRECTION::Up);
		break;
	case 5:
	case 6:
		SetDirection(PLAYER_DIRECTION::LeftUp);
		break;
	case 7:
	case 8:
		SetDirection(PLAYER_DIRECTION::Left);
		break;
	case 9:
	case 10:
		SetDirection(PLAYER_DIRECTION::LeftDown);
		break;
	case 11:
	case 12:
		SetDirection(PLAYER_DIRECTION::Down);
		break;
	case 13:
	case 14:
		SetDirection(PLAYER_DIRECTION::RightDown);
		break;
	default:
		break;
	}
}

bool Player::MoveCheckInIdle()
{
	float4 MoveCheck = float4::ZERO;

	if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('A', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		return true;
	}
	else if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('D', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('A', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('D', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::RightDown);
		return true;
	}
	else if (true == GameEngineInput::IsPress('W', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		return true;
	}
	else if (true == GameEngineInput::IsPress('A', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		return true;
	}
	else if (true == GameEngineInput::IsPress('S', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		return true;
	}
	else if (true == GameEngineInput::IsPress('D', this))
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
	if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('A', this))
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
	else if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('D', this))
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
	else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('A', this))
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
	else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('D', this))
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
	else if (true == GameEngineInput::IsPress('W', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Up);
		if (false == BodyColInfo.UpCheck)
		{
			return true;
		}

		switch (TileColInfo.UpColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case TILE_COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (TILE_COLLISION_TYPE::LEFTUP_TRIANGLE == TileColInfo.LeftColType)
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
				return true;
			}
			else if (TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE == TileColInfo.RightColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
				return true;
			}
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		//case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		//case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('A', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		if (false == BodyColInfo.LeftCheck)
		{
			return true;
		}

		switch (TileColInfo.LeftColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case TILE_COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (TILE_COLLISION_TYPE::LEFTUP_TRIANGLE == TileColInfo.UpColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
				return true;
			}
			else if (TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE == TileColInfo.DownColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftUp);
				return true;
			}
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		//case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
		//case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('S', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		if (false == BodyColInfo.DownCheck)
		{
			return true;
		}

		switch (TileColInfo.DownColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case TILE_COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE == TileColInfo.LeftColType)
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
				return true;
			}
			else if (TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE == TileColInfo.RightColType)
			{
				SetDirection(PLAYER_DIRECTION::LeftDown);
				return true;
			}
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		//case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
		//case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
		default:
			ChangeState(PLAYER_STATE::Blocked);
			return false;
			break;
		}
	}
	else if (true == GameEngineInput::IsPress('D', this))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		if (false == BodyColInfo.RightCheck)
		{
			return true;
		}

		switch (TileColInfo.RightColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
		{
			return true;
		}
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case TILE_COLLISION_TYPE::RECT:
			// 중간중간 사각형 충돌체와 충돌해서 멈추는 현상 제거
			if (TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE == TileColInfo.UpColType)
			{
				SetDirection(PLAYER_DIRECTION::RightDown);
				return true;
			}
			else if (TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE == TileColInfo.DownColType)
			{
				SetDirection(PLAYER_DIRECTION::RightUp);
				return true;
			}
			ChangeState(PLAYER_STATE::Blocked);
			return false;
		//case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
		//case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
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
}

void Player::BodyColCheck()
{
	bool LeftCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalLeftPos);
	bool LeftCheck2 = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalLeftPos2);
	bool RightCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalRightPos);
	bool RightCheck2 = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalRightPos2);
	bool UpCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalUpPos);
	bool UpCheck2 = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalUpPos2);
	bool DownCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalDownPos);
	bool DownCheck2 = CurMap->AllColCheck(Transform.GetLocalPosition() + LocalDownPos2);

	BodyColInfo.UpCheck = UpCheck || UpCheck2;
	BodyColInfo.DownCheck = DownCheck || DownCheck2;
	BodyColInfo.LeftCheck = LeftCheck || LeftCheck2;
	BodyColInfo.RightCheck = RightCheck || RightCheck2;
}

void Player::TileColCheck()
{
	bool LeftCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + TileLeftPos, TileColInfo.LeftColType);
	bool RightCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + TileRightPos, TileColInfo.RightColType);
	bool UpCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + TileUpPos, TileColInfo.UpColType);
	bool DownCheck = CurMap->AllColCheck(Transform.GetLocalPosition() + TileDownPos, TileColInfo.DownColType);

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
	return true == BodyColInfo.UpCheck ||
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
		break;
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
		case TILE_COLLISION_TYPE::EMPTY:
			return;
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Up);
			return;
		case TILE_COLLISION_TYPE::RECT:
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		}
	case PLAYER_DIRECTION::Up:
		switch (TileColInfo.UpColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
			return;
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		case TILE_COLLISION_TYPE::RECT:
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		}
	case PLAYER_DIRECTION::Left:
		switch (TileColInfo.LeftColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
			return;
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Down);
			return;
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Up);
			return;
		case TILE_COLLISION_TYPE::RECT:
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		}
	case PLAYER_DIRECTION::Down:
		switch (TileColInfo.DownColType)
		{
		case TILE_COLLISION_TYPE::EMPTY:
			return;
		case TILE_COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Right);
			return;
		case TILE_COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::Left);
			return;
		case TILE_COLLISION_TYPE::RECT:
		case TILE_COLLISION_TYPE::LEFTUP_TRIANGLE:
		case TILE_COLLISION_TYPE::RIGHTUP_TRIANGLE:
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
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 1.0f, 1.0f });

	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalRightPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalRightPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalLeftPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalLeftPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalUpPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalUpPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalDownPos);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + LocalDownPos2);
	GameEngineDebug::DrawBox2D(TData, { 1, 0, 1, 1 });

	TData.SetLocalPosition(Transform.GetWorldPosition() + TileRightPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + TileLeftPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + TileUpPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	TData.SetLocalPosition(Transform.GetWorldPosition() + TileDownPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
}

void Player::AimCheck()
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		if (true == HasArrow())
		{
			ChangeState(PLAYER_STATE::Aim);
			return;
		}
	}
	else if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		if (ARROW_STATE::Fallen == MyArrow->GetCurState() ||
			ARROW_STATE::Pinned == MyArrow->GetCurState())
		{
			ChangeState(PLAYER_STATE::Returning);
		}
		return;
	}
}