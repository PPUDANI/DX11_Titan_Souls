#include "PreCompile.h"
#include "FadeIn.h"

FadeIn::FadeIn()
{
}

FadeIn::~FadeIn()
{
}

void FadeIn::Start()
{
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI\\Fade");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_FRONT);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetCameraOrder(ECAMERAORDER::UI);

	FadeRenderer->SetImageScale({ GlobalValue::WindowScale.X + 10.0f, GlobalValue::WindowScale.Y + 10.0f });
	FadeRenderer->GetColorData().MulColor.A = StartAlpha;
}

void FadeIn::Update(float _Delta)
{
	if (false == FadeEnd)
	{
		if (FadeRenderer->GetColorData().MulColor.A > 0.0f)
		{
			FadeRenderer->GetColorData().MulColor.A -= FadeSpeed * _Delta;
		}
		else if (FadeRenderer->GetColorData().MulColor.A < 0.0f)
		{
			FadeRenderer->GetColorData().MulColor.A = 0.0f;
			FadeEnd = true;
		}
	}
}