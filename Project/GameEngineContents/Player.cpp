#include "PreCompile.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	GlobalLoad::PlayerLoad();

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Player);
	BodyRenderer->SetSprite("Player.png");
	BodyRenderer->SetImageScale(GlobalValue::StandardRatio);

	// Idle
	BodyRenderer->CreateAnimation("Right_Idle", "Player.png", 0.f, 0, 0, false);
	BodyRenderer->CreateAnimation("Up_Idle", "Player.png", 0.1f, 15, 15, false);
	BodyRenderer->CreateAnimation("Left_Idle", "Player.png", 0.1f, 30, 30, false);
	BodyRenderer->CreateAnimation("Down_Idle", "Player.png", 0.1f, 45, 45, false);
	BodyRenderer->CreateAnimation("RightDown_Idle", "Player.png", 0.1f, 60, 60, false);
	BodyRenderer->CreateAnimation("LeftDown_Idle", "Player.png", 0.1f, 75, 75, false);
	BodyRenderer->CreateAnimation("LeftUp_Idle", "Player.png", 0.1f, 90, 90, false);
	BodyRenderer->CreateAnimation("RightUp_Idle", "Player.png", 0.1f, 105, 105, false);

	// Run
	BodyRenderer->CreateAnimation("Right_Run", "Player.png", 0.1f, 0, 5, true);
	BodyRenderer->CreateAnimation("Up_Run", "Player.png", 0.1f, 15, 20, true);
	BodyRenderer->CreateAnimation("Left_Run", "Player.png", 0.1f, 30, 35, true);
	BodyRenderer->CreateAnimation("Down_Run", "Player.png", 0.1f, 45, 50, true);
	BodyRenderer->CreateAnimation("RightDown_Run", "Player.png", 0.1f, 60, 65, true);
	BodyRenderer->CreateAnimation("LeftDown_Run", "Player.png", 0.1f, 75, 80, true);
	BodyRenderer->CreateAnimation("LeftUp_Run", "Player.png", 0.1f, 90, 95, true);
	BodyRenderer->CreateAnimation("RightUp_Run", "Player.png", 0.1f, 105, 110, true);

	// Run
	BodyRenderer->CreateAnimation("Right_Run", "Player.png", 0.1f, 0, 5, true);
	BodyRenderer->CreateAnimation("Up_Run", "Player.png", 0.1f, 15, 20, true);
	BodyRenderer->CreateAnimation("Left_Run", "Player.png", 0.1f, 30, 35, true);
	BodyRenderer->CreateAnimation("Down_Run", "Player.png", 0.1f, 45, 50, true);
	BodyRenderer->CreateAnimation("RightDown_Run", "Player.png", 0.1f, 60, 65, true);
	BodyRenderer->CreateAnimation("LeftDown_Run", "Player.png", 0.1f, 75, 80, true);
	BodyRenderer->CreateAnimation("LeftUp_Run", "Player.png", 0.1f, 90, 95, true);
	BodyRenderer->CreateAnimation("RightUp_Run", "Player.png", 0.1f, 105, 110, true);

	CurDir = PLAYER_DIRECTION::Down;
	ChangeState(PLAYER_STATE::Idle);
}

void Player::Update(float _Delta)
{
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case PLAYER_STATE::Run:
		RunUpdate(_Delta);
		break;
	case PLAYER_STATE::Roll:
		RollUpdate(_Delta);
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
	default:
		break;
	}
}

void Player::SetAnimation(std::string_view _AnimName)
{
	std::string AnimationName = "";

	switch (CurDir)
	{
	case PLAYER_DIRECTION::Right:
		AnimationName += "Right_";
		break;
	case PLAYER_DIRECTION::Up:
		AnimationName += "Up_";
		break;
	case PLAYER_DIRECTION::Left:
		AnimationName += "Left_";
		break;
	case PLAYER_DIRECTION::Down:
		AnimationName += "Down_";
		break;
	case PLAYER_DIRECTION::RightDown:
		AnimationName += "RightDown_";
		break;
	case PLAYER_DIRECTION::LeftDown:
		AnimationName += "LeftDown_";
		break;
	case PLAYER_DIRECTION::LeftUp:
		AnimationName += "LeftUp_";
		break;
	case PLAYER_DIRECTION::RightUp:
		AnimationName += "RightUp_";
		break;
	default:
		break;
	}

	AnimationName += _AnimName.data();

	BodyRenderer->ChangeAnimation(AnimationName, false);
}

void Player::ChangeState(PLAYER_STATE _State)
{
	CurState = _State;
	
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleStart();
		break;
	case PLAYER_STATE::Run:
		RunStart();
		break;
	case PLAYER_STATE::Roll:
		RollStart();
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
	default:
		break;
	}
}
