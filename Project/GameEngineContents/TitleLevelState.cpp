#include "PreCompile.h"
#include "TitleLevel.h"


void TitleLevel::GamePadStart()
{
	GamePadImage->On();
}

void TitleLevel::AcidnerveStart()
{
	AcidnerveImage->On();
}

void TitleLevel::DevolverStart()
{
	DevolverImage->On();
}

void TitleLevel::MainTitleStart()
{
	FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
	FadeInActor->Init(FadeColor::Black);

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
	FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
	FadeOutActor->Init(FadeColor::Black);
}

void TitleLevel::GamePadUpdate(float _Delta)
{
	if (true == GamePadImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		GamePadImage->Death();
		GamePadImage = nullptr;
		ChangeState(TITLE_STATE::ACIDNERVE);
	}
}

void TitleLevel::AcidnerveUpdate(float _Delta)
{
	if (true == AcidnerveImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		AcidnerveImage->Death();
		AcidnerveImage = nullptr;
		ChangeState(TITLE_STATE::DEVOLVER);
	}
}

void TitleLevel::DevolverUpdate(float _Delta)
{
	if (true == DevolverImage->FadeIsEnd() ||
		true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		DevolverImage->Death();
		DevolverImage = nullptr;
		ChangeState(TITLE_STATE::MAIN_TITLE);
	}
}

void TitleLevel::MainTitleUpdate(float _Delta)
{
	if (false == FadeInActor->FadeIsEnd())
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

void TitleLevel::SetSelectAction()
{
	switch (CurSelectMenu)
	{
	case SELECT_MENU::START:
		StartText->SelectOn();
		OptionText->SelectOff();
		ExitText->SelectOff();
		break;
	case SELECT_MENU::OPTION:
		StartText->SelectOff();
		OptionText->SelectOn();
		ExitText->SelectOff();
		break;
	case SELECT_MENU::EXIT:
		StartText->SelectOff();
		OptionText->SelectOff();
		ExitText->SelectOn();
		break;
	default:
		break;
	}
}

void TitleLevel::GameStartUpdate(float _Delta)
{
	if (true == FadeOutActor->FadeIsEnd())
	{
		GameEngineCore::ChangeLevel("01.Floor1");
	}
}