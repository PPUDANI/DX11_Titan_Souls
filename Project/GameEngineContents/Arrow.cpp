#include "PreCompile.h"
#include "Arrow.h"

bool Arrow::SoundIsLoaded = false;
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

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::AttackArrow);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 10.0f, 10.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -10.0f, 1.0f });

	PickUpCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::PickupArrow);
	PickUpCollision->SetCollisionType(ColType::SPHERE2D);
	PickUpCollision->Transform.SetLocalScale({ 10.0f, 10.0f, 1.0f });


	SoundLoad();


	ChangeState(ARROW_STATE::Hold);
	GameEngineInput::AddInputObject(this);
}

void Arrow::Update(float _Delta)
{
	// ArrowheadCheckPos Update
	ArrowheadCheckPos = FlyingDirectionBasis * ArrowheadPosBasis;

	if (true == GetLevel()->IsDebug &&
		ARROW_STATE::Hold != CurState &&
		ARROW_STATE::PickUp != CurState)
	{
		DebugRender();
	}

	if (PLAYER_STATE::Death == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Hold);
		OwnerPlayer->GetArrow();
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
	float4 _MovePosUnit = FlyingDirectionBasis;

	int IndexInt = static_cast<int>(abs((abs(FlyingDirectionBasis.X) > abs(FlyingDirectionBasis.Y)) ? _MovePos.X / _MovePosUnit.X : _MovePos.Y / _MovePosUnit.Y));

	for (int i = 0; i < IndexInt; ++i)
	{
		float Index = static_cast<float>(i);
		float4 MovePos = _MovePosUnit * Index;

		if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + MovePos, TileColType))
		{
			if (ARROW_STATE::Returning != CurState)
			{
				Transform.AddLocalPosition(MovePos);
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

	if (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos + _MovePos, TileColType))
	{
		if (ARROW_STATE::Returning != CurState)
		{
			Transform.AddLocalPosition(_MovePos);
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
	bool Res = false;
	switch (CurState)
	{
	case ARROW_STATE::Flying:
		Res = Collision->Collision(COLLISION_TYPE::BossBody, std::bind(&Arrow::BossBodyCollisionEvent, this, std::placeholders::_1, _MovePos)) ||
			Collision->Collision(COLLISION_TYPE::Weakness, std::bind(&Arrow::WeaknessCollisionEvent, this, std::placeholders::_1, _MovePos));
		return Res;

	case ARROW_STATE::Fallen:
		if (true == PickUpCollision->Collision(COLLISION_TYPE::Player, _MovePos))
		{
			Transform.AddLocalPosition(_MovePos);
			OwnerPlayer->OnArrowInBagRenderer();
			ChangeState(ARROW_STATE::PickUp);
			return true;
		}

		Res = Collision->Collision(COLLISION_TYPE::BossBody, std::bind(&Arrow::BossBodyCollisionEvent, this, std::placeholders::_1, _MovePos)) ||
			Collision->Collision(COLLISION_TYPE::Weakness, std::bind(&Arrow::WeaknessCollisionEvent, this, std::placeholders::_1, _MovePos));
		return Res;

	case ARROW_STATE::Returning:
		if (true == PickUpCollision->Collision(COLLISION_TYPE::Player, _MovePos))
		{
			Transform.AddLocalPosition(_MovePos);
			OwnerPlayer->OnArrowInBagRenderer();
			ChangeState(ARROW_STATE::PickUp);
			return true;
		}

		Res = Collision->Collision(COLLISION_TYPE::BossBody, std::bind(&Arrow::BossBodyCollisionEvent, this, std::placeholders::_1, _MovePos)) ||
			Collision->Collision(COLLISION_TYPE::Weakness, std::bind(&Arrow::WeaknessCollisionEvent, this, std::placeholders::_1, _MovePos));
		return Res;

	default:
		break;
	}

	return false;
}

void Arrow::AdjustPosByTileCol()
{
	while (true == CurMap->ArrowColCheck(Transform.GetLocalPosition() + ArrowheadCheckPos))
	{
		Transform.AddLocalPosition(-FlyingDirectionBasis);
	}
}

void Arrow::AdjustPosByCol()
{
	while (true == Collision->Collision(COLLISION_TYPE::Weakness) ||
		true == Collision->Collision(COLLISION_TYPE::BossBody))
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



void Arrow::WeaknessCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup, float4 _MovePos)
{
	if (StandartPullingForceByHit < PullingForce)
	{
		BossBase* BossActor = dynamic_cast<BossBase*>(_CollisionGroup[0]->GetParentObject());
		BossActor->WeaknessHitByArrow();
		Transform.AddLocalPosition(_MovePos);
		AdjustPosByCol();
		ChangeState(ARROW_STATE::Pinned);
	}
	else
	{
		Transform.AddLocalPosition(_MovePos);
		AdjustPosByCol();
		ChangeState(ARROW_STATE::Fallen);
		PullingForce /= 2.0f;
		DirSpecularReflection();
	}
}

void Arrow::BossBodyCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup, float4 _MovePos)
{
	BossBase* BossActor = dynamic_cast<BossBase*>(_CollisionGroup[0]->GetParentObject());
	BossActor->BodyHitByArrow();
	Transform.AddLocalPosition(_MovePos);
	AdjustPosByCol();

	PullingForce /= 2.0f;
	if (ARROW_STATE::Flying == CurState)
	{
		ChangeState(ARROW_STATE::Fallen);
		DirSpecularReflection();
	}
}

