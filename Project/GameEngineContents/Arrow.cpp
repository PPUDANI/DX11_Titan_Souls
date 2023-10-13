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

	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->SetImageScale(GlobalValue::StandardTextureScale);
	Renderer->Transform.AddLocalPosition(DepthValue::TempValue);
	Renderer->CreateAnimation("Idle", "Player.png", 1.0f, 31, 31, false);
	Renderer->CreateAnimation("Get", "Player.png", 0.07f, 220, 223, false);

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Arrow);
	Collision->SetCollisionType(ColType::OBBBOX2D);
	Collision->Transform.SetLocalScale({12.0f, 24.0f, 1.0f });

	ChangeState(ARROW_STATE::Hold);

	GameEngineInput::AddInputObject(this);
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

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y + 3.25f;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	Renderer->Transform.SetLocalPosition(RenderPos);
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

void Arrow::MoveAndColCheck(float4& _MovePos)
{
	float4 _MovePosUnit = FlyingDirectionBasis * 10.0f;

	int IndexInt = static_cast<int>(abs((abs(FlyingDirectionBasis.X) > abs(FlyingDirectionBasis.Y)) ? _MovePos.X / _MovePosUnit.X : _MovePos.Y / _MovePosUnit.Y));

	for (int i = 0; i < IndexInt; ++i)
	{
		float Index = static_cast<float>(i);
		float4 MovePos = _MovePosUnit * Index;
		if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + MovePos, TileColType))
		{
			if (ARROW_STATE::Returning != CurState)
			{
				Transform.AddLocalPosition(_MovePosUnit * Index);
				AdjustPosByCol();
				if (false == IsBlocked)
				{
					DirSpecularReflection();
				}
				PullingForce /= 10.0f;
			}
			else
			{
				IsBlocked = true;
				ChangeState(ARROW_STATE::Fallen);
			}
			return;
		}
		if (true == ArrowColCheckByState(MovePos))
		{
			return;
		}
	}

	float Indexfloat = static_cast<float>(IndexInt);
	if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + _MovePos, TileColType))
	{
		if (ARROW_STATE::Returning != CurState)
		{
			Transform.AddLocalPosition(_MovePosUnit * Indexfloat);
			AdjustPosByCol();
			if (false == IsBlocked)
			{
				DirSpecularReflection();
			}
			PullingForce /= 10.0f;
		}
		else
		{
			IsBlocked = true;
			ChangeState(ARROW_STATE::Fallen);
		}
		return;
	}

	if (true == ArrowColCheckByState(_MovePos))
	{
		return;
	}
	Transform.AddLocalPosition(_MovePos);
}

bool Arrow::ArrowColCheckByState(float4& _MovePos)
{
	switch (CurState)
	{
	case ARROW_STATE::Flying:

		break;
	case ARROW_STATE::Fallen:
	case ARROW_STATE::Returning:
		if (true == Collision->Collision(COLLISION_TYPE::Player, _MovePos))
		{
			Transform.AddLocalPosition(_MovePos);
			ChangeState(ARROW_STATE::PickUp);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
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
