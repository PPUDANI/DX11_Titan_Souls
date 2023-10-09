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
	WindowScale = GameEngineCore::MainWindow.GetScale();

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
	ArrowheadCheckPos = ArrowheadPosBasis * FlyingDirectionBasis;

	if (true == DebugingMode &&
		ARROW_STATE::Hold != CurState &&
		ARROW_STATE::PickUp != CurState)
	{
		DebugRender();
	}

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

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	if (0.0f > CameraPos.X - WindowScale.hX())
	{
		CameraPos.X = WindowScale.hX();
	}
	if (TileEndPos.X < CameraPos.X + WindowScale.hX())
	{
		CameraPos.X = TileEndPos.X - WindowScale.hX();
	}
	if (0.0f < CameraPos.Y + WindowScale.hY())
	{
		CameraPos.Y = -WindowScale.hY();
	}
	if (TileEndPos.Y > CameraPos.Y - WindowScale.hY())
	{
		CameraPos.Y = TileEndPos.Y + WindowScale.hY();
	}
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(CameraPos);
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

void Arrow::NextColCkeck(float4 _MovePos)
{
	float4 _MovePosUnit = FlyingDirectionBasis * 10.0f;

	unsigned int Index = static_cast<unsigned int>(abs((abs(FlyingDirectionBasis.X) > abs(FlyingDirectionBasis.Y)) ? _MovePos.X / _MovePosUnit.X : _MovePos.Y / _MovePosUnit.Y));

	for (unsigned int i = 0; i < Index; ++i)
	{
		float Index = static_cast<float>(i);
		if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + (_MovePosUnit * Index) , TileColType))
		{
			Transform.AddLocalPosition(_MovePosUnit * Index);
			AdjustPosByCol();
			DirSpecularReflection();
			PullingForce /= 5.0f;
			return;
		}
		else
		{
			continue;
		}
	}

	if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + _MovePos, TileColType))
	{
		Transform.AddLocalPosition(_MovePos);
		AdjustPosByCol();
		DirSpecularReflection();
		PullingForce /= 5.0f;
		return;
	}

	Transform.AddLocalPosition(_MovePos);
}

void Arrow::AdjustPosByCol()
{
	while(true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos))
	{
		Transform.AddLocalPosition(-FlyingDirectionBasis);
	}

}

void Arrow::DirSpecularReflection()
{
	ArrowAngleDeg.Z += 180.0f;
	Transform.SetLocalRotation(ArrowAngleDeg);
	FlyingDirectionBasis = -FlyingDirectionBasis;
	ArrowheadCheckPos = ArrowheadPosBasis * FlyingDirectionBasis;
}

void Arrow::DebugRender()
{
	GameEngineTransform TData;
	TData.SetLocalRotation(ArrowAngleDeg);
	TData.SetLocalScale({ 5.0f, 5.0f });
	TData.SetLocalPosition(Transform.GetLocalPosition() + ArrowheadCheckPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 0, 1 });
}
