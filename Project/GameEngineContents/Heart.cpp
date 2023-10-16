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

	// Renderer setting
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::AlphaLess);
	Renderer->Transform.SetLocalPosition(RenderPosBase);
	Renderer->SetImageScale({ 64.0f, 64.0f });

	Renderer->CreateAnimation("InSludge", "Heart.png", 10.0f, 0, 0, false);
	Renderer->CreateAnimation("Idle", "Heart.png", 10.0f, 1, 1, false);
	Renderer->CreateAnimation("Jump", "Heart.png", 0.2f, 2, 3, false);
	Renderer->CreateAnimation("Landing", "Heart.png", 0.2f, 4, 5, false);
	Renderer->CreateAnimation("Death", "Heart.png", 10.0f, 6, 6, false);

	// Collision setting
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 38.0f, 25.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -8.0f, 0.0f });

	GravityForce = 1200.0f;

	ChangeState(JUMPBOSS_STATE::Idle);
}

void Heart::Update(float _Delta)
{
	SetMoveDir(JumpStartPos);

	JumpBoss::Update(_Delta);


	if (true == IsHitArrow)
	{
		ChangeState(JUMPBOSS_STATE::Death);
		return;
	}

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 5.0f, 5.0f });

	TData.SetLocalPosition(JumpStartPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y - 8.0f;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	Renderer->Transform.SetLocalPosition(RenderPos);
}


