#include "PreCompile.h"
#include "SpreadParticle.h"

SpreadParticle::SpreadParticle()
{
}

SpreadParticle::~SpreadParticle()
{
}

void SpreadParticle::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);

	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
	Speed = Inst.RandomFloat(200.0f, 500.0f);
}

void SpreadParticle::Update(float _Delta)
{
	UpdateRatio -= _Delta / DeathTime;
	if (0.0f > UpdateRatio)
	{
		Renderer->GetColorData().MulColor.A = 0.0f;
		Death();
		return;
	}

	Renderer->GetColorData().MulColor.A = Alpha * UpdateRatio;
	Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 100.0f * _Delta });
	Transform.AddLocalPosition(BasisVec * Speed * UpdateRatio * _Delta);

}
