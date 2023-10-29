#include "PreCompile.h"
#include "Floor1.h"

Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::Map), "TileMap");
	TileMapActor->BaseSetting(101, 219, "Floor1", "Overworld.png");

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::WALL, "WALL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::TCOL, "TCOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::ACOL, "ACOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);

	// TileMap Setting
	PlayerActor->TileMapSetting(TileMapActor);
	ArrowActor->TileMapSetting(TileMapActor);

	EnterPlaceToSludgeRoom = CreateActor<EventPlace>(static_cast<int>(UPDATE_ORDER::EnterPlace), "EnterPlaceToSludgeRoom");
	EnterPlaceToSludgeRoom->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
	EnterPlaceToSludgeRoom->SetPlaceScale({ 90.0f, 60.0f });

	FadeActor = CreateActor<Fade>(RENDERING_ORDER::AlphaLess);
	FadeActor->SetFadeMode(FadeMode::FadeOut);
	FadeActor->SetFadeSpeed(0.5f);
	FadeActor->SetBlackColor();
	FadeActor->SetMaxFade(0.3f);
}

void Floor1::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	if (true == EnterPlaceToSludgeRoom->EnterCheck())
	{
		PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);
	}

	if (true == PlayerActor->EnterEnd())
	{
		PlayerActor->EnterEndReset();
		GameEngineCore::ChangeLevel("02.SludgeHeartRoom");
	}
}


void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
}

void Floor1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}

void Floor1::SpawnPlayer()
{
	//PlayerActor->Transform.SetLocalPosition({ 1616.0f, -6560.0f });
	PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3270.0f });
	
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}