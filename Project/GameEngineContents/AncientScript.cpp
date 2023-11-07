#include "PreCompile.h"
#include "AncientScript.h"

AncientScript::AncientScript()
{
}

AncientScript::~AncientScript()
{
}

void AncientScript::Init(std::string_view _Text)
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

void AncientScript::Start()
{

}

void AncientScript::Update(float _Delta)
{

}