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
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Overlay);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetCameraOrder(ECAMERAORDER::UI);

	FadeRenderer->SetImageScale({ GlobalValue::WindowScale.X + 10.0f, GlobalValue::WindowScale.Y + 10.0f });
}

void ScreenOverlay::Update(float _Delta)
{

}