#include "PreCompile.h"
#include "TitleLevel.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GetMainCamera()->SetYSort(RENDERING_ORDER::UI_FRONT);

	// TileMap
	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::TileMap), "TileMap");
	TileMapActor->BaseSetting(71, 71, "Title", "Overworld2.png", {16.0f, 16.0f });

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::WALL, "WALL.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
	TileMapActor->Off();

	// ScreenOverlayActor
	ScreenOverlayActor = CreateActor<OverlayActor>(UPDATE_ORDER::UI);
	ScreenOverlayActor->SetAlpha(0.4f);
	ScreenOverlayActor->SetScale(GlobalValue::WindowScale);
	ScreenOverlayActor->Transform.SetLocalPosition({ 568.0f, -568.0f - GlobalValue::WindowScale.hY()});
	ScreenOverlayActor->SetOrder(RENDERING_ORDER::UI);

	// ImageActor
	GlobalLoad::LoadSpriteSingle("GamePad.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSpriteSingle("Acidnerve.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSpriteSingle("Devolver.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSpriteSingle("TitleLogo.png", "Resource\\Texture\\Title");

	GamePadImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	GamePadImage->Init("GamePad.png", 1.0f, 1.5f);
	GamePadImage->Off();

	AcidnerveImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	AcidnerveImage->Init("Acidnerve.png", 1.0f, 1.5f);
	AcidnerveImage->Off();

	DevolverImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	DevolverImage->Init("Devolver.png", 1.0f, 1.5f);
	DevolverImage->Off();

	TitleLogo = CreateActor<ImageActor>(UPDATE_ORDER::UI);
	TitleLogo->SetImage("TitleLogo.png", { 546.0f, 254.0f});
	TitleLogo->Transform.SetLocalPosition({ 0.0f, 150.0f });
	TitleLogo->Off();

	StartText = CreateActor<SelectText>();
	StartText->Init("START", SelectedColor, UnSelectedColor, 32.0f);
	StartText->Transform.SetLocalPosition({ 568.0f, -560.0f });
	StartText->Off();

	OptionText = CreateActor<SelectText>();
	OptionText->Init("OPTION", SelectedColor, UnSelectedColor, 32.0f);
	OptionText->Transform.SetLocalPosition({ 568.0f, -592.0f });
	OptionText->Off();

	ExitText = CreateActor<SelectText>();
	ExitText->Init("EXIT", SelectedColor, UnSelectedColor, 32.0f);
	ExitText->Transform.SetLocalPosition({ 568.0f, -624.0f });
	ExitText->Off();

	// BGM, AMBIENCE
	GlobalLoad::LoadSound("Forest.ogg", "Resource\\Sound\\Ambience\\");
	GlobalLoad::LoadSound("Opening.ogg", "Resource\\Sound\\Title\\");
	GlobalLoad::LoadSound("Motif.ogg", "Resource\\Sound\\Title\\");

	// Button
	GlobalLoad::LoadSound("Select.ogg", "Resource\\Sound\\Title\\");
	GlobalLoad::LoadSound("StartGame.ogg", "Resource\\Sound\\Title\\");


	GetMainCamera()->Transform.SetLocalPosition({ 568.0f, -568.0f });

	GameEngineInput::AddInputObject(this);
}

void TitleLevel::Update(float _Delta)
{
	LevelBase::Update(_Delta);
	switch (CurState)
	{
	case TITLE_STATE::GAMEPAD:
		GamePadUpdate(_Delta);
		break;
	case TITLE_STATE::ACIDNERVE:
		AcidnerveUpdate(_Delta);
		break;
	case TITLE_STATE::DEVOLVER:
		DevolverUpdate(_Delta);
		break;
	case TITLE_STATE::MAIN_TITLE:
		MainTitleUpdate(_Delta);
		break;
	case TITLE_STATE::GAME_START:
		GameStartUpdate(_Delta);
		break;
	default:
		break;
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelBase::LevelStart(_PrevLevel);
	ChangeState(TITLE_STATE::GAMEPAD);
	BackgroundPlay("Opening.ogg");
	AmbiencePlay("Forest.ogg", 10000);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	LevelBase::LevelEnd(_NextLevel);
	if (nullptr != FadeOutActor)
	{
		FadeOutActor->Death();
		FadeOutActor = nullptr;
	}

	if (nullptr != FadeInActor)
	{
		FadeInActor->Death();
		FadeInActor = nullptr;
	}
}

void TitleLevel::ChangeState(TITLE_STATE _State)
{
	CurState = _State;
	switch (CurState)
	{
	case TITLE_STATE::GAMEPAD:
		GamePadStart();
		break;
	case TITLE_STATE::ACIDNERVE:
		AcidnerveStart();
		break;
	case TITLE_STATE::DEVOLVER:
		DevolverStart();
		break;
	case TITLE_STATE::MAIN_TITLE:
		MainTitleStart();
		break;
	case TITLE_STATE::GAME_START:
		GameStartStart();
		break;
	default:
		break;
	}
}


void TitleLevel::MainTitleActorOff()
{
	if (nullptr != TitleLogo)
	{
		TitleLogo->Off();
	}	
	if (nullptr != TileMapActor)
	{
		TileMapActor->Off();
	}
	if (nullptr != StartText)
	{
		StartText->Off();
	}
	if (nullptr != OptionText)
	{
		OptionText->Off();
	}
	if (nullptr != ExitText)
	{
		ExitText->Off();
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

	EffectPlay("Select.ogg");
}