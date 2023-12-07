#include "PreCompile.h"
#include "WeaknessActor.h"

WeaknessActor::WeaknessActor()
{
}

WeaknessActor::~WeaknessActor()
{
}

void WeaknessActor::Start()
{
	GlobalLoad::LoadSpriteCut(7, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");
	GlobalLoad::LoadSpriteSingle("Shadow.png", "Resource\\Texture\\Boss\\SludgeHeart");

	// Renderer setting
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyRenderer->SetSprite("Heart.png", 1);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });


	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetImageScale({ 64.0f, 32.0f, 1.0f });
	ShadowRenderer->Transform.SetLocalPosition({ 0.0f, -16.0f });
	ShadowRenderer->GetColorData().MulColor.A = 0.5f;

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Weakness);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 40.0f, 40.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -5.0f });
}

void WeaknessActor::Update(float _Delta)
{
	if (true == IsWeaknessHitByArrow)
	{
		IsWeaknessHitByArrow = false;
		BodyRenderer->SetSprite("Heart.png", 6);
		BodyRenderer->SetImageScale({ 64.0f, 64.0f });
	}
}
