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
}

void SludgeHeartRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
	if (JUMPBOSS_STATE::Death != HeartActor->GetCurState())
	{
		HeartActor->Death();
		HeartActor = nullptr;
	}
	else
	{
		BossIsDeath = true;
	}

	std::list<std::shared_ptr<Sludge>>::iterator Start = Sludges.begin();
	std::list<std::shared_ptr<Sludge>>::iterator End = Sludges.end();
	for (; Start != End;)
	{
		if (nullptr != *Start)
		{
			(*Start)->Death();
			(*Start) = nullptr;
		}
		++Start;
	}
}

void SludgeHeartRoom::SpawnBoss()
{
	if (false == BossIsDeath)
	{
		SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);
		SludgeActor->SetEnymePlayer(PlayerActor.get());
		SludgeActor->SetEnymeArrow(ArrowActor.get());
		SludgeActor->Transform.SetLocalPosition({ 1008.0f, -900.0f });

		HeartActor = CreateActor<Heart>(UPDATE_ORDER::Boss);
		HeartActor->Transform.SetLocalPosition({ 1008.0f, -800.0f });
		HeartActor->SetEnymePlayer(PlayerActor.get());
		HeartActor->SetEnymeArrow(ArrowActor.get());

		HeartActor->SetOwnerSludge(SludgeActor.get());

		SludgeActor->SetHeart(HeartActor.get());

		Sludges.push_back(SludgeActor);
		SludgeActor = nullptr;
	}
}

void SludgeHeartRoom::SpawnPlayer()
{
	// 1856.0f
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1056.0f });
	ArrowActor->Transform.SetLocalPosition({ 1008.0f, -1056.0f });
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}

void SludgeHeartRoom::SpawnDividedSludge(float _DividedCount, float4 _SpawnPos)
{
	SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);
	SludgeActor->SetEnymePlayer(PlayerActor.get());
	SludgeActor->SetEnymeArrow(ArrowActor.get());

	SludgeActor->DividedSludgeInit(_DividedCount);

	SludgeActor->Transform.SetLocalPosition(_SpawnPos);

	Sludges.push_back(SludgeActor);
	SludgeActor = nullptr;
}
