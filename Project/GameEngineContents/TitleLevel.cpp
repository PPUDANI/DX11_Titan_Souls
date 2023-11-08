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
	GetMainCamera()->SetYSort(RENDERING_ORDER::UIFront);

	// TileMap
	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::Map), "TileMap");
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
	GamePadImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	GamePadImage->Off();

	AcidnerveImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	AcidnerveImage->Init("Acidnerve.png", 1.0f, 1.5f);
	AcidnerveImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	AcidnerveImage->Off();

	DevolverImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	DevolverImage->Init("Devolver.png", 1.0f, 1.5f);
	DevolverImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	DevolverImage->Off();

	TitleLogo = CreateActor<ImageActor>(UPDATE_ORDER::UI);
	TitleLogo->SetImage("TitleLogo.png", { 546.0f, 254.0f});
	TitleLogo->Transform.SetLocalPosition({ 568.0f, -400.0f });
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


	GetMainCamera()->Transform.SetLocalPosition({ 568.0f, -568.0f });

	GameEngineInput::AddInputObject(this);

	ChangeState(TITLE_STATE::GAMEPAD);
}

void TitleLevel::Update(float _Delta)
{
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
	case TITLE_STATE::OPTION_SCREEN:

		break;
	case TITLE_STATE::EXIT_SCREEN:

		break;
	default:
		break;
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	GameEngineSprite::Release("GamePad.png");
	GameEngineSprite::Release("Acidnerve.png");
	GameEngineSprite::Release("Devolver.png");
	GameEngineSprite::Release("TitleLogo.png");

	GameEngineTexture::Release("GamePad.png");
	GameEngineTexture::Release("Acidnerve.png");
	GameEngineTexture::Release("Devolver.png");
	GameEngineTexture::Release("TitleLogo.png");

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
