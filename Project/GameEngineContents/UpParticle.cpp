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
	UpdateRatio -= _Delta / DeathTime;
	if (0.0f > UpdateRatio)
	{
		Renderer->GetColorData().MulColor.A = 0.0f;
		Death();
		return;
	}

	Renderer->SetImageScale(Scale * UpdateRatio);
	Renderer->GetColorData().MulColor.A = Alpha * UpdateRatio;
	Renderer->Transform.AddLocalRotation({0.0f, 0.0f, 100.0f * _Delta });
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
	Transform.AddLocalPosition({ Inst.RandomFloat(-1.0f, 1.0f) * 50.0f * _Delta, 50.0f * _Delta });
}