#include "PreCompile.h"
#include "Yeti.h"
#include "YetiRoom.h"

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
	Collision->Transform.SetLocalScale({ 40.0f, 20.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 60.0f });
	Collision->Off();

	BodyCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetLocalScale({ 70.0f, 30.0f, 1.0f });

	BodyCollision2 = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	BodyCollision2->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision2->Transform.SetLocalScale({ 70.0f, 30.0f, 1.0f });

	RollingCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBodyAttack);
	RollingCollision->SetCollisionType(ColType::AABBBOX2D);
	RollingCollision->Transform.SetLocalScale({ 80.0f, 50.0f, 1.0f });
	RollingCollision->Transform.SetLocalPosition(RollingColStandardPos);
	RollingCollision->Off();

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			ChangeState(YETI_STATE::Idle);
		};

	NextStateBuffer = YETI_STATE::Throwing;

	SetDirToDeg(270.0f);
	DirectionUpdate();
}

void Yeti::Update(float _Delta)
{
	if (YETI_STATE::Sleep == CurState &&
		true == IsBodyHitByArrow)
	{
		WakeUpYeti();
	}

	if (true == IsWeaknessHitByArrow)
	{
		IsWeaknessHitByArrow = false;
		ChangeState(YETI_STATE::Hit);
	}

	BossBase::Update(_Delta);

	BodyCollision->CollisionEvent(COLLISION_TYPE::AttackArrow, Param);
	BodyCollision2->CollisionEvent(COLLISION_TYPE::AttackArrow, Param);

	if (YETI_STATE::Blocked != CurState)
	{
		JumpStartPos = Transform.GetLocalPosition();
	}

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

	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + ShadowStandardPos);
	
	if (true == GetLevel()->IsDebug)
	{
		GameEngineTransform TData;
		TData.SetLocalRotation(Transform.GetLocalRotationEuler());
		TData.SetLocalScale({ 5.0f, 5.0f });

		TData.SetLocalPosition(JumpStartPos);
		GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

		TData.SetLocalPosition(LeftPos + Transform.GetLocalPosition());
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(RightPos + Transform.GetLocalPosition());
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(UpPos + Transform.GetLocalPosition());
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(DownPos + Transform.GetLocalPosition());
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });
	}

	if (true == YetiIsWakeUp())
	{
		CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition()) / 2.0f;
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
	Collision->On();
	YetiIsWakeUpValue = true;
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

void Yeti::DirReflection()
{
	MoveAngle = -MoveAngle;
	MoveDirBasis = -MoveDirBasis;
}

void Yeti::SetColScaleByDir()
{
	float4 BodyPosByDir;
	float4 BodyScaleByDir;

	float4 Body2PosByDir;
	float4 Body2ScaleByDir;

	float4 WeeknessPosByDir;

	switch (CurDir)
	{
	case YETI_DIRECTION::Right:
		BodyPosByDir = { 5.0f, -10.0f };
		BodyScaleByDir = { 50.0f, 70.0f, 1.0f };
		Body2PosByDir = float4::ZERO;
		Body2ScaleByDir = float4::ZERO;
		WeeknessPosByDir = { -12.0f, 5.0f };
		break;
	case YETI_DIRECTION::RightUp:
		BodyPosByDir = { 5.0f, 23.0f };
		BodyScaleByDir = { -70.0f, 20.0f , 1.0f };
		Body2PosByDir = { 25.0f, -17.0f };
		Body2ScaleByDir = { 30.0f, 60.0f, 1.0f };
		WeeknessPosByDir = { -10.0f, 3.0f };
		break;
	case YETI_DIRECTION::Up:
		BodyPosByDir = { 0.0f, 30.0f };
		BodyScaleByDir = { 80.0f, 30.0f , 1.0f };
		Body2PosByDir = float4::ZERO;
		Body2ScaleByDir = float4::ZERO;
		WeeknessPosByDir = { 0.0f, 0.0f };
		break;
	case YETI_DIRECTION::LeftUp:
		BodyPosByDir = { -5.0f, 23.0f };
		BodyScaleByDir = { 70.0f, 20.0f , 1.0f };
		Body2PosByDir = { -25.0f, -17.0f };
		Body2ScaleByDir = { 30.0f, 60.0f, 1.0f };
		WeeknessPosByDir = { 10.0f, 3.0f };
		break;
	case YETI_DIRECTION::Left:
		BodyPosByDir = { -5.0f, -10.0f };
		BodyScaleByDir = { 50.0f, 70.0f, 1.0f };
		Body2PosByDir = float4::ZERO;
		Body2ScaleByDir = float4::ZERO;
		WeeknessPosByDir = { 12.0f, 5.0f };
		break;
	case YETI_DIRECTION::LeftDown:
		BodyPosByDir = { 15.0f, -30.0f };
		BodyScaleByDir = { 40.0f, 40.0f, 1.0f };
		Body2PosByDir = { -20.0f, -15.0f };
		Body2ScaleByDir = { -30.0f, 40.0f, 1.0f };
		WeeknessPosByDir = { 10.0f, 0.0f };
		break;
	case YETI_DIRECTION::Down:
		BodyPosByDir = { 0.0f, -30.0f };
		BodyScaleByDir = { 90.0f, 40.0f, 1.0f };
		Body2PosByDir = float4::ZERO;
		Body2ScaleByDir = float4::ZERO;
		WeeknessPosByDir = { 0.0f, 00.0f };
		break;
	case YETI_DIRECTION::RightDown:
		BodyPosByDir = { -15.0f, -30.0f };
		BodyScaleByDir = { 40.0f, 40.0f, 1.0f };
		Body2PosByDir = { 20.0f, -15.0f };
		Body2ScaleByDir = { 30.0f, 40.0f, 1.0f };
		WeeknessPosByDir = { -10.0f, 0.0f };
		break;
	default:
		break;
	}

	BodyCollision->Transform.SetLocalPosition(BodyColStandardPos + BodyPosByDir + RendererStandardPos);
	BodyCollision->Transform.SetLocalScale(BodyScaleByDir);

	if (true == BodyCollision2->IsUpdate())
	{
		BodyCollision2->Transform.SetLocalPosition(BodyColStandardPos + Body2PosByDir + RendererStandardPos);
		BodyCollision2->Transform.SetLocalScale(Body2ScaleByDir);
	}
	
	Collision->Transform.SetLocalPosition(BodyColStandardPos + WeeknessPosByDir + RendererStandardPos);
}


bool Yeti::TileColCheck(float4& _MovePos)
{
	TILE_COLLISION_TYPE Type = TILE_COLLISION_TYPE::EMPTY;
	bool ColCheck = false;
	if (true == CurMap->ColCheck(LeftPos + Transform.GetLocalPosition(), Type))
	{
		AdjustLeftPosByTileCol(_MovePos);
		ColCheck = true;
	}

	if (true == CurMap->ColCheck(RightPos + Transform.GetLocalPosition(), Type))
	{
		AdjustRightPosByTileCol(_MovePos);
		ColCheck = true;
	}

	if (true == CurMap->ColCheck(UpPos + Transform.GetLocalPosition(), Type))
	{
		AdjustUpPosByTileCol(_MovePos);
		ColCheck = true;
	}

	if (true == CurMap->ColCheck(DownPos + Transform.GetLocalPosition(), Type))
	{
		AdjustDownPosByTileCol(_MovePos);
		ColCheck = true;
	}

	return ColCheck;
}

void Yeti::AdjustLeftPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(LeftPos + _MovePos))
	{
		_MovePos += float4::RIGHT;
	}
}

void Yeti::AdjustRightPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(RightPos + _MovePos))
	{
		_MovePos += float4::LEFT;
	}
}

void Yeti::AdjustUpPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(UpPos + _MovePos))
	{
		_MovePos += float4::DOWN;
	}
}

void Yeti::AdjustDownPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(DownPos + _MovePos))
	{
		_MovePos += float4::UP;
	}
}

void Yeti::Gravity(float _Delta)
{
	if (JumpStartPos.Y > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = JumpStartPos.Y;
		Transform.SetLocalPosition(MovePos);

		ChangeState(YETI_STATE::Landing);
		return;
	}

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);
}

void Yeti::ThrowSnowball()
{
	RENDERING_ORDER Order = RENDERING_ORDER::Y_SORT_ENTITY;
	switch (CurDir)
	{
	case YETI_DIRECTION::LeftDown:
	case YETI_DIRECTION::Down:
	case YETI_DIRECTION::RightDown:
		Order = RENDERING_ORDER::Y_SORT_ENTITY_FRONT;
		break;
	default:
		break;
	}

	float4 StartPos = Transform.GetLocalPosition() + float4{ 0.0f, 40.0f };
	SetMoveDir(StartPos);

	dynamic_cast<YetiRoom*>(GetLevel())->SpawnSnowBall(StartPos, MoveDirBasis, Order);
}

void Yeti::DropIcicle()
{
	float4 FirstTargetPos = Transform.GetLocalPosition() + float4{ 0.0f, 40.0f };
	float4 IcicleMoveAngle = SetMoveDirReturn(FirstTargetPos);
	dynamic_cast<YetiRoom*>(GetLevel())->SpawnIcicle(FirstTargetPos, IcicleMoveAngle);
}

void Yeti::ShakingScreenInit()
{
	ShakingEnd = false;
	ScreenShakingTime = 1.0f;
	ScreenShakingTimer = 0.0f;
	ShakingPerFrame = 0.2f;
	ShakingLerpValue = 15.0f;
}
