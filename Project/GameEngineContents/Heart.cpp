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
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });
	BodyRenderer->CreateAnimation("InSludge", "Heart.png", 10.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Idle", "Heart.png", 10.0f, 1, 1, false);
	BodyRenderer->CreateAnimation("Jump", "Heart.png", 0.2f, 2, 3, false);
	BodyRenderer->CreateAnimation("Landing", "Heart.png", 0.2f, 4, 5, false);
	BodyRenderer->CreateAnimation("Death", "Heart.png", 10.0f, 6, 6, false);
	BodyRenderer->Transform.AddLocalPosition(RenderPosBase);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale({ 60.0f, 20.0f });
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase + float4{ 0.0f, -4.0f });

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Weakness);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 30.0f, 30.0f, 1.0f });

	GravityForce = 1200.0f;
	MoveSpeed = 150.0f;

	ColPosInterval = { 64.0f, 64.0f };

	ChangeState(JUMPBOSS_STATE::InSludge);
}

void Heart::Update(float _Delta)
{
	if (true == IsWeaknessHitByArrow)
	{
		ChangeState(JUMPBOSS_STATE::Death);
		return;
	}

	PosUpdate();

	JumpBoss::Update(_Delta);

	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);
}
