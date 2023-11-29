#include "PreCompile.h"
#include "ClearLight2.h"


ClearLight2::ClearLight2()
{
}

ClearLight2::~ClearLight2()
{
}

void ClearLight2::Start()
{
	GlobalLoad::LoadSpriteSingle("ClearLight.png", "Resource\\Texture\\Map\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::BGA_Tile);
	Renderer->SetSprite("ClearLight.png");
	Renderer->SetImageScale({ 32.0f, 32.0f, 1.0f });
	Renderer->Off();
}

void ClearLight2::Update(float _Delta)
{
}
