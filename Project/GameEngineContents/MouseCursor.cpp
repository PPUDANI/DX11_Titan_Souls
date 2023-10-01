#include "PreCompile.h"
#include "MouseCursor.h"

MouseCursor::MouseCursor()
{
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::Start()
{
	GlobalLoad::LoadSpriteCut(1, 1, "Cursor.png", "Resource\\Texture\\UI\\");
	GlobalLoad::LoadSpriteCut(1, 1, "Cursor2.png", "Resource\\Texture\\UI\\");
	GlobalLoad::LoadSpriteCut(1, 1, "Cursor3.png", "Resource\\Texture\\UI\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	Renderer->SetImageScale(GlobalValue::StandardTextureScale);

	Renderer->CreateAnimation("Idle", "Cursor3.png", 1.0f, 0, 0, false);

	Renderer->ChangeAnimation("Idle");
}

void MouseCursor::Update(float _Delta)
{
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->GetWorldMousePos2D());
}
