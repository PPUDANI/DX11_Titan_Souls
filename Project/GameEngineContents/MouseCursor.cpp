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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	Renderer->SetImageScale({ 32.0f, 32.0f });
	Renderer->CreateAnimation("Idle", "Cursor.png", 1.0f, 0, 0, false);
	Renderer->ChangeAnimation("Idle");
	Renderer->RenderBaseInfoValue.Target3 = 1;
}

void MouseCursor::Update(float _Delta)
{
	float4 MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	MousePos.Z += -500.0f;
	Transform.SetLocalPosition(MousePos);
}
