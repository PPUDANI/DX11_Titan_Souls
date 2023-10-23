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
	GlobalLoad::LoadSpriteSingle("PressMark.png", "Resource\\Texture\\Boss\\SludgeHeart");
	RenderPosBase = DefaultRenderPosBase;

	// Renderer
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
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

	PressMarkRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	PressMarkRenderer->SetPivotType(PivotType::Bottom);
	PressMarkRenderer->SetSprite("PressMark.png");
	PressMarkRenderer->SetImageScale({ 128.0f, 128.0f });
	PressMarkRenderer->Transform.AddLocalPosition(RenderPosBase);

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Sludge);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale(DefaultCollisionSizeBase);

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			BodyRenderer->ChangeAnimation("Hit", true);
			IsHitArrow = false;
			IsDivision = true;
			Collision->Off();
		};

	GravityForce = DefaultGravityForce;
	MoveSpeed = DefaultMoveSpeed;
	RandomMoveValue = true;
	ChangeState(JUMPBOSS_STATE::Idle);

}

void Sludge::Update(float _Delta)
{
	if (float4::ZERO == JumpStartPos)
	{
		JumpStartPos = Transform.GetLocalPosition();
	}

	Collision->CollisionEvent(COLLISION_TYPE::AttackArrow, Param);

	JumpBoss::Update(_Delta);

	if (4.0f > DividedCount &&
		false == MaxDivision)
	{
		if (nullptr != HeartActor)
		{
			HeartActor->Transform.SetLocalPosition(Transform.GetWorldPosition() + HeartPos);
		}
		
		if (true == IsDivision)
		{
			DividedCount++;
			IsDivision = false;
			SetByDivided();

			float4 SpawnPos = Transform.GetLocalPosition();
			Transform.AddLocalPosition(-50.0f / DividedCount);
			SpawnPos.X += 50.0f;
			dynamic_cast<SludgeHeartRoom*>(GetLevel())->SpawnDividedSludge(DividedCount, SpawnPos);
		}
	}
	else
	{
		MaxDivision = true;
		DividedCount = 3.0f;
		if (nullptr != HeartActor)
		{
			// Sludge와 Heart를 분리
			HeartActor->SetOwnerSludge(nullptr);
		}
	}

	// Heart position setting
	HeartPos = { 0.0f, RenderScale.Y / 4.0f - 16.0f * DividedCount};

	// Collision Position Setting
	float4 CollisionPos = HeartPos;
	CollisionPos.Y -= 48.0f * (1.0f - DecreaseSize * DividedCount);
	Collision->Transform.SetLocalPosition(CollisionPos + GlobalValue::DebugDepth);
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
	float SizeValue = 1.0f - DividedCount * DecreaseSize;

	BodyRenderer->SetImageScale(RenderScale * SizeValue);
	ShadowRenderer->SetImageScale(ShadowRenderScale * SizeValue);
	PressMarkRenderer->SetImageScale(ShadowRenderScale * SizeValue);
	PressMarkRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = BodyRenderer->Transform.GetWorldPosition().Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);

	RenderPos.Z += 0.01f;
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase + RenderPos);
}

void Sludge::SetByDivided()
{
	RenderPosBase = DefaultRenderPosBase * (1.0f - DecreaseSize * DividedCount);
	Collision->Transform.SetLocalScale(DefaultCollisionSizeBase * (1.0f - DecreaseSize * DividedCount));

	MoveSpeed = DefaultMoveSpeed + DividedCount * IncreaseMoveSpeed;
	GravityForce = DefaultGravityForce + DividedCount * IncreaseGravityForce;
}

void Sludge::DividedSludgeInit(float _DividedCount)
{
	DividedCount = _DividedCount;
	Collision->Off();
	SetByDivided();
}
