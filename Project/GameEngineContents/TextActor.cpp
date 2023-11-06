#include "PreCompile.h"
#include "TextActor.h"

TextActor::TextActor()
{
}

TextActor::~TextActor()
{
}

void TextActor::Init(std::string_view _Text)
{

	std::string Text = GameEngineString::ToUpperReturn(_Text);

	GlobalLoad::LoadSpriteCut(26, 3, "Text.png", "Resource\\Texture\\Title");

	size_t TextSize = Text.size();
	Renderers.assign(TextSize, nullptr);
	for (int i = 0; i < TextSize; ++i)
	{
		char Word = Text[i];
		int AsciiNum = static_cast<int>(Word);
	}
}

void TextActor::Start()
{
	
}

void TextActor::Update(float _Delta)
{

}