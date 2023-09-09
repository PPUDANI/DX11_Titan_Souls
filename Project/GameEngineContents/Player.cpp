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
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Player);
	BodyRenderer->SetSprite("PlayerMove.png");
	BodyRenderer->SetImageScale({ 32.0f, 32.0f });

	// Idle
	BodyRenderer->CreateAnimation("Right_Idle", "PlayerMove.png", 0.f, 0, 0, false);
	BodyRenderer->CreateAnimation("Up_Idle", "PlayerMove.png", 0.1f, 15, 15, false);
	BodyRenderer->CreateAnimation("Left_Idle", "PlayerMove.png", 0.1f, 30, 30, false);
	BodyRenderer->CreateAnimation("Down_Idle", "PlayerMove.png", 0.1f, 45, 45, false);
	BodyRenderer->CreateAnimation("RightDown_Idle", "PlayerMove.png", 0.1f, 60, 60, false);
	BodyRenderer->CreateAnimation("LeftDown_Idle", "PlayerMove.png", 0.1f, 75, 75, false);
	BodyRenderer->CreateAnimation("LeftUp_Idle", "PlayerMove.png", 0.1f, 90, 90, false);
	BodyRenderer->CreateAnimation("RightUp_Idle", "PlayerMove.png", 0.1f, 105, 105, false);

	// Run
	BodyRenderer->CreateAnimation("Right_Run", "PlayerMove.png", 0.1f, 0, 5, true);
	BodyRenderer->CreateAnimation("Up_Run", "PlayerMove.png", 0.1f, 15, 20, true);
	BodyRenderer->CreateAnimation("Left_Run", "PlayerMove.png", 0.1f, 30, 35, true);
	BodyRenderer->CreateAnimation("Down_Run", "PlayerMove.png", 0.1f, 45, 50, true);
	BodyRenderer->CreateAnimation("RightDown_Run", "PlayerMove.png", 0.1f, 60, 65, true);
	BodyRenderer->CreateAnimation("LeftDown_Run", "PlayerMove.png", 0.1f, 75, 80, true);
	BodyRenderer->CreateAnimation("LeftUp_Run", "PlayerMove.png", 0.1f, 90, 95, true);
	BodyRenderer->CreateAnimation("RightUp_Run", "PlayerMove.png", 0.1f, 105, 110, true);

	CurDir = PlayerDir::Down;
	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	switch (CurState)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Run:
		RunUpdate();
		break;
	case PlayerState::Roll:
		RollUpdate();
		break;
	case PlayerState::Aim:
		AimUpdate();
		break;
	case PlayerState::Shot:
		ShotUpdate();
		break;
	case PlayerState::Death:
		DeathUpdate();
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
	case PlayerDir::Right:
		AnimationName += "Right_";
		break;
	case PlayerDir::Up:
		AnimationName += "Up_";
		break;
	case PlayerDir::Left:
		AnimationName += "Left_";
		break;
	case PlayerDir::Down:
		AnimationName += "Down_";
		break;
	case PlayerDir::RightDown:
		AnimationName += "RightDown_";
		break;
	case PlayerDir::LeftDown:
		AnimationName += "LeftDown_";
		break;
	case PlayerDir::LeftUp:
		AnimationName += "LeftUp_";
		break;
	case PlayerDir::RightUp:
		AnimationName += "RightUp_";
		break;
	default:
		break;
	}

	AnimationName += _AnimName.data();

	BodyRenderer->ChangeAnimation(AnimationName, false);
}

void Player::ChangeState(PlayerState _State)
{
	CurState = _State;
	
	switch (CurState)
	{
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Run:
		RunStart();
		break;
	case PlayerState::Roll:
		RollStart();
		break;
	case PlayerState::Aim:
		AimStart();
		break;
	case PlayerState::Shot:
		ShotStart();
		break;
	case PlayerState::Death:
		DeathStart();
		break;
	default:
		break;
	}
}
