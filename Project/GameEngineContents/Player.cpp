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
	BodyRenderer->SetImageScale({ 32.0f, 32.0f });

	// Idle Animations
	BodyRenderer->CreateAnimation("Right_Idle", "Player.png", 1.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Up_Idle", "Player.png", 1.0f, 25, 25, false);
	BodyRenderer->CreateAnimation("Left_Idle", "Player.png", 1.0f, 50, 50, false);
	BodyRenderer->CreateAnimation("Down_Idle", "Player.png", 1.0f, 75, 75, false);
	BodyRenderer->CreateAnimation("RightDown_Idle", "Player.png", 1.0f, 100, 100, false);
	BodyRenderer->CreateAnimation("LeftDown_Idle", "Player.png", 1.0f, 125, 125, false);
	BodyRenderer->CreateAnimation("LeftUp_Idle", "Player.png", 1.0f, 150, 150, false);
	BodyRenderer->CreateAnimation("RightUp_Idle", "Player.png", 1.0f, 175, 175, false);

	// Walk Animations
	BodyRenderer->CreateAnimation("Right_Walk", "Player.png", 0.1f, 0, 5, true);
	BodyRenderer->CreateAnimation("Up_Walk", "Player.png", 0.1f, 25, 30, true);
	BodyRenderer->CreateAnimation("Left_Walk", "Player.png", 0.1f, 50, 55, true);
	BodyRenderer->CreateAnimation("Down_Walk", "Player.png", 0.1f, 75, 80, true);
	BodyRenderer->CreateAnimation("RightDown_Walk", "Player.png", 0.1f, 100, 105, true);
	BodyRenderer->CreateAnimation("LeftDown_Walk", "Player.png", 0.1f, 125, 130, true);
	BodyRenderer->CreateAnimation("LeftUp_Walk", "Player.png", 0.1f, 150, 155, true);
	BodyRenderer->CreateAnimation("RightUp_Walk", "Player.png", 0.1f, 175, 180, true);

	// Run Animations
	BodyRenderer->CreateAnimation("Right_Run", "Player.png", 0.08f, 214, 219, true);
	BodyRenderer->CreateAnimation("Up_Run", "Player.png", 0.08f, 239, 244, true);
	BodyRenderer->CreateAnimation("Left_Run", "Player.png", 0.08f, 264, 269, true);
	BodyRenderer->CreateAnimation("Down_Run", "Player.png", 0.08f, 289, 294, true);
	BodyRenderer->CreateAnimation("RightDown_Run", "Player.png", 0.08f, 314, 319, true);
	BodyRenderer->CreateAnimation("LeftDown_Run", "Player.png", 0.08f, 339, 344, true);
	BodyRenderer->CreateAnimation("LeftUp_Run", "Player.png", 0.08f, 364, 369, true);
	BodyRenderer->CreateAnimation("RightUp_Run", "Player.png", 0.08f, 389, 394, true);

	// Roll Animations
	BodyRenderer->CreateAnimation("Right_Roll", "Player.png", 0.063f, 6, 11, false);
	BodyRenderer->CreateAnimation("Up_Roll", "Player.png", 0.063f, 31, 36, false);
	BodyRenderer->CreateAnimation("Left_Roll", "Player.png", 0.063f, 56, 61, false);
	BodyRenderer->CreateAnimation("Down_Roll", "Player.png", 0.063f, 81, 86, false);
	BodyRenderer->CreateAnimation("RightDown_Roll", "Player.png", 0.063f, 106, 111, false);
	BodyRenderer->CreateAnimation("LeftDown_Roll", "Player.png", 0.063f, 131, 136, false);
	BodyRenderer->CreateAnimation("LeftUp_Roll", "Player.png", 0.063f, 156, 161, false);
	BodyRenderer->CreateAnimation("RightUp_Roll", "Player.png", 0.063f, 181, 186, false);

	// Death Animations
	BodyRenderer->CreateAnimation("Right_Death", "Player.png", 1.0f, 12, 12, false);
	BodyRenderer->CreateAnimation("Up_Death", "Player.png", 1.0f, 37, 37, false);
	BodyRenderer->CreateAnimation("Left_Death", "Player.png", 1.0f, 62, 62, false);
	BodyRenderer->CreateAnimation("Down_Death", "Player.png", 1.0f, 87, 87, false);
	BodyRenderer->CreateAnimation("RightDown_Death", "Player.png", 1.0f, 112, 112, false);
	BodyRenderer->CreateAnimation("LeftDown_Death", "Player.png", 1.0f, 137, 137, false);
	BodyRenderer->CreateAnimation("LeftUp_Death", "Player.png", 1.0f, 162, 162, false);
	BodyRenderer->CreateAnimation("RightUp_Death", "Player.png", 1.0f, 186, 186, false);

	// Spawn Animations
	BodyRenderer->CreateAnimation("Spawn", "Player.png", 0.15f, 65, 74, true);

	ChangeState(PLAYER_STATE::Spawn);
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

	// State Update
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case PLAYER_STATE::Walk:
		WalkUpdate(_Delta);
		break;
	/*case PLAYER_STATE::Run:
		RunUpdate(_Delta);
		break;*/
	case PLAYER_STATE::Stop:
		StopUpdate(_Delta);
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
	case PLAYER_STATE::Spawn:
		SpawnUpadte(_Delta);
		break;
	default:
		break;
	}
}

void Player::ChangeState(PLAYER_STATE _State)
{
	CurState = _State;
	
	switch (CurState)
	{
	case PLAYER_STATE::Idle:
		IdleStart();
		break;
	case PLAYER_STATE::Walk:
		WalkStart();
		break;
	/*case PLAYER_STATE::Run:
		RunStart();
		break;*/
	case PLAYER_STATE::Stop:
		StopStart();
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
	case PLAYER_STATE::Spawn:
		SpawnStart();
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

	AnimationName += _AnimName.data();
	
	if (0 != _Frame)
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force, _Frame);
	}
	else
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force);
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