#include "PreCompile.h"
#include "Heart.h"


Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{
	JumpBoss::Start();

	GlobalLoad::LoadSpriteCut(7, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");
	GlobalLoad::LoadSpriteSingle("Shadow.png", "Resource\\Texture\\Boss\\SludgeHeart");
	RenderPosBase = { 0.0f, -24.0f };

	// Renderer setting
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::AlphaLess);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });
	BodyRenderer->CreateAnimation("InSludge", "Heart.png", 10.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Idle", "Heart.png", 10.0f, 1, 1, false);
	BodyRenderer->CreateAnimation("Jump", "Heart.png", 0.2f, 2, 3, false);
	BodyRenderer->CreateAnimation("Landing", "Heart.png", 0.2f, 4, 5, false);
	BodyRenderer->CreateAnimation("Death", "Heart.png", 10.0f, 6, 6, false);
	BodyRenderer->Transform.AddLocalPosition(RenderPosBase);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale({ 56.0f, 16.0f });
	ShadowRenderer->Transform.AddLocalPosition(RenderPosBase);

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Boss);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 38.0f, 25.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 24.0f, 0.0f });

	GravityForce = 1500.0f;
	MoveSpeed = 150.0f;
	ChangeState(JUMPBOSS_STATE::InSludge);
}

void Heart::Update(float _Delta)
{
	SetMoveDir(JumpStartPos);

	if (true == IsHitArrow)
	{
		ChangeState(JUMPBOSS_STATE::Death);
		return;
	}

	JumpBoss::Update(_Delta);
}

void Heart::RendererSetting()
{
	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y + RenderPosBase.Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);

	RenderPos.Z += 0.1f;
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase + RenderPos);

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 5.0f, 5.0f });
	TData.SetLocalPosition(JumpStartPos + GlobalValue::DebugDepth);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
}