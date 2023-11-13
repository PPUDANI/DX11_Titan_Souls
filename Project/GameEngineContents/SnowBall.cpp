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

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::SnowBall);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 48.0f, 48.0f });
}

void Snowball::Update(float _Delta)
{
	Transform.AddLocalPosition(AngleToPlayer * SnowballSpeed * _Delta);

	if (true == TileColCheck())
	{
		Death();
	}
}

bool Snowball::TileColCheck()
{
	return CurMap->AllColCheck(Transform.GetLocalPosition());
}