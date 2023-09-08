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
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(10.0f);
	BodyRenderer->SetSamplerState(SamplerOption::POINT);
	BodyRenderer->CreateAnimation("Idle", "PlayerMove.png", 0.1f, 0, 0, true);
	BodyRenderer->CreateAnimation("Work", "PlayerMove.png", 0.1f, 0, 5, true);

	BodyRenderer->ChangeAnimation("Idle");


}

void Player::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress('W'))
	{
		BodyRenderer->ChangeAnimation("Work");
	}
	else
	{
		BodyRenderer->ChangeAnimation("Idle");
	}
}
