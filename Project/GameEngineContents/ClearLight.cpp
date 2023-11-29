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
	GlobalLoad::LoadSpriteCut(32, 32, "Player.png", "Resource\\Texture\\PlayerElement\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	Renderer->SetSprite("Player.png", 809);
	Renderer->SetImageScale({ 32.0f, 32.0f, 1.0f });

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	LightRenderer->SetSprite("Player.png", 810);
	LightRenderer->SetImageScale({ 32.0f, 32.0f, 1.0f });
	LightRenderer->Off();
}

void ClearLight::Update(float _Delta)
{
	
}
