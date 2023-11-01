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

	EnterTheFloor1 = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterTheFloor1");
	EnterTheFloor1->Transform.SetLocalPosition({ 1008.0f, -1856.0f });
	EnterTheFloor1->SetPlaceScale({ 90.0f, 60.0f });
	EnterTheFloor1->Off();


	FadeInActor = CreateActor<Fade>(RENDERING_ORDER::UI);
	FadeInActor->SetFadeMode(FadeMode::FadeIn);
	FadeInActor->SetFadeSpeed(0.75f);
	FadeInActor->SetTargetValue(0.1f);
	FadeInActor->SetBlackColor();
	FadeInActor->Off();

	FadeOutActor = CreateActor<Fade>(RENDERING_ORDER::UI);
	FadeOutActor->SetFadeMode(FadeMode::FadeOut);
	FadeOutActor->SetFadeSpeed(0.75f);
	FadeOutActor->SetDefaultValue(0.1f);
	FadeInActor->SetBlackColor();
	FadeOutActor->Off();
}

void SludgeHeartRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	if (PLAYER_STATE::ExitLevel == PlayerActor->GetCurState() ||
		PLAYER_STATE::EnterLevel == PlayerActor->GetCurState())
	{
		EnterTheFloor1->Off();
	}
	else
	{
		EnterTheFloor1->On();
	}

	if (JUMPBOSS_STATE::Death == HeartActor->GetCurState())
	{
		BossIsDeath = true;
	}

	if (true == BossIsDeath)
	{
		ReleaseSludges();
	}


	if (true == EnterTheFloor1->EnterCheck())
	{
		EnterTheFloor1Update();
	}
}

void SludgeHeartRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	FadeOutActor->FadeResetByMode();
	FadeOutActor->Off();

	FadeInActor->FadeResetByMode();
	FadeInActor->On();
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
		SludgeActor->Transform.SetLocalPosition({ 1008.0f, -500.0f });

		HeartActor = CreateActor<Heart>(UPDATE_ORDER::Boss);
		HeartActor->SetEnymePlayer(PlayerActor.get());
		HeartActor->SetEnymeArrow(ArrowActor.get());
		HeartActor->SetCurMap(TileMapActor.get());

		HeartActor->SetOwnerSludge(SludgeActor.get());

		SludgeActor->SetHeart(HeartActor.get());
		SludgeActor = nullptr;
	}
}

void SludgeHeartRoom::SpawnPlayer(GameEngineLevel* _PrevLevel)
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

void SludgeHeartRoom::EnterTheFloor1Update()
{
	PlayerActor->ChangeState(PLAYER_STATE::ExitLevel);
	EnterTheFloor1->Off();
	FadeOutActor->On();

	if (true == FadeOutActor->FadeIsEnd())
	{
		PlayerActor->ChangeState(PLAYER_STATE::Idle);
		EnterTheFloor1->EnterCheckReset();
		GameEngineCore::ChangeLevel("01.Floor1");
	}
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
