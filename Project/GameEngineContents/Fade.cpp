#include "PreCompile.h"
#include "Fade.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::Start()
{
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetCameraOrder(ECAMERAORDER::UI);
	
	FadeRenderer->SetImageScale({1500.0f, 1000.0f, 0.0f});
	FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };
	FadeRenderer->GetColorData().MulColor.A = 0.0f;
}

void Fade::Update(float _Delta)
{
	switch (Mode)
	{
	case FadeMode::FadeIn:
		if (FadeRenderer->GetColorData().MulColor.A > TargetValue)
		{
			FadeRenderer->GetColorData().MulColor.A -= FadeSpeed * _Delta;
		}
		else if (FadeRenderer->GetColorData().MulColor.A < TargetValue)
		{
			FadeRenderer->GetColorData().MulColor.A = TargetValue;
			FadeEnd = true;
		}
		break;

	case FadeMode::FadeOut:
		if (FadeRenderer->GetColorData().MulColor.A < TargetValue)
		{
			FadeRenderer->GetColorData().MulColor.A += FadeSpeed * _Delta;
		}
		else if (FadeRenderer->GetColorData().MulColor.A > TargetValue)
		{
			FadeRenderer->GetColorData().MulColor.A = TargetValue;
			FadeEnd = true;
		}
		break;

	case FadeMode::Off:
		break;
	default:
		break;
	}
}