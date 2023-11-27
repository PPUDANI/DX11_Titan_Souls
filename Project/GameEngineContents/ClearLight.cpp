#include "PreCompile.h"
#include "ClearLight.h"


ClearLight::ClearLight()
{
}

ClearLight::~ClearLight()
{
}

void ClearLight::Start()
{
	GlobalLoad::LoadSpriteCut(2, 1, "ClearLight.png", "Resource\\Texture\\Map\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	Renderer->SetSprite("ClearLight.png", 0);
	Renderer->SetImageScale({ 32.0f, 32.0f, 1.0f });
	Renderer->RenderBaseInfoValue.Target4 = 1;

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	LightRenderer->SetSprite("ClearLight.png", 1);
	LightRenderer->SetImageScale({ 32.0f, 32.0f, 1.0f });
	LightRenderer->RenderBaseInfoValue.Target4 = 1;
	LightRenderer->Off();
}

void ClearLight::Update(float _Delta)
{
	
}
