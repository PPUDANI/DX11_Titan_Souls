#include "PreCompile.h"
#include "Sludge.h"

Sludge::Sludge()
{
}

Sludge::~Sludge()
{
}

void Sludge::Start()
{
	BossBase::Start();
	GlobalLoad::LoadSpriteSingle("Sludge.png", "Resource\\Texture\\Boss\\SludgeHeart");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetSprite("Sludge.png");
	Renderer->SetImageScale({256.0f, 256.0f});
}

void Sludge::Update(float _Delta)
{
	BossBase::Update(_Delta);

	if (false == ReverseSclae)
	{
		if (MaxYScale < Scale.Y)
		{
			ReverseSclae = true;
		}
		else
		{
			Scale.Y += WaveSpeed * _Delta;
			Scale.X -= WaveSpeed * _Delta;
		}
	}
	else
	{
		if (MinYScale > Scale.Y)
		{
			ReverseSclae = false;
		}
		else
		{
			Scale.Y -= WaveSpeed * _Delta;
			Scale.X += WaveSpeed * _Delta;
		}
	}

	Renderer->SetImageScale(Scale);

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	Renderer->Transform.SetLocalPosition(RenderPos);
}

// 