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

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);

	Renderer->SetImageScale(GlobalValue::StandardTextureScale);
	Renderer->CreateAnimation("Idle", "Player.png", 1.0f, 31, 31, false);
	Renderer->CreateAnimation("Get", "Player.png", 0.06f, 220, 223, false);
	Renderer->CreateAnimation("Pinned", "Player.png", 10.0f, 62, 62, false);

	GetCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::GetArrow);
	GetCollision->SetCollisionType(ColType::OBBBOX2D);
	GetCollision->Transform.SetLocalScale({12.0f, 12.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::AttackArrow);
	AttackCollision->SetCollisionType(ColType::OBBBOX2D);
	AttackCollision->Transform.SetLocalScale({ 12.0f, 12.0f, 1.0f });

	ChangeState(ARROW_STATE::Hold);

	GameEngineInput::AddInputObject(this);
}

void Arrow::Update(float _Delta)
{
	// ArrowheadCheckPos Update
	ArrowheadCheckPos = FlyingDirectionBasis * ArrowheadPosBasis;

	if (true == DebugingMode &&
		ARROW_STATE::Hold != CurState &&
		ARROW_STATE::PickUp != CurState)
	{
		DebugRender();
	}

	if (PLAYER_STATE::Death == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Hold);
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
	case ARROW_STATE::Pinned:
		PinnedUpdate(_Delta);
		break;
	default:
		break;
	}

	if (ARROW_STATE::Aim != CurState)
	{
		if (StandartPullingForceByHit < PullingForce)
		{
			AttackCollision->On();
		}
		else
		{
			AttackCollision->Off();
		}
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
	case ARROW_STATE::Pinned:
		PinnedStart();
		break;
	default:
		break;
	}
}

void Arrow::MoveAndColCheck(const float4& _MovePos)
{
	float4 _MovePosUnit = FlyingDirectionBasis * 5.0f;

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
				AdjustPosByTileCol();
				if (false == IsBlocked)
				{
					DirSpecularReflection();
				}
				PullingForce /= 2.0f;
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
			AdjustPosByTileCol();
			if (false == IsBlocked)
			{
				DirSpecularReflection();
			}
			PullingForce /= 2.0f;
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

bool Arrow::ArrowColCheckByState(const float4& _MovePos)
{
	switch (CurState)
	{
	case ARROW_STATE::Flying:
		return GetCollision->Collision(COLLISION_TYPE::Boss, std::bind(&Arrow::BossCollisionEvent, this, std::placeholders::_1));
		break;

	case ARROW_STATE::Fallen:
	case ARROW_STATE::Returning:
		if (true == GetCollision->Collision(COLLISION_TYPE::Player, _MovePos))
		{
			Transform.AddLocalPosition(_MovePos);
			OwnerPlayer->OnArrowInBagRenderer();
			ChangeState(ARROW_STATE::PickUp);
			return true;
		}

		return GetCollision->Collision(COLLISION_TYPE::Boss, std::bind(&Arrow::BossCollisionEvent, this, std::placeholders::_1));
		break;

	default:
		break;
	}

	return false;
}

void Arrow::AdjustPosByTileCol()
{
	while(true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos))
	{
		Transform.AddLocalPosition(-FlyingDirectionBasis);
	}
}

void Arrow::AdjustPosByCol()
{
	while (true == GetCollision->Collision(COLLISION_TYPE::Boss))
	{
		Transform.AddLocalPosition(-FlyingDirectionBasis);
	}
}

void Arrow::DirSpecularReflection()
{
	ArrowAngleDeg.Z += 180.0f;
	Transform.SetLocalRotation(ArrowAngleDeg);
	FlyingDirectionBasis = -FlyingDirectionBasis;
	ArrowheadCheckPos = FlyingDirectionBasis * ArrowheadPosBasis;
}

void Arrow::DebugRender()
{
	GameEngineTransform TData;
	TData.SetLocalRotation(ArrowAngleDeg);
	TData.SetLocalScale({ 5.0f, 5.0f });
	TData.SetLocalPosition(Transform.GetLocalPosition() + ArrowheadCheckPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 0, 1 });
}


void Arrow::BossCollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
{
	if (StandartPullingForceByHit < PullingForce)
	{
		BossBase* BossActor = dynamic_cast<BossBase*>(_CollisionGroup[0]->GetParentObject());
		BossActor->HitArrow();
		AdjustPosByCol();
		if (true == BossActor->IsWeaknessActor())
		{
			ChangeState(ARROW_STATE::Pinned);
		}
	}
	else
	{
		AdjustPosByCol();
		ChangeState(ARROW_STATE::Fallen);
	}
}