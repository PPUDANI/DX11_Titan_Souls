#include "PreCompile.h"
#include "SludgeHeartRoom.h"

#include "Heart.h"
SludgeHeartRoom::SludgeHeartRoom()
{
}

SludgeHeartRoom::~SludgeHeartRoom()
{
}

void SludgeHeartRoom::Start()
{
	PlayLevelBase::Start();
	PlayerSpawnPos = { 1008.0f, -1856.0f };

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);
	TileMapActor->BaseSetting(60, 80, "SludgeHeart", "Underworld.png");

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::ACOL, "ACOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);

	PlayerActor->TileMapSetting(TileMapActor);
	ArrowActor->TileMapSetting(TileMapActor);
}

void SludgeHeartRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void SludgeHeartRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

	HeartActor = CreateActor<Heart>(UPDATE_ORDER::Monster);
	HeartActor->Transform.SetLocalPosition({ 1008.0f, -1600.0f });
}

void SludgeHeartRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}
