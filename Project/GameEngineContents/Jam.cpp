#include "PreCompile.h"
#include "Jam.h"

Jam::Jam()
{
}

Jam::~Jam()
{
}

void Jam::Start()
{
	PlayLevelBase::Start();
	PlayerSpawnPos = { 2768.0f, -2688.0f };

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);

	TileMapActor->BaseSetting(185, 160, "Jam", "Jam.png");
	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BG2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BG3.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::WALL, "WALL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::TCOL, "COL2.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
}

void Jam::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void Jam::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
}

void Jam::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}
