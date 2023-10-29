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
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FadeRenderer->SetCameraOrder(ECAMERAORDER::UI);
	FadeRenderer->SetImageScale({100.0f, 100.0f, 0.0f});
	FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };
	FadeRenderer->GetColorData().MulColor.A = 0.0f;
}

void Fade::Update(float _Delta)
{
	if (FadeMode::FadeOut == Mode)
	{
		if (FadeRenderer->GetColorData().MulColor.A < MaxFade)
		{
			FadeRenderer->GetColorData().MulColor.A += FadeSpeed * _Delta;
		}
		else if(FadeRenderer->GetColorData().MulColor.A > MaxFade)
		{
			FadeRenderer->GetColorData().MulColor.A = MaxFade;
		}
	}
	else if (FadeMode::FadeIn == Mode)
	{
		FadeRenderer->GetColorData().MulColor.A -= FadeSpeed * _Delta;
	}
}