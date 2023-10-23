#include "PreCompile.h"
#include "Sludge.h"
#include "Heart.h"
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
	RenderPosBase = {0.0f, -64.0f};

	// Renderer
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->CreateAnimation("Default", "Sludge.png", 1.0f, 1, 1, false);
	BodyRenderer->CreateAnimation("Hit", "Sludge.png", 0.15f, 0, 1, false);
	BodyRenderer->ChangeAnimation("Default");
	BodyRenderer->SetImageScale({ 256.0f, 256.0f });
	BodyRenderer->Transform.AddLocalPosition(RenderPosBase);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale({ 128.0f, 128.0f });
	ShadowRenderer->Transform.AddLocalPosition(RenderPosBase);

	PressMarkRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	PressMarkRenderer->SetPivotType(PivotType::Bottom);
	PressMarkRenderer->SetSprite("PressMark.png");
	PressMarkRenderer->SetImageScale({ 128.0f, 128.0f });
	PressMarkRenderer->Transform.AddLocalPosition(RenderPosBase);

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Sludge);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 160.0f, 112.0f, 0.0f });

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			BodyRenderer->ChangeAnimation("Hit", true);
			IsHitArrow = false;
			IsDivision = true;
			Collision->Off();
		};

	GravityForce = 1200.0f;
	MoveSpeed = 250.0f;
	SludgeDividedSize = 1.0f + DividedCount * SizeReduction;

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

	// Heart position setting
	HeartPos = { 0.0f, RenderScale.Y / (4.0f * SludgeDividedSize) - 3.0f * SludgeDividedSize };

	// Collision Position Setting
	float4 CollisionPos = HeartPos;
	Collision->Transform.SetLocalPosition(CollisionPos + GlobalValue::DebugDepth);

	if (4.0f > DividedCount)
	{
		if (nullptr != HeartActor)
		{
			HeartActor->Transform.SetLocalPosition(Transform.GetWorldPosition() + HeartPos);
		}
		
		if (true == IsDivision)
		{
			IsDivision = false;
			DividedCount++;
			SizeReduction *= 1.4f;
			SludgeDividedSize = 1.0f + DividedCount * SizeReduction;
			MoveSpeed += 20.0f;
			GravityForce += 100.0f;
			RenderPosBase *= 0.66f;
			Collision->Transform.SetLocalScale(Collision->Transform.GetLocalScale() / 1.5f);
		}
	}
	else
	{
		HeartActor->SetOwnerSludge(nullptr);
		Death();
	}
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
	BodyRenderer->SetImageScale(RenderScale / SludgeDividedSize);
	ShadowRenderer->SetImageScale(ShadowRenderScale / SludgeDividedSize);
	PressMarkRenderer->SetImageScale(ShadowRenderScale / SludgeDividedSize);
	PressMarkRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = BodyRenderer->Transform.GetWorldPosition().Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);

	RenderPos.Z += 0.01f;
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase + RenderPos);
}
