#include "PreCompile.h"
#include "SludgeHeartRoom.h"

#include "Sludge.h"
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

	if (nullptr == SludgeActor)
	{
		SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);
		SludgeActor->Transform.SetLocalPosition({ 1008.0f, -900.0f });
		SludgeActor->SetEnymePlayer(PlayerActor.get());
		SludgeActor->SetEnymeArrow(ArrowActor.get());

		if (nullptr == HeartActor)
		{
			HeartActor = CreateActor<Heart>(UPDATE_ORDER::Boss);
			HeartActor->Transform.SetLocalPosition({ 1008.0f, -800.0f });
			HeartActor->SetEnymePlayer(PlayerActor.get());
			HeartActor->SetEnymeArrow(ArrowActor.get());
			HeartActor->SetOwnerSludge(SludgeActor.get());
		}

		SludgeActor->SetHeart(HeartActor.get());
	}
}

void SludgeHeartRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}

void SludgeHeartRoom::SpawnPlayer()
{
	// 1856.0f
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1056.0f });
	ArrowActor->Transform.SetLocalPosition({ 1008.0f, -1056.0f });
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}