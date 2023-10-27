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

	GetMainCamera()->SetZSort(RENDERING_ORDER::Shadow);

	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::Map), "TileMap");
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

	if (JUMPBOSS_STATE::Death == HeartActor->GetCurState())
	{
		BossIsDeath = true;
	}

	if (true == BossIsDeath)
	{
		ReleaseSludges();
	}
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

	ReleaseSludges();
}

void SludgeHeartRoom::SpawnBoss()
{
	if (false == BossIsDeath)
	{
		SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);
		SludgeActor->SetEnymePlayer(PlayerActor.get());
		SludgeActor->SetEnymeArrow(ArrowActor.get());
		SludgeActor->SetCurMap(TileMapActor.get());
		SludgeActor->Transform.SetLocalPosition({ 1008.0f, -900.0f });

		HeartActor = CreateActor<Heart>(UPDATE_ORDER::Boss);
		HeartActor->SetEnymePlayer(PlayerActor.get());
		HeartActor->SetEnymeArrow(ArrowActor.get());
		HeartActor->SetCurMap(TileMapActor.get());

		HeartActor->SetOwnerSludge(SludgeActor.get());

		SludgeActor->SetHeart(HeartActor.get());
		SludgeActor = nullptr;
	}
}

void SludgeHeartRoom::SpawnPlayer()
{
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1856.0f });
	PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);
	return;
}

void SludgeHeartRoom::ReleaseSludges()
{
	std::vector<std::shared_ptr<Sludge>> ObjectType = GetObjectGroupConvert<Sludge>(UPDATE_ORDER::Boss);

	for (size_t i = 0; i < ObjectType.size(); ++i)
	{
		ObjectType[i]->Death();
		ObjectType[i] = nullptr;
	}
	ObjectType.clear();
}

void SludgeHeartRoom::SpawnDividedSludge(int _DividedCount, float4 _SpawnPos)
{
	SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);

	SludgeActor->SetEnymePlayer(PlayerActor.get());
	SludgeActor->SetEnymeArrow(ArrowActor.get());
	SludgeActor->SetCurMap(TileMapActor.get());

	SludgeActor->DividedSludgeInit(_DividedCount);
	SludgeActor->Transform.SetLocalPosition(_SpawnPos);
	SludgeActor->ChangeState(JUMPBOSS_STATE::Division);

	SludgeActor = nullptr;
}
