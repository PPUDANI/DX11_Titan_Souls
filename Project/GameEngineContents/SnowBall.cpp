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
	Renderer->SetImageScale({ 64.0f, 64.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::YetiAttack);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 32.0f, 32.0f });
}

void Snowball::Update(float _Delta)
{
	Transform.AddLocalPosition(AngleToPlayer * SnowballSpeed * _Delta);

	if (true == TileColCheck() ||
		Collision->Collision(COLLISION_TYPE::Player))
	{
		Death();
	}
}

bool Snowball::TileColCheck()
{
	return CurMap->AllColCheck(Transform.GetLocalPosition());
}