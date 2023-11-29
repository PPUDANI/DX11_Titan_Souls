#include "PreCompile.h"
#include "TextActor.h"

TextActor::TextActor()
{
}

TextActor::~TextActor()
{
}

void TextActor::Init(std::string_view _Text, const float4& _Color,float _FontScale)
{
	Text = _Text;
	Color = _Color;
	FontScale = _FontScale;
	FontRenderer->SetText("TSfont", Text, FontScale, Color, FW1_CENTER);
}

void TextActor::SetColor(const float4& _Color)
{
	Color = _Color;
	FontRenderer->SetText("TSfont", Text, FontScale, Color, FW1_CENTER);
}

void TextActor::Start()
{
	FontRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI);
}
