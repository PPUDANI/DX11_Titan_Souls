#include "PreCompile.h"
#include "SelectText.h"

SelectText::SelectText()
{
}

SelectText::~SelectText()
{
}

void SelectText::Init(std::string_view _Text, const float4& _SelectedColor, const float4& _UnSelectedColor, float _FontScale)
{
	SelectedColor = _SelectedColor;
	UnSelectedColor = _UnSelectedColor;
	TextActor::Init(_Text, SelectedColor, _FontScale);
}

void SelectText::Start()
{
	TextActor::Start();
	GlobalLoad::LoadSpriteSingle("SelectImage.png", "Resource\\Texture\\Title\\");

	SideRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
	SideRenderer->SetSprite("SelectImage.png");
	SideRenderer->Transform.AddLocalPosition({ 0.0f, -19.0f });
	SideRenderer->SetImageScale({ 224.0f , 32.0f });
	SideRenderer->Off();
}