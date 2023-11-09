#include "PreCompile.h"
#include "FadeImage.h"

FadeImage::FadeImage()
{
}

FadeImage::~FadeImage()
{
}

void FadeImage::Init(std::string_view _ImageName, float _FadeSpeed /*= 1.0f*/, float _RestingTime /*= 1.0f*/)
{
	Renderer->SetSprite(_ImageName);
	FadeSpeed = 1.0f / _FadeSpeed;
	RestingTime = _RestingTime;
}

void FadeImage::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_FRONT);
	Renderer->SetCameraOrder(ECAMERAORDER::UI);
	Renderer->GetColorData().MulColor.A = 0.0f;
}

void FadeImage::Update(float _Delta)
{
	if (false == FadeIsEndValue)
	{
		switch (CurState)
		{
		case IMAGE_STATE::FADE_IN:
			FadeInUpdate(_Delta);
			break;
		case IMAGE_STATE::RESTING:
			RestingUpdate(_Delta);
			break;
		case IMAGE_STATE::FADE_OUT:
			FadeOutUpdate(_Delta);
			break;
		default:
			break;
		}
	}
}
