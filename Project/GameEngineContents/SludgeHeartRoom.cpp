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

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(1, "SludgeHeartRoomRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

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
	EnterTheFloor1->SetTriggerFunction(std::bind(&SludgeHeartRoom::Floor1TriggerFunc, this));

	ScreenOverlayActor = CreateActor<ScreenOverlay>(UPDATE_ORDER::UI);
	ScreenOverlayActor->SetColor({ 0.0f, 0.2f, 0.0f });
	ScreenOverlayActor->SetAlpha(0.15f);
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

	if (nullptr != HeartActor &&
		true == HeartActor->IsFirstHit())
	{
		HeartActor->SetFirstHit(false);
		OutputBossName();
	}
}

void SludgeHeartRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::Black);
	}

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
	ReleaseBossName();
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
		HeartActor->Transform.SetLocalPosition({ 1008.0f, -500.0f });

		PutTheHeartInSludge();
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

void SludgeHeartRoom::PutTheHeartInSludge()
{
	HeartActor->SetOwnerSludge(SludgeActor.get());
	SludgeActor->SetHeart(HeartActor.get());
}


void SludgeHeartRoom::Floor1TriggerFunc()
{
	PlayerActor->ChangeState(PLAYER_STATE::ExitLevel);

	if (nullptr == FadeOutActor)
	{
		FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
		FadeOutActor->Init(FadeColor::Black);
	}

	if (true == FadeOutActor->FadeIsEnd())
	{
		PlayerActor->ChangeState(PLAYER_STATE::Idle);
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

void SludgeHeartRoom::OutputBossName()
{
	// BossName Actor
	BossNameBack = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	BossNameBack->Init("BossNameBG.png");
	BossNameBack->Transform.SetLocalPosition({ 0.0f, -305.0f });

	SludgeHeartScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	SludgeHeartScript->Init("SLUDGEHEART", FONT_TYPE::ANCIENT, { 32.0f, 32.0f }, 2.0f);
	SludgeHeartScript->FadeInit();
	SludgeHeartScript->Transform.SetLocalPosition({ 5.0f, -290.0f });
	
	GuardianScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	GuardianScript->Init("HEART OF THE GUARDIAN", FONT_TYPE::ANCIENT, { 16.0f, 16.0f });
	GuardianScript->FadeInit();
	GuardianScript->Transform.SetLocalPosition({ 0.0f, -325.0f });
}

void SludgeHeartRoom::ReleaseBossName()
{
	if (nullptr != BossNameBack)
	{
		BossNameBack->Death();
		BossNameBack = nullptr;
	}

	if (nullptr != SludgeHeartScript)
	{
		SludgeHeartScript->Death();
		SludgeHeartScript = nullptr;
	}

	if (nullptr != GuardianScript)
	{
		GuardianScript->Death();
		GuardianScript = nullptr;
	}
}
