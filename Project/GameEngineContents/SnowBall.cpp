#include "PreCompile.h"
#include "Snowball.h"

Snowball::Snowball()
{
}

Snowball::~Snowball()
{
}

void Snowball::Start()
{
	GlobalLoad::LoadSpriteSingle("Snowball.png", "Resource\\Texture\\Boss\\Yeti\\");
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetSprite("SnowBall.png");


	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::SnowBall);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 64.0f, 64.0f });

}

void Snowball::Update(float _Delta)
{
}
