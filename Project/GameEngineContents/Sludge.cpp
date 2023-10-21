#include "PreCompile.h"
#include "Sludge.h"

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
	BodyRenderer->CreateAnimation("Default", "Sludge.png", 1.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Hit", "Sludge.png", 0.1f, 0, 1, true);
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



	GravityForce = 1500.0f;
	MoveSpeed = 250.0f;
	
	ChangeState(JUMPBOSS_STATE::Idle);
}

void Sludge::Update(float _Delta)
{
	if (float4::ZERO == JumpStartPos)
	{
		JumpStartPos = Transform.GetLocalPosition();
	}

	SetMoveDir(JumpStartPos);
	
	JumpBoss::Update(_Delta);

	// Heart position setting
	HeartPos = { 0.0f, RenderScale.Y / (4.0f * DividedCount) - 24.0f * DividedCount };

	// Collision Position Setting
	float4 CollisionPos = HeartPos;
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
	BodyRenderer->SetImageScale(RenderScale / DividedCount);
	ShadowRenderer->SetImageScale(ShadowRenderScale / DividedCount);
	PressMarkRenderer->SetImageScale(ShadowRenderScale / DividedCount);
	PressMarkRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = BodyRenderer->Transform.GetWorldPosition().Y + RenderPosBase.Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);

	RenderPos.Z += 0.01f;
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase + RenderPos);

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 5.0f, 5.0f });
	TData.SetLocalPosition(JumpStartPos + GlobalValue::DebugDepth);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
}
