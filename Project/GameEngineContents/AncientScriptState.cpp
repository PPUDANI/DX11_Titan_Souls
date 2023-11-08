#include "PreCompile.h"
#include "AncientScript.h"

void AncientScript::FadeInUpdate(float _Delta)
{
	if (AlphaValue < 1.0f)
	{
		AlphaValue += FadeSpeed * _Delta;
	}
	else if (AlphaValue > 1.0f)
	{
		AlphaValue = 1.0f;
		CurState = FADE_STATE::RESTING;
	}

	for (size_t i = 0; i < TextNum; ++i)
	{
		if (nullptr == Renderers[i])
		{
			continue;
		}

		Renderers[i]->GetColorData().MulColor.A = AlphaValue;
	}
}


void AncientScript::RestingUpdate(float _Delta)
{
	if (RestingTime > RestingTimer)
	{
		RestingTimer += _Delta;
	}
	else
	{
		RestingTimer = 0.0f;
		CurState = FADE_STATE::FADE_OUT;
	}
}

void AncientScript::FadeOutUpdate(float _Delta)
{
	if (AlphaValue > 0.0f)
	{
		AlphaValue -= FadeSpeed * _Delta;
	}
	else if (AlphaValue < 0.0f)
	{
		AlphaValue = 0.0f;
		FadeIsEndValue = true;
	}

	for (size_t i = 0; i < TextNum; ++i)
	{
		if (nullptr == Renderers[i])
		{
			continue;
		}

		Renderers[i]->GetColorData().MulColor.A = AlphaValue;
	}
}
