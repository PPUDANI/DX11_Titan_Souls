#include "PreCompile.h"
#include "AncientScript.h"

AncientScript::AncientScript()
{
}

AncientScript::~AncientScript()
{
}

void AncientScript::Init(std::string_view _Text, FONT_TYPE _Type, const float4& _TextSize, float _Interval)
{
	std::string Text = GameEngineString::ToUpperReturn(_Text);

	TextNum = Text.size(); // Null문자 제거

	Type = _Type;

	Renderers.assign(TextNum, nullptr);

	for (int i = 0; i < TextNum; ++i)
	{
		char Word = Text[i];
		int Index = ChangeAsciiToIndex(static_cast<int>(Word));
		if (0 > Index)
		{
			continue;
		}

		Renderers[i] = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_FRONT);
		Renderers[i]->SetCameraOrder(ECAMERAORDER::UI);
		Renderers[i]->SetSprite("Text.png", static_cast<unsigned int>(Index));
		Renderers[i]->SetImageScale(_TextSize);

		// Middle Sort
		float TextPosUnit = static_cast<float>(i) - (static_cast<float>(TextNum) / 2.0f);
		float Interval = _Interval;

		Renderers[i]->Transform.AddLocalPosition({ (_TextSize.X * TextPosUnit) + Interval * TextPosUnit, 0.0f });
		Renderers[i]->GetColorData().MulColor.A = AlphaValue;
	}
}

void AncientScript::FadeInit(float _FadeSpeed /*= 1.0f*/, float _RestingTime /*= 1.0f*/)
{
	FadeSpeed = 1.0f / _FadeSpeed;
	RestingTime = _RestingTime;
}

void AncientScript::Start()
{
	GlobalLoad::LoadSpriteCut(26, 2, "Text.png", "Resource\\Texture\\UI");
}

void AncientScript::Update(float _Delta)
{
	switch (CurState)
	{
	case FADE_STATE::FADE_IN:
		FadeInUpdate(_Delta);
		break;
	case FADE_STATE::RESTING:
		RestingUpdate(_Delta);
		break;
	case FADE_STATE::FADE_OUT:
		FadeOutUpdate(_Delta);
		break;
	default:
		break;
	}
}

int AncientScript::ChangeAsciiToIndex(int _AsciiNum)
{
	int Result = _AsciiNum - 'A';
	if (0 <= Result)
	{
		if (FONT_TYPE::ANCIENT == Type)
		{
			return Result + 26;
		}
		else if (FONT_TYPE::ENGLISH == Type)
		{
			return Result;
		}
	}

	return -1;
}
