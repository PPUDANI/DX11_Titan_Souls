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
	FadeInActor->Init(FadeColor::Black, 1.0f);

	TileMapActor->On();
}


void TitleLevel::GamePadUpdate(float _Delta)
{
	if (true == GamePadImage->FadeIsEnd())
	{
		GamePadImage->Death();
		GamePadImage = nullptr;
		ChangeState(TITLE_STATE::ACIDNERVE);
	}
}

void TitleLevel::AcidnerveUpdate(float _Delta)
{
	if (true == AcidnerveImage->FadeIsEnd())
	{
		AcidnerveImage->Death();
		AcidnerveImage = nullptr;
		ChangeState(TITLE_STATE::DEVOLVER);
	}
}

void TitleLevel::DevolverUpdate(float _Delta)
{
	if (true == DevolverImage->FadeIsEnd())
	{
		DevolverImage->Death();
		DevolverImage = nullptr;
		ChangeState(TITLE_STATE::MAIN_TITLE);
	}
}

void TitleLevel::MainTitleUpdate(float _Delta)
{

}
