#include "PreCompile.h"
#include "ScreenOverlay.h"

ScreenOverlay::ScreenOverlay()
{
}

ScreenOverlay::~ScreenOverlay()
{
}

void ScreenOverlay::Start()
{
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI\\Fade");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetImageScale({ GlobalValue::WindowScale.X + 10.0f, GlobalValue::WindowScale.Y + 10.0f });
	FadeRenderer->RenderBaseInfoValue.Target4 = 1;
	FadeRatio = 0.0f;
}

void ScreenOverlay::Update(float _Delta)
{
	if (true == FadeOnValue)
	{
		if (1.0f < FadeRatio)
		{
			FadeRenderer->GetColorData().MulColor.A = MaxFadeAlpha;
			FadeOnValue = false;
		}
		else
		{
			FadeRatio += _Delta / FadeTime;
			FadeRenderer->GetColorData().MulColor.A = FadeRatio * MaxFadeAlpha;
		}
	}

	FadeRenderer->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
}