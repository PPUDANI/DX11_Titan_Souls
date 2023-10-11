#include "PreCompile.h"
#include "KnightElhananRoom.h"

KnightElhananRoom::KnightElhananRoom()
{
}

KnightElhananRoom::~KnightElhananRoom()
{
}

void KnightElhananRoom::Start()
{
	PlayLevelBase::Start();
	PlayerSpawnPos = { 944.0f, -1760.0f };
	PlayerSpawnPos += DepthValue::TempValue;

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);
	TileMapActor->BaseSetting(59, 60, "KnightElhanan", "Underworld.png");

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::TCOL, "COL2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::ACOL, "ACOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);

	PlayerActor->TileMapSetting(TileMapActor);
	ArrowActor->TileMapSetting(TileMapActor);
}

void KnightElhananRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void KnightElhananRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
}

void KnightElhananRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
}
