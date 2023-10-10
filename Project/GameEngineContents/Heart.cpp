#include "PreCompile.h"
#include "Heart.h"


Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{
	GlobalLoad::LoadSpriteCut(6, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Monster);
	Renderer->SetImageScale({ 64.0f, 64.0f });

	Renderer->CreateAnimation("InSludge", "Heart.png", 10.0f, 0, 0, false);
	Renderer->CreateAnimation("Idle", "Heart.png", 10.0f, 1, 1, false);
	Renderer->CreateAnimation("Jump", "Heart.png", 0.2f, 2, 3, false);
	Renderer->CreateAnimation("Landing", "Heart.png", 0.2f, 4, 5, false);

	Renderer->ChangeAnimation("Idle");

	ChangeState(HEART_STATE::Idle);

}

void Heart::Update(float _Delta)
{
	switch (CurState)
	{
	case HEART_STATE::InSludge:
		InSludgeUpdate(_Delta);
		break;
	case HEART_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case HEART_STATE::Jump:
		JumpUpdate(_Delta);
		break;
	case HEART_STATE::Fall:
		FallUpdate(_Delta);
		break;
	case HEART_STATE::Landing:
		LandingUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Heart::ChangeState(HEART_STATE _State)
{
	if (CurState == _State)
	{
		return;
	}

	CurState = _State;

	switch (CurState)
	{
	case HEART_STATE::InSludge:
		InSludgeStart();
		break;
	case HEART_STATE::Idle:
		IdleStart();
		break;
	case HEART_STATE::Jump:
		JumpStart();
		break;
	case HEART_STATE::Fall:
		FallStart();
		break;
	case HEART_STATE::Landing:
		LandingStart();
		break;
	default:
		break;
	}
}


void Heart::Gravity(float _Delta)
{
	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);

	if (StartYPos > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = StartYPos;
		Transform.SetLocalPosition(MovePos);
		ChangeState(HEART_STATE::Landing);
	}
}

