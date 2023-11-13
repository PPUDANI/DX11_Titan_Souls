#include "PreCompile.h"
#include "Icicle.h"

Icicle::Icicle()
{
}

Icicle::~Icicle()
{
}

void Icicle::Init(const float4& _TargetPoint)
{
	TargetPoint = _TargetPoint;
	Transform.SetLocalPosition(TargetPoint + StandardHeight);
}

void Icicle::Start()
{
	GlobalLoad::LoadSpriteCut(8, 1, "Icicle.png", "Resource\\Texture\\Boss\\Yeti\\");
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);

	GameEngineRandom Inst;
	Inst.SetSeed(reinterpret_cast<__int64>(this));
	int RandomIndex = Inst.RandomInt(0, 3);
	int StuckAnimationIndex = RandomIndex + 4;

	Renderer->SetSprite("Icicle.png", RandomIndex);
	Renderer->CreateAnimation("StuckInGround", "Icicle.png", 1.0f, StuckAnimationIndex, StuckAnimationIndex, false);

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);

}

void Icicle::Update(float _Delta)
{
	if (TargetPoint.Y < Transform.GetLocalPosition().Y)
	{
		GravityValue -= GravityForce * _Delta;
		Transform.AddLocalPosition(GravityValue * _Delta);
	}
	else
	{
		Transform.SetLocalPosition(TargetPoint);
		Renderer->ChangeAnimation("StuckInGround");
	}
}