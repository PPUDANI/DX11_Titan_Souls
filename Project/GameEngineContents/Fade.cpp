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
	FadeRenderer->SetImageScale({1500.0f, 1000.0f, 0.0f});
	FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };
	FadeRenderer->GetColorData().MulColor.A = 0.0f;
}

void Fade::Update(float _Delta)
{
	FadeRenderer->GetColorData().MulColor.A += 0.5f * _Delta;

}