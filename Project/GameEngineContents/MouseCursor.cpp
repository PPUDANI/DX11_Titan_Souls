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
	GlobalLoad::LoadSpriteCut(1, 1, "Cursor15.png", "Resource\\Texture\\UI\\MouseCursor\\");
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->Transform.AddLocalPosition(DepthValue::UI);
	Renderer->SetImageScale({ 32.0f, 32.0f });
	Renderer->CreateAnimation("Idle", "Cursor15.png", 1.0f, 0, 0, false);
	Renderer->ChangeAnimation("Idle");
}

void MouseCursor::Update(float _Delta)
{
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->GetWorldMousePos2D());
}
