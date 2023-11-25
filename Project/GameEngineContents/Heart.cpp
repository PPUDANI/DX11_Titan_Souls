#include "PreCompile.h"
#include "Heart.h"

SoundRandomPlayer Heart::LandPlayer(GlobalValue::HeartList);
bool Heart::SoundIsLoaded = false;

Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{
	JumpBoss::Start();
	SoundLoad();
	GlobalLoad::LoadSpriteCut(7, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");
	GlobalLoad::LoadSpriteSingle("Shadow.png", "Resource\\Texture\\Boss\\SludgeHeart");
	RenderPosBase = { 0.0f, -28.0f };

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

	ShadowStandardPos = { 0.0f, -32.0f };
	ShadowStandardScale = { 70.0f, 35.0f };
	ShadowStandardAlpha = 0.6f;
	ShadowScaleConstant = 5.0f;
	ShadowAlphaConstant = 2.0f;

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale(ShadowStandardScale);
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + ShadowStandardPos);
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha;

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
	}

	PosUpdate();

	JumpBoss::Update(_Delta);
	ShadowVariableByHeightUpdate(JumpStartPos);
	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + ShadowStandardPos);
}

void Heart::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	size_t Index = GlobalValue::HeartList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::HeartList[i], "Resource\\Sound\\Boss\\SludgeHeart\\");
	}
}