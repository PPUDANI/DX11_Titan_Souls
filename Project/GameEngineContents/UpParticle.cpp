#include "PreCompile.h"
#include "UpParticle.h"

UpParticle::UpParticle()
{
}

UpParticle::~UpParticle()
{
}

void UpParticle::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
}

void UpParticle::Update(float _Delta)
{
	DeathTimer -= _Delta;
	if (0.0f > DeathTimer)
	{
		Renderer->GetColorData().MulColor.A = 0.0f;
		Death();
		return;
	}

	Renderer->SetImageScale(Scale * DeathTimer);
	Renderer->GetColorData().MulColor.A = Alpha * DeathTimer;

	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
	Transform.AddLocalPosition({ Inst.RandomFloat(-1.0f, 1.0f) * 50.0f * _Delta, 50.0f * _Delta });
}