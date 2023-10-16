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
	GlobalLoad::LoadSpriteSingle("SludgeShadow.png", "Resource\\Texture\\Boss\\SludgeHeart");

	// Renderer
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->CreateAnimation("Default", "Sludge.png", 1.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Hit", "Sludge.png", 0.1f, 0, 1, true);
	BodyRenderer->ChangeAnimation("Default");
	BodyRenderer->SetImageScale({ 256.0f, 256.0f });

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	ShadowRenderer->SetSprite("SludgeShadow.png");
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetImageScale({ 128.0f, 128.0f });
	ShadowRenderer->Transform.SetLocalPosition({ 0.0f, -24.0f });

	RenderPosBase.Y = -48.0f;
	// Collision setting
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 38.0f, 25.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -8.0f, 0.0f });

	GravityForce = 1200.0f;
	ChangeState(JUMPBOSS_STATE::Idle);
}

void Sludge::Update(float _Delta)
{
	SetMoveDir(JumpStartPos);
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);

	JumpBoss::Update(_Delta);

	BodyRenderer->SetImageScale(RenderScale);
	ShadowRenderer->SetImageScale(ShadowRenderScale);

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 5.0f, 5.0f });

	TData.SetLocalPosition(JumpStartPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y + RenderPosBase.Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);
}


void Sludge::DecreaseY(float _SpeedPerSecond)
{
	if (MaxScale > RenderScale.X)
	{
		ExpandDir = SLUDGE_STATE::Decrease;
		RenderScale.Y -= ExpandDefalutSpeed * _SpeedPerSecond;
		RenderScale.X += ExpandDefalutSpeed * _SpeedPerSecond;

		ShadowRenderScale.X = RenderScale.X * 0.8f;
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Increase;
	}
}

void Sludge::IncreaseY(float _SpeedPerSecond)
{
	if (MaxScale > RenderScale.Y)
	{
		ExpandDir = SLUDGE_STATE::Increase;
		RenderScale.Y += ExpandDefalutSpeed * _SpeedPerSecond;
		RenderScale.X -= ExpandDefalutSpeed * _SpeedPerSecond;

		ShadowRenderScale.X = RenderScale.X * 0.8f;

	}
	else
	{
		ExpandDir = SLUDGE_STATE::Decrease;
	}
}
