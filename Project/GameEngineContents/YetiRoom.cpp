#include "PreCompile.h"
#include "YetiRoom.h"

YetiRoom::YetiRoom()
{
}

YetiRoom::~YetiRoom()
{
}

void YetiRoom::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::Map), "TileMap");
	TileMapActor->BaseSetting(60, 60, "Yeti", "Underworld.png");

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::TCOL, "COL2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::ACOL, "ACOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);

	PlayerActor->TileMapSetting(TileMapActor);
	ArrowActor->TileMapSetting(TileMapActor);
}

void YetiRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void YetiRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

}

void YetiRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
}

void YetiRoom::SpawnPlayer()
{
	//PlayerSpawnPos = { 1008.0f, -1824.0f };
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1700.0f });
	ArrowActor->Transform.SetLocalPosition({ 1008.0f, -1700.0f });
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}