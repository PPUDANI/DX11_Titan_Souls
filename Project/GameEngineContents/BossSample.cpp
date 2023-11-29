#include  "PreCompile.h"
#include "BossSample.h"

BossSample::BossSample()
{
}

BossSample::~BossSample()
{
}

void BossSample::Start()
{
	GlobalLoad::LoadSpriteCut(7, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");

	// Renderer setting
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyRenderer->SetSprite("Heart.png", 1);
	BodyRenderer->SetPivotType(PivotType::Center);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Weakness);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({30.0f, 30.0f, 1.0f});
	Collision->Transform.SetLocalPosition({ 0.0f, 20.0f });

	Collision2 = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision2->SetCollisionType(ColType::AABBBOX2D);
	Collision2->Transform.SetLocalScale({ 64.0f, 64.0f, 1.0f });
}

void BossSample::Update(float _Delta)
{

}

