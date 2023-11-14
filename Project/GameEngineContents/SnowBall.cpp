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

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Snowball);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 32.0f, 32.0f });
}

void Snowball::Update(float _Delta)
{
	if (true == Collision->Collision(COLLISION_TYPE::Player))
	{
		if (false == EnymePlayer->InvincibilityModeIsOn())
		{
			EnymePlayer->ChangeState(PLAYER_STATE::Death);
		}
		Death();
	}

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