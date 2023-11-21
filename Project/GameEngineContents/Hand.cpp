#include "PreCompile.h"
#include "Hand.h"

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::Init(HAND_DIR _Dir)
{
	CurDir = _Dir;
	switch (_Dir)
	{
	case HAND_DIR::Left:
		break;
	case HAND_DIR::Right:
		Renderer->LeftFlip();
		break;
	default:
		break;
	}

	ChangeState(HAND_STATE::Sleep);

}

void Hand::Start()
{
	GlobalLoad::LoadSpriteCut(3, 1, "ColossusHand.png", "Resource\\Texture\\Boss\\Colossus");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetImageScale({ 128.0f, 128.0f , 1.0f});
	Renderer->CreateAnimation("Idle", "ColossusHand.png", 1.0f, 0, 0, true);
	Renderer->CreateAnimation("InHide", "ColossusHand.png", 0.5f, 0, 2, false);
	Renderer->CreateAnimation("InHover", "ColossusHand.png", 0.5f, 2, 0, false);

	Renderer->ChangeAnimation("Idle");

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBodyAttack);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 50.0f, 36.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 40.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 50.0f, 36.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 40.0f });
}

void Hand::Update(float _Delta)
{

	switch (CurState)
	{
	case HAND_STATE::Sleep:
		SleepUpdate(_Delta);
		break;
	case HAND_STATE::Hide:
		HideUpdate(_Delta);
		break;
	case HAND_STATE::Hover:
		HoverUpdate(_Delta);
		break;
	case HAND_STATE::Fall:
		FallUpdate(_Delta);
		break;
	case HAND_STATE::Land:
		LandUpdate(_Delta);
		break;
	default:
		break;
	}

}

void Hand::ChangeState(HAND_STATE _State)
{
	CurState = _State;

	switch (CurState)
	{
	case HAND_STATE::Sleep:
		SleepStart();
		break;
	case HAND_STATE::Hide:
		HideStart();
		break;
	case HAND_STATE::Hover:
		HoverStart();
		break;
	case HAND_STATE::Fall:
		FallStart();
		break;
	case HAND_STATE::Land:
		LandStart();
		break;
	default:
		break;
	}
}
