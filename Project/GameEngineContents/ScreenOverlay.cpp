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
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI\\");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	FadeRenderer->SetSprite("FadeTexture.png");
	FadeRenderer->SetImageScale({ GlobalValue::WindowScale.X + 10.0f, GlobalValue::WindowScale.Y + 10.0f });
	FadeRenderer->RenderBaseInfoValue.Target4 = 1;
}

void ScreenOverlay::Update(float _Delta)
{
	FadeRenderer->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
}