#include "PreCompile.h"
#include "FadeScreenOverlay.h"

FadeScreenOverlay::FadeScreenOverlay()
{
}

FadeScreenOverlay::~FadeScreenOverlay()
{
}

void FadeScreenOverlay::Start()
{
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI\\Fade");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetImageScale({ GlobalValue::WindowScale.X + 10.0f, GlobalValue::WindowScale.Y + 10.0f });
	FadeRenderer->RenderBaseInfoValue.Target4 = 1;
	FadeRatio = 0.0f;
}

void FadeScreenOverlay::Update(float _Delta)
{
	if (true == FadeOutOnValue)
	{
		if (1.0f < FadeRatio)
		{
			FadeRenderer->GetColorData().MulColor.A = MaxFadeAlpha;
			FadeOutOnValue = false;
		}
		else
		{
			FadeRatio += _Delta / FadeOutTime;
			FadeRenderer->GetColorData().MulColor.A = FadeRatio * MaxFadeAlpha;
		}
	}
	else if (true == FadeInOnValue)
	{
		if (0.0f > FadeRatio)
		{
			FadeRenderer->GetColorData().MulColor.A = 0.0f;
			FadeInOnValue = false;
		}
		else
		{
			FadeRatio -= _Delta / FadeInTime;
			FadeRenderer->GetColorData().MulColor.A = FadeRatio * MaxFadeAlpha;
		}
	}

	FadeRenderer->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
}
