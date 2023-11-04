#include "PreCompile.h"
#include "Sludge.h"
#include "Heart.h"
#include "SludgeHeartRoom.h"
Sludge::Sludge()
{
}

Sludge::~Sludge()
{
}

void Sludge::Start()
{
	JumpBoss::Start();

	GlobalLoad::LoadSpriteCut(2, 1, "Sludge.png", "Resource\\Texture\\Boss\\SludgeHeart");
	GlobalLoad::LoadSpriteSingle("Shadow.png", "Resource\\Texture\\Boss\\SludgeHeart");
	RenderPosBase = DefaultRenderPosBase;

	// Renderer
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->CreateAnimation("Default", "Sludge.png", 1.0f, 1, 1, false);
	BodyRenderer->CreateAnimation("Hit", "Sludge.png", 0.15f, 0, 1, false);
	BodyRenderer->ChangeAnimation("Default");
	BodyRenderer->SetImageScale({ 256.0f, 256.0f });
	BodyRenderer->Transform.AddLocalPosition(RenderPosBase);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale({ 128.0f, 128.0f });
	ShadowRenderer->Transform.AddLocalPosition(RenderPosBase);

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Sludge);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale(DefaultCollisionSizeBase);

	CollisionParam.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			++DividedCount;
			if (3 >= DividedCount)
			{
				IsDivision = true;
			}
		};

	// Collision setting
	PlayerDetectionRange = CreateComponent<GameEngineCollision>(COLLISION_TYPE::DetectionRange);
	PlayerDetectionRange->SetCollisionType(ColType::AABBBOX2D);
	PlayerDetectionRange->Transform.SetLocalScale(DefaultDetectionRangeSize);


	GravityForce = DefaultGravityForce;
	MoveSpeed = DefaultMoveSpeed;

	ColPosInterval = { 64.0f, 64.0f };
	ChangeState(JUMPBOSS_STATE::Idle);
}

void Sludge::Update(float _Delta)
{
	// JumpStartPos 초기값 설정
	if (float4::ZERO == JumpStartPos)
	{
		JumpStartPos = Transform.GetLocalPosition();
	}

	if (PlayerDetectionRange->Collision(COLLISION_TYPE::Player))
	{
		FindPlayer = true;
	}
	else
	{
		FindPlayer = false;
	}

	RendererSetting();
	// Sludge 분열 (최대 3번)
	if(false == MaxDivision)
	{ 
		Collision->CollisionEvent(COLLISION_TYPE::AttackArrow, CollisionParam);
		if (3 >= DividedCount)
		{
			if (true == IsDivision)
			{
				IsDivision = false;
				SetByDivided();
				AddMoveDirByArrow(90.0f);
				float4 SpawnPos = Transform.GetLocalPosition();
				dynamic_cast<SludgeHeartRoom*>(GetLevel())->SpawnDividedSludge(DividedCount, SpawnPos);

				ChangeState(JUMPBOSS_STATE::Division);
			}
			// Heart가 연결되어있다면 본인 좌표로 이동
			if (nullptr != HeartActor)
			{
				HeartActor->Transform.SetLocalPosition(Transform.GetWorldPosition() + HeartPos);
			}
		}
		else
		{
			MaxDivision = true;
			DividedCount = 3;
			if (nullptr != HeartActor)
			{
				// Sludge와 Heart를 분리
				HeartActor->ChangeState(JUMPBOSS_STATE::OutOfSludge);
				HeartActor->SetOwnerSludge(nullptr);
				Collision->Death();
			}
		}
	}

	JumpBoss::Update(_Delta);

	// Heart position setting
	HeartPos = { 0.0f, RenderScale.Y / 4.0f - 16.0f * static_cast<float>(DividedCount)};

	// Collision Position Setting
	float4 CollisionPos = HeartPos;
	CollisionPos.Y -= 32.0f * (1.0f - DecreaseSize * static_cast<float>(DividedCount));
	Collision->Transform.SetLocalPosition(CollisionPos);
}


void Sludge::DecreaseY(float _SpeedPerSecond)
{
	if (MaxScale * LerpRange > RenderScale.X)
	{
		ExpandDir = SLUDGE_STATE::Decrease;

		RenderScale.Y = std::lerp(RenderScale.Y, MinScale, _SpeedPerSecond);
		RenderScale.X = std::lerp(RenderScale.X, MaxScale, _SpeedPerSecond);

		ShadowRenderScale.X = RenderScale.X * 0.82f;
		ShadowRenderScale.Y = 128.0f * 0.6f + ShadowRenderScale.X * 0.2f;
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Increase;
	}
}

void Sludge::IncreaseY(float _SpeedPerSecond)
{
	if (MaxScale * LerpRange > RenderScale.Y)
	{
		ExpandDir = SLUDGE_STATE::Increase;

		RenderScale.Y = std::lerp(RenderScale.Y, MaxScale, _SpeedPerSecond);
		RenderScale.X = std::lerp(RenderScale.X, MinScale, _SpeedPerSecond);

		ShadowRenderScale.X = RenderScale.X * 0.82f;
		ShadowRenderScale.Y = 128.0f * 0.6f + ShadowRenderScale.X * 0.2f;
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Decrease;
	}
}


void Sludge::RendererSetting()
{
	// Renderers ImageScale & position Setting
	float SizeValue = 1.0f - static_cast<float>(DividedCount) * DecreaseSize;

	BodyRenderer->SetImageScale(RenderScale * SizeValue);
	BodyRenderer->Transform.SetLocalPosition(RenderPosBase);

	ShadowRenderer->SetImageScale(ShadowRenderScale * SizeValue);
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);
}

void Sludge::SetByDivided()
{
	float Count;
	if (4 == DividedCount)
	{
		Count = 3.0f;
	}
	else
	{
		Count = static_cast<float>(DividedCount);
	}
	RenderPosBase = DefaultRenderPosBase * (1.0f - DecreaseSize * Count);
	Collision->Transform.SetLocalScale(DefaultCollisionSizeBase * (1.0f - DecreaseSize * Count));
	MoveSpeed = DefaultMoveSpeed + Count * IncreaseMoveSpeed;
	GravityForce = DefaultGravityForce + Count * IncreaseGravityForce;
}

void Sludge::DividedSludgeInit(int _DividedCount)
{
	DividedCount = _DividedCount;
	AddMoveDirByArrow(-90.0f);
	SetByDivided();
}
