#include "PreCompile.h"
#include "EndingLevel.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	GlobalLoad::LoadSpriteSingle("TitleLogo.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSound("Motif.ogg", "Resource\\Sound\\Title\\");
	TitanSoulsRogo = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	TitanSoulsRogo->Init("TitleLogo.png", 2.0f, 2.0f);
	TitanSoulsRogo->SetScale({ 546.0f, 254.0f, 1.0f });
	TitanSoulsRogo->Off();
	EndingText = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	EndingText->Init("THANK YOU FOR PLAYING", FONT_TYPE::ENGLISH, { 32.0f, 32.0f });
}

void EndingLevel::Update(float _Delta)
{
	LevelBase::Update(_Delta);

	if (DelayTime < DelayTimer)
	{
		if (false == TitanSoulsRogo->IsUpdate())
		{
			BackgroundPlay("Motif.ogg");
			TitanSoulsRogo->On();
		}
	}
	else
	{
		DelayTimer += _Delta;
	}

	if (true == TitanSoulsRogo->FadeIsEnd())
	{
		EndingText->FadeInit(2.0f, 2.0f);
	}

	if (true == EndingText->FadeIsEnd())
	{
		GameEngineCore::ChangeLevel("00.TitleLevel");
	}
}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BackgroundStop();
}
