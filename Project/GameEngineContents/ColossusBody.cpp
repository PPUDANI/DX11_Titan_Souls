#include "PreCompile.h"
#include "ColossusBody.h"

ColossusBody::ColossusBody()
{
}

ColossusBody::~ColossusBody()
{
}

void ColossusBody::Start()
{
	GlobalLoad::LoadSpriteSingle("ColossusBody.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteSingle("BodyMask.png", "Resource\\Texture\\Boss\\Colossus\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetSprite("ColossusBody.png");
	Renderer->SetImageScale({ 256.0f, 256.0f, 1.0f });
	Renderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	Renderer->RenderBaseInfoValue.Target0 = 0;
	Renderer->RenderBaseInfoValue.Target3 = 1;

	MaskRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
	MaskRenderer->SetPivotType(PivotType::Bottom);
	MaskRenderer->SetSprite("BodyMask.png");
	MaskRenderer->SetImageScale({ 256.0f, 256.0f, 1.0f });
	MaskRenderer->Transform.SetLocalPosition({ 0.0f, -128.0f });
	MaskRenderer->RenderBaseInfoValue.Target0 = 0;
	MaskRenderer->RenderBaseInfoValue.Target4 = 1;
}

void ColossusBody::Update(float _Delta)
{

}
