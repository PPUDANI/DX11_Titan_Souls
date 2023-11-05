#include "PreCompile.h"
#include "FadeImage.h"

void FadeImage::FadeInUpdate(float _Delta)
{
	if (Renderer->GetColorData().MulColor.A < 1.0f)
	{
		Renderer->GetColorData().MulColor.A += FadeSpeed * _Delta;
	}
	else if (Renderer->GetColorData().MulColor.A > 1.0f)
	{
		Renderer->GetColorData().MulColor.A = 1.0f;
		CurState = IMAGE_STATE::RESTING;
	}
}


void FadeImage::RestingUpdate(float _Delta)
{
	if (RestingTime > RestingTimer)
	{
		RestingTimer += _Delta;
	}
	else
	{
		RestingTimer = 0.0f;
		CurState = IMAGE_STATE::FADE_OUT;
	}
}

void FadeImage::FadeOutUpdate(float _Delta)
{
	if (Renderer->GetColorData().MulColor.A > 0.0f)
	{
		Renderer->GetColorData().MulColor.A -= FadeSpeed * _Delta;
	}
	else if (Renderer->GetColorData().MulColor.A < 0.0f)
	{
		Renderer->GetColorData().MulColor.A = 0.0f;
		FadeIsEndValue = true;
	}
}
