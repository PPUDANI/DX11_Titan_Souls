#include "PreCompile.h"
#include "StartDoor.h"

StartDoor::StartDoor()
{
}

StartDoor::~StartDoor()
{
}

void StartDoor::Start()
{
	GlobalLoad::LoadSpriteCut(2, 1, "ClearLight.png", "Resource\\Texture\\Map\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	Renderer->SetSprite("ClearLight.png", 0);
	Renderer->SetImageScale({ 32.0f, 32.0f, 1.0f });
}

void StartDoor::Update(float _Delta)
{

}
