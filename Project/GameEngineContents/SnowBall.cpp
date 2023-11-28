#include "PreCompile.h"
#include "Snowball.h"

SoundRandomPlayer Snowball::ThrowPlayer(GlobalValue::SnowballThrowList);
bool Snowball::SoundIsLoaded = false;

Snowball::Snowball()
{
}

Snowball::~Snowball()
{

}

void Snowball::Start()
{
	GlobalLoad::LoadSpriteSingle("Snowball.png", "Resource\\Texture\\Boss\\Yeti\\");
	SoundLoad();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetSprite("SnowBall.png");
	Renderer->SetImageScale({ 64.0f, 64.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Snowball);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 32.0f, 32.0f });
}

void Snowball::Update(float _Delta)
{
	if (false == SoundIsPlay)
	{
		SoundIsPlay = true;
		ThrowPlayer.RandomPlay();
	}

	if (true == Collision->Collision(COLLISION_TYPE::Player))
	{
		EffectSoundPlay("Impact.ogg");
		if (false == EnymePlayer->InvincibilityModeIsOn())
		{
			EnymePlayer->ChangeState(PLAYER_STATE::Death);
		}
		SnowSpreadParticle();
		Death();
	}

	Transform.AddLocalPosition(AngleToPlayer * SnowballSpeed * _Delta);

	if (true == TileColCheck())
	{
		EffectSoundPlay("Impact.ogg");
		SnowSpreadParticle();
		Death();
	}

	if (RollingSnowCoolTime < RollingSnowCoolTimer)
	{
		RollingSnowCoolTimer -= RollingSnowCoolTime;

		SnowParticle();
		SnowParticle();
		SnowParticle();
	}
	else
	{
		RollingSnowCoolTimer += _Delta;
	}
}

bool Snowball::TileColCheck()
{
	return CurMap->AllColCheck(Transform.GetLocalPosition());
}

void Snowball::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	GlobalLoad::LoadSound("Impact.ogg", "Resource\\Sound\\Player\\Death\\");

	size_t Index = GlobalValue::SnowballThrowList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::SnowballThrowList[i], "Resource\\Sound\\Boss\\Yeti\\");
	}
}
