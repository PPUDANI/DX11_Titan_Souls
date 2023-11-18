#include "PreCompile.h"
#include "TitleLevel.h"


void TitleLevel::GamePadStart()
{
	MainTitleActorOff();
	AcidnerveImage->Off();
	DevolverImage->Off();

	GamePadImage->Reset();
	GamePadImage->On();
}

void TitleLevel::AcidnerveStart()
{
	MainTitleActorOff();
	GamePadImage->Off();
	DevolverImage->Off();

	AcidnerveImage->Reset();
	AcidnerveImage->On();
}

void TitleLevel::DevolverStart()
{
	MainTitleActorOff();
	GamePadImage->Off();
	AcidnerveImage->Off();

	DevolverImage->Reset();
	DevolverImage->On();
}

void TitleLevel::MainTitleStart()
{
	Background2Play("Motif.ogg");
	FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
	FadeInActor->Init(FadeColor::Black);

	GamePadImage->Off();
	AcidnerveImage->Off();
	DevolverImage->Off();

	TileMapActor->On();
	TitleLogo->On();

	StartText->On();
	OptionText->On();
	ExitText->On();

	PrevSelectMenu = SELECT_MENU::START;
	CurSelectMenu = SELECT_MENU::START;
	SetSelectAction();
}


void TitleLevel::GameStartStart()
{
	BackgroundStop();
	Background2Stop();
	AmbienceStop();
	EffectPlay("StartGame.ogg");

	FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
	FadeOutActor->Init(FadeColor::Black, 2.0f);
}

void TitleLevel::GamePadUpdate(float _Delta)
{
	if (true == GamePadImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(TITLE_STATE::ACIDNERVE);
	}
}

void TitleLevel::AcidnerveUpdate(float _Delta)
{
	if (true == AcidnerveImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(TITLE_STATE::DEVOLVER);
	}
}

void TitleLevel::DevolverUpdate(float _Delta)
{
	if (true == DevolverImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(TITLE_STATE::MAIN_TITLE);
	}
}

void TitleLevel::MainTitleUpdate(float _Delta)
{
	if (0.3f < FadeInActor->GetAlpha())
	{
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		switch (CurSelectMenu)
		{
		case SELECT_MENU::START:
			ChangeState(TITLE_STATE::GAME_START);
			break;
		case SELECT_MENU::EXIT:
			GameEngineWindow::WindowLoopOff();
			break;
		case SELECT_MENU::OPTION:
		default:
			break;
		}
	}

	if (GameEngineInput::IsDown('W', this))
	{
		switch (CurSelectMenu)
		{
		case SELECT_MENU::START:
			CurSelectMenu = SELECT_MENU::EXIT;
			break;
		case SELECT_MENU::OPTION:
			CurSelectMenu = SELECT_MENU::START;
			break;
		case SELECT_MENU::EXIT:
			CurSelectMenu = SELECT_MENU::OPTION;
			break;
		default:
			break;
		}
	}

	if (GameEngineInput::IsDown('S', this))
	{
		switch (CurSelectMenu)
		{
		case SELECT_MENU::START:
			CurSelectMenu = SELECT_MENU::OPTION;
			break;
		case SELECT_MENU::OPTION:
			CurSelectMenu = SELECT_MENU::EXIT;
			break;
		case SELECT_MENU::EXIT:
			CurSelectMenu = SELECT_MENU::START;
			break;
		default:
			break;
		}
	}

	if(PrevSelectMenu != CurSelectMenu)
	{
		PrevSelectMenu = CurSelectMenu;
		SetSelectAction();
	}
}

void TitleLevel::GameStartUpdate(float _Delta)
{
	if (nullptr != FadeInActor &&
		true == FadeInActor->FadeIsEnd())
	{
		FadeInActor->Death();
		FadeInActor = nullptr;
	}

	if (nullptr != FadeOutActor)
	{
		if (true == FadeOutActor->FadeIsEnd())
		{
			GameEngineCore::ChangeLevel("01.Floor1");
		}
	}
}