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
	ScreenOverlayActor = CreateActor<ScreenOverlay>(UPDATE_ORDER::UI);
	ScreenOverlayActor->SetAlpha(0.3f);

	// ImageActor
	GlobalLoad::LoadSpriteSingle("GamePad.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSpriteSingle("Acidnerve.png", "Resource\\Texture\\Title");
	GlobalLoad::LoadSpriteSingle("Devolver.png", "Resource\\Texture\\Title");

	GamePadImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	GamePadImage->Init("GamePad.png", 1.0f, 1.0f);
	GamePadImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	GamePadImage->Off();

	AcidnerveImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	AcidnerveImage->Init("Acidnerve.png", 1.0f, 1.0f);
	AcidnerveImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	AcidnerveImage->Off();

	DevolverImage = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	DevolverImage->Init("Devolver.png", 1.0f, 1.0f);
	DevolverImage->Transform.SetLocalPosition({ 568.0f, -568.0f });
	DevolverImage->Off();

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
	case TITLE_STATE::START:
	default:
		break;
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
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
	case TITLE_STATE::START:
	default:
		break;
	}
}
