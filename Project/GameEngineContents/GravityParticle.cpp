#include "PreCompile.h"
#include "GravityParticle.h"

GravityParticle::GravityParticle()
{
}

GravityParticle::~GravityParticle()
{
}


void GravityParticle::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
	RandomXSpeed = Inst.RandomFloat(-100.0f, 100.0f);
	RandomYSpeed = Inst.RandomFloat(-100.0f, 0.0f);
}

void GravityParticle::Update(float _Delta)
{
	UpdateRatio -= _Delta / DeathTime;
	if (0.0f > UpdateRatio)
	{
		Renderer->GetColorData().MulColor.A = 0.0f;
		Death();
		return;
	}

	Renderer->GetColorData().MulColor.A = Alpha * UpdateRatio;

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos + float4{RandomXSpeed * _Delta, RandomYSpeed * _Delta });
}
