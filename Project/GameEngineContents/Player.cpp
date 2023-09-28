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

	BodyColCheck();

	if (PLAYER_STATE::Move == CurState)
	{
		AdjustPosByCol();
	}
	
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
		if (false == ColTileInfo.LeftCheck)
		{
			if (false == ColTileInfo.UpCheck)
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
		else if (false == ColTileInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftUp);
		return false;
	}
	else if (true == GameEngineInput::IsPress('W') && true == GameEngineInput::IsPress('D'))
	{
		if (false == ColTileInfo.RightCheck)
		{
			if (false == ColTileInfo.UpCheck)
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
		else if (false == ColTileInfo.UpCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Up);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::RightUp);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		if (false == ColTileInfo.LeftCheck)
		{
			if (false == ColTileInfo.DownCheck)
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
		else if (false == ColTileInfo.DownCheck)
		{
			ChangeDirCheck(PLAYER_DIRECTION::Down);
			return true;
		}

		ChangeDirCheck(PLAYER_DIRECTION::LeftDown);
		return false;
	}
	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		if (false == ColTileInfo.RightCheck)
		{
			if (false == ColTileInfo.DownCheck)
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
		else if (false == ColTileInfo.DownCheck)
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
		if (false == ColTileInfo.UpCheck)
		{
			return true;
		}

		switch (ColTileInfo.UpColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			MsgBoxAssert("UpCheck : 충돌한 상태인데 UpColType값이 \"COLLISION_TYPE::EMPTY\"입니다.");
		}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Left);
		if (false == ColTileInfo.LeftCheck)
		{
			return true;
		}

		switch (ColTileInfo.LeftColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			MsgBoxAssert("LeftCheck : 충돌한 상태인데 LeftColType값이 \"COLLISION_TYPE::EMPTY\"입니다.");
		}
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftUp);
			return true;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
		default:
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Down);
		if (false == ColTileInfo.DownCheck)
		{
			return true;
		}

		switch (ColTileInfo.DownColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			MsgBoxAssert("DownCheck : 충돌한 상태인데 DownColType값이 \"COLLISION_TYPE::EMPTY\"입니다.");
		}
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::LeftDown);
			return true;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:

		default:
			return false;
		}
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		ChangeDirCheck(PLAYER_DIRECTION::Right);
		if (false == ColTileInfo.RightCheck)
		{
			return true;
		}
		
		switch (ColTileInfo.RightColType)
		{
		case COLLISION_TYPE::EMPTY:
		{
			MsgBoxAssert("RightCheck : 충돌한 상태인데 RightColType이 \"COLLISION_TYPE::EMPTY\"가나왔습니다.");
		}
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightDown);
			return true;
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			SetDirection(PLAYER_DIRECTION::RightUp);
			return true;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		default:
			return false;
		}
	}
	else
	{
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

	ColInfo.UpCheck = UpCheck || UpCheck2;
	ColInfo.DownCheck = DownCheck || DownCheck2;
	ColInfo.LeftCheck = LeftCheck || LeftCheck2;
	ColInfo.RightCheck = RightCheck || RightCheck2;

}

void Player::TileColCheck()
{
	bool LeftCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileLeftPos, ColTileInfo.LeftColType);
	bool RightCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileRightPos, ColTileInfo.RightColType);
	bool UpCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileUpPos, ColTileInfo.UpColType);
	bool DownCheck = CurMap->AllColCheck(Transform.GetWorldPosition() + TileDownPos, ColTileInfo.DownColType);

	ColTileInfo.UpCheck = UpCheck;
	ColTileInfo.DownCheck = DownCheck;
	ColTileInfo.LeftCheck = LeftCheck;
	ColTileInfo.RightCheck = RightCheck;
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
	TileColCheck();
	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		if (true == ColTileInfo.RightCheck)
		{
			while (true == ColInfo.RightCheck)
			{
				Transform.AddLocalPosition(float4::LEFT);
				BodyColCheck();
			}
 			Transform.AddLocalPosition(float4::RIGHT);
		}
		break;

	case PLAYER_DIRECTION::RightUp:
		if (true == ColTileInfo.RightCheck)
		{
			if (true == ColTileInfo.UpCheck)
			{
				while (true == ColInfo.RightCheck || true == ColInfo.UpCheck)
				{
					Transform.AddLocalPosition(float4::LEFT);
					Transform.AddLocalPosition(float4::DOWN);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::RIGHT);
				Transform.AddLocalPosition(float4::UP);
			}
			else
			{
				while (true == ColInfo.RightCheck)
				{
					Transform.AddLocalPosition(float4::LEFT);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::RIGHT);
			}
		}
		else if (true == ColTileInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}
		break;

	case PLAYER_DIRECTION::Up:
		if (true == ColTileInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}
		break;

	case PLAYER_DIRECTION::LeftUp:
		if (true == ColTileInfo.LeftCheck)
		{
			if (true == ColTileInfo.UpCheck)
			{
				while (true == ColInfo.LeftCheck || true == ColInfo.UpCheck)
				{
					Transform.AddLocalPosition(float4::RIGHT);
					Transform.AddLocalPosition(float4::DOWN);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::LEFT);
				Transform.AddLocalPosition(float4::UP);
			}
			else
			{
				while (true == ColInfo.LeftCheck)
				{
					Transform.AddLocalPosition(float4::RIGHT);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::LEFT);
			}
		}
		else if (true == ColTileInfo.UpCheck)
		{
			while (true == ColInfo.UpCheck)
			{
				Transform.AddLocalPosition(float4::DOWN);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::UP);
		}
		break;

	case PLAYER_DIRECTION::Left:
		if (true == ColTileInfo.LeftCheck)
		{
			while (true == ColInfo.LeftCheck)
			{
				Transform.AddLocalPosition(float4::RIGHT);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::LEFT);
		}
		break;
	case PLAYER_DIRECTION::LeftDown:
		if (true == ColTileInfo.LeftCheck)
		{
			if (true == ColTileInfo.DownCheck)
			{
				while (true == ColInfo.LeftCheck || true == ColInfo.DownCheck)
				{
					if (true == ColInfo.LeftCheck)
					{
						Transform.AddLocalPosition(float4::RIGHT);
					}

					if (true == ColInfo.DownCheck)
					{
						Transform.AddLocalPosition(float4::UP);
					}
					
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::LEFT);
				Transform.AddLocalPosition(float4::DOWN);
			}
			else
			{
				while (true == ColInfo.LeftCheck)
				{
					Transform.AddLocalPosition(float4::RIGHT);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::LEFT);
			}
		}
		else if (true == ColTileInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}
		break;
	case PLAYER_DIRECTION::Down:
		if (true == ColTileInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}
		break;
	case PLAYER_DIRECTION::RightDown:
		if (true == ColTileInfo.RightCheck)
		{
			if (true == ColTileInfo.DownCheck)
			{
				while (true == ColInfo.RightCheck || true == ColInfo.DownCheck)
				{
					Transform.AddLocalPosition(float4::LEFT);
					Transform.AddLocalPosition(float4::UP);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::RIGHT);
				Transform.AddLocalPosition(float4::DOWN);
			}
			else
			{
				while (true == ColInfo.RightCheck)
				{
					Transform.AddLocalPosition(float4::LEFT);
					BodyColCheck();
				}
				Transform.AddLocalPosition(float4::RIGHT);
			}
		}
		else if (true == ColTileInfo.DownCheck)
		{
			while (true == ColInfo.DownCheck)
			{
				Transform.AddLocalPosition(float4::UP);
				BodyColCheck();
			}
			Transform.AddLocalPosition(float4::DOWN);
		}
		break;
	default:
		break;
	}

	TileColCheck();
	BodyColCheck();
}

void Player::DirSpecularReflection()
{
	//switch (CurDir)
	//{
	//case PLAYER_DIRECTION::Right:
	//	break;
	//case PLAYER_DIRECTION::RightUp:
	//	break;
	//case PLAYER_DIRECTION::Up:
	//	break;
	//case PLAYER_DIRECTION::LeftUp:
	//	break;
	//case PLAYER_DIRECTION::Left:
	//	break;
	//case PLAYER_DIRECTION::LeftDown:
	//	break;
	//case PLAYER_DIRECTION::Down:
	//	break;
	//case PLAYER_DIRECTION::RightDown:
	//	break;
	//default:
	//	break;
	//}
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