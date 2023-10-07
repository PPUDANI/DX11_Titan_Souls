#include "PreCompile.h"
#include "Arrow.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Arrow);
	Renderer->SetImageScale(GlobalValue::StandardTextureScale);

	Renderer->CreateAnimation("Idle", "Player.png", 1.0f, 31, 31, false);
	Renderer->CreateAnimation("Get", "Player.png", 0.07f, 220, 223, false);

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Arrow);
	Collision->SetCollisionType(ColType::OBBBOX2D);
	Collision->Transform.SetLocalScale({12.0f, 24.0f, 1.0f });

	ChangeState(ARROW_STATE::Hold);
}

void Arrow::Update(float _Delta)
{
	// ArrowheadCheckPos Update
	ArrowheadCheckPos = ArrowheadPosBasis * FlyingDirection;

	if (true == DebugingMode &&
		ARROW_STATE::Hold != CurState &&
		ARROW_STATE::PickUp != CurState)
	{
		DebugRender();
	}

	ColCkeck();

	switch (CurState)
	{
	case ARROW_STATE::Hold:
		HoldUpdate(_Delta);
		break;
	case ARROW_STATE::Aim:
		AimUpdate(_Delta);
		break;
	case ARROW_STATE::Flying:
		FlyingUpdate(_Delta);
		break;
	case ARROW_STATE::Fallen:
		FallenUpdate(_Delta);
		break;
	case ARROW_STATE::Returning:
		ReturningUpdate(_Delta);
		break;
	case ARROW_STATE::PickUp:
		PickUpUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Arrow::ChangeState(ARROW_STATE _State)
{
	if (CurState == _State)
	{
		return;
	}

	CurState = _State;

	switch (CurState)
	{
	case ARROW_STATE::Hold:
		HoldStart();
		break;
	case ARROW_STATE::Aim:
		AimStart();
		break;
	case ARROW_STATE::Flying:
		FlyingStart();
		break;
	case ARROW_STATE::Fallen:
		FallenStart();
		break;
	case ARROW_STATE::Returning:
		ReturningStart();
		break;
	case ARROW_STATE::PickUp:
		PickUpStart();
		break;
	default:
		break;
	}
}

void Arrow::ColCkeck()
{
	ArrowheadColCheck = CurMap->ArrowColCheck(Transform.GetWorldPosition() + ArrowheadCheckPos, ColType);
}


void Arrow::DebugRender()
{
	GameEngineTransform TData;
	TData.SetLocalRotation(ArrowAngleDeg);
	TData.SetLocalScale({ 5.0f, 5.0f });
	TData.SetLocalPosition(Transform.GetLocalPosition() + ArrowheadCheckPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 0, 1 });
}
