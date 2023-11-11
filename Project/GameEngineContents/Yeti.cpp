#include "PreCompile.h"
#include "Yeti.h"

Yeti::Yeti()
{
}

Yeti::~Yeti()
{
}

void Yeti::Start()
{
	BossBase::Start();

	// Create Renderer
	CreateYetiAnimation();
	SetDirection(YETI_DIRECTION::Down);
	ChangeState(YETI_STATE::Sleep);

	// Create Collision
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Weakness);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 50.0f, 50.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 60.0f });
	WeaknessActorValue = true;


	BodyCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	BodyCollision->SetCollisionType(ColType::SPHERE2D);
	BodyCollision->Transform.SetLocalScale({ 90.0f, 90.0f, 1.0f });

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			ChangeState(YETI_STATE::Idle);
		};

	//GameEngineInput::AddInputObject(this);
}

void Yeti::Update(float _Delta)
{
	if (YETI_STATE::Sleep == CurState &&
		true == IsHitArrow)
	{
		WakeUpYeti();
	}
	BossBase::Update(_Delta);
	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();

	BodyCollision->CollisionEvent(COLLISION_TYPE::AttackArrow, Param);

	switch (CurState)
	{
	case YETI_STATE::Sleep:
		SleepUpdate(_Delta);
		break;
	case YETI_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case YETI_STATE::Throwing:
		ThrowingUpdate(_Delta);
		break;
	case YETI_STATE::ReadyToRoll:
		ReadyToRollUpdate(_Delta);
		break;
	case YETI_STATE::Rolling:
		RollingUpdate(_Delta);
		break;
	case YETI_STATE::Landing:
		LandingUpdate(_Delta);
		break;
	case YETI_STATE::Blocked:
		BlockedUpdate(_Delta);
		break;
	case YETI_STATE::Hit:
		HitUpdate(_Delta);
		break;
	case YETI_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Yeti::ChangeState(YETI_STATE _State)
{
	//if (CurState == _State)
	//{
	//	return;
	//}

	CurState = _State;

	switch (CurState)
	{
	case YETI_STATE::Sleep:
		SleepStart();
		break;
	case YETI_STATE::Idle:
		IdleStart();
		break;
	case YETI_STATE::Throwing:
		ThrowingStart();
		break;
	case YETI_STATE::ReadyToRoll:
		ReadyToRollStart();
		break;
	case YETI_STATE::Rolling:
		RollingStart();
		break;
	case YETI_STATE::Landing:
		LandingStart();
		break;
	case YETI_STATE::Blocked:
		BlockedStart();
		break;
	case YETI_STATE::Hit:
		HitStart();
		break;
	case YETI_STATE::Death:
		DeathStart();
		break;
	default:
		break;
	}
}

void Yeti::WakeUpYeti()
{
	ChangeState(YETI_STATE::Idle);
}

void Yeti::SetDirection(YETI_DIRECTION _Dir)
{
	CurDir = _Dir;
}

void Yeti::DirectionUpdate()
{
	int DividedAngleIndex = static_cast<int>(MoveAngle.Z / 22.5f);

	switch (DividedAngleIndex)
	{
	case 0:
	case 15:
		SetDirection(YETI_DIRECTION::Right);
		break;
	case 1:
	case 2:
		SetDirection(YETI_DIRECTION::RightUp);
		break;
	case 3:
	case 4:
		SetDirection(YETI_DIRECTION::Up);
		BodyCollision->Transform.SetLocalPosition({ 0.0f, 80.0f });
		break;
	case 5:
	case 6:
		SetDirection(YETI_DIRECTION::LeftUp);
		break;
	case 7:
	case 8:
		SetDirection(YETI_DIRECTION::Left);
		break;
	case 9:
	case 10:
		SetDirection(YETI_DIRECTION::LeftDown);
		break;
	case 11:
	case 12:
		SetDirection(YETI_DIRECTION::Down);
		break;
	case 13:
	case 14:
		SetDirection(YETI_DIRECTION::RightDown);
		break;
	default:
		break;
	}
	SetColScaleByDir();
}

void Yeti::SetColScaleByDir()
{
	float4 PosByDir;

	switch (CurDir)
	{
	case YETI_DIRECTION::Right:
		PosByDir = float4{ 30.0f, 0.0f };
		break;
	case YETI_DIRECTION::RightUp:
		PosByDir = float4{ 25.0f, 25.0f };
		break;
	case YETI_DIRECTION::Up:
		PosByDir = float4{ 0.0f, 30.0f };
		break;
	case YETI_DIRECTION::LeftUp:
		PosByDir = float4{ -25.0f, 25.0f };
		break;
	case YETI_DIRECTION::Left:
		PosByDir = float4{ -30.0f, 0.0f };
		break;
	case YETI_DIRECTION::LeftDown:
		PosByDir = float4{ -25.0f, -25.0f };
		break;
	case YETI_DIRECTION::Down:
		PosByDir = float4{ 0.0f, -30.0f };
		break;
	case YETI_DIRECTION::RightDown:
		PosByDir = float4{ 25.0f, -25.0f };
		break;
	default:
		break;
	}

	BodyCollision->Transform.SetLocalPosition(BodyColStandardPos + PosByDir);
}
