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
}

void GravityParticle::Update(float _Delta)
{
	if (0.0f > Renderer->GetColorData().MulColor.A)
	{
		Death();
	}
	else
	{
		Renderer->GetColorData().MulColor.A -= _Delta;
	}

	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
}

