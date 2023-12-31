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

	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::TileMap), "TileMap");
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

	ScreenOverlayActor = CreateActor<ScreenOverlay>(UPDATE_ORDER::UI);
	ScreenOverlayActor->SetColor({ 0.0f, 0.2f, 0.0f });
	ScreenOverlayActor->SetAlpha(0.1f);

}

void SludgeHeartRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	BossStateUpdate();

	if (false == StartProcessingIsEnd)
	{
		StartProcessing();
	}
}

void SludgeHeartRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	SetBackgroundVolume(1.0f);
	PlayLevelBase::LevelStart(_PrevLevel);
	StartProcessingIsEnd = false;
	if (false == BossIsDeath)
	{
		SpawnBoss();
	}

	AmbiencePlay("Sewer.ogg", 10000);
}

void SludgeHeartRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	SetBackgroundVolume(0.5f);
	PlayLevelBase::LevelEnd(_NextLevel);
	BossFirstHitPrecessingIsEnd = false;
	// 액터 레벨이동 구현 
	if (false == BossIsDeath)
	{
		ReleaseBoss();
	}
}

void SludgeHeartRoom::SpawnBoss()
{
	SludgeActor = CreateActor<Sludge>(UPDATE_ORDER::Boss);
	SludgeActor->SetEnymePlayer(PlayerActor.get());
	SludgeActor->SetEnymeArrow(ArrowActor.get());
	SludgeActor->TileMapSetting(TileMapActor.get());
	SludgeActor->Transform.SetLocalPosition({ 1008.0f, -500.0f });

	HeartActor = CreateActor<Heart>(UPDATE_ORDER::Boss);
	HeartActor->SetEnymePlayer(PlayerActor.get());
	HeartActor->SetEnymeArrow(ArrowActor.get());
	HeartActor->TileMapSetting(TileMapActor.get());
	HeartActor->Transform.SetLocalPosition({ 1008.0f, -500.0f });

	PutTheHeartInSludge();
	SludgeActor = nullptr;
}

void SludgeHeartRoom::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1856.0f });
	PlayerActor->ChangeStateFromLevel(PLAYER_STATE::EnterLevel);
	return;
}

void SludgeHeartRoom::SpawnTriggerBox()
{
	if (nullptr == EnterTheFloor1)
	{
		EnterTheFloor1 = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterTheFloor1");
		EnterTheFloor1->Transform.SetLocalPosition({ 1008.0f, -1856.0f });
		EnterTheFloor1->SetPlaceScale({ 90.0f, 60.0f });
		EnterTheFloor1->SetEnterTriggerFunc(std::bind(&SludgeHeartRoom::ExitRoomTriggerFunc, this));
		EnterTheFloor1->SetStayTriggerFunc(std::bind(&SludgeHeartRoom::Floor1TriggerFunc, this));
	}
}

void SludgeHeartRoom::ReleaseSludges()
{
	std::vector<std::shared_ptr<Sludge>> ObjectType = GetObjectGroupConvert<Sludge>(UPDATE_ORDER::Boss);

	for (size_t i = 0; i < ObjectType.size(); ++i)
	{
		if (nullptr != ObjectType[i])
		{
			ObjectType[i]->Death();
			ObjectType[i] = nullptr;
		}
	}
	ObjectType.clear();
}

void SludgeHeartRoom::PutTheHeartInSludge()
{
	HeartActor->SetOwnerSludge(SludgeActor.get());
	SludgeActor->SetHeart(HeartActor.get());
}

void SludgeHeartRoom::ReleaseBoss()
{
	if (nullptr != HeartActor)
	{
		HeartActor->Death();
		HeartActor = nullptr;
	}
	ReleaseSludges();
}

void SludgeHeartRoom::BossStateUpdate()
{
	// The Process When Boss is alive
	if (false == BossIsDeath)
	{
		if (JUMPBOSS_STATE::Hit == HeartActor->GetCurState())
		{
			BossIsDeath = true;
			SludgeIsDeath = true;
			BackgroundStop();
		}

		if (true == BossIsDeath &&
			false == BossDeathPrecessingIsEnd)
		{
			BossDeathProcessing();
		}

		if (nullptr != HeartActor &&
			false == BossFirstHitPrecessingIsEnd &&
			true == HeartActor->IsFirstHit())
		{
			BossFirstHitPrecessingIsEnd = true;
			BackgroundPlay("AcidNerve.ogg", 10000);
			OutputBossName();
		}
	}
}

void SludgeHeartRoom::BossDeathProcessing()
{
	BossDeathPrecessingIsEnd = true;

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::White, 6.0f);
		FadeInActor->SetFadeStartAlpha(0.4f);
	}

	ReleaseSludges();
}

void SludgeHeartRoom::Floor1TriggerFunc()
{
	PlayerActor->ChangeState(PLAYER_STATE::ExitLevel);

	if (nullptr == FadeOutActor)
	{
		FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
		FadeOutActor->Init(FadeColor::Black, 1.5f);
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
	SludgeActor->TileMapSetting(TileMapActor.get());

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

	BossNameScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossNameScript->Init("SLUDGE HEART", FONT_TYPE::ANCIENT, { 32.0f, 32.0f }, 2.0f);
	BossNameScript->FadeInit();
	BossNameScript->Transform.SetLocalPosition({ 5.0f, -290.0f });
	
	BossDescriptionScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossDescriptionScript->Init("HEART OF THE GUARDIAN", FONT_TYPE::ANCIENT, { 16.0f, 16.0f });
	BossDescriptionScript->FadeInit();
	BossDescriptionScript->Transform.SetLocalPosition({ 0.0f, -325.0f });
}

void SludgeHeartRoom::ReleaseTriggerBox()
{
	if (nullptr != EnterTheFloor1)
	{
		EnterTheFloor1->Death();
		EnterTheFloor1 = nullptr;
	}
}


void SludgeHeartRoom::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	GlobalLoad::LoadSound("AcidNerve.ogg", "Resource\\Sound\\BGM\\");
	GlobalLoad::LoadSound("Sewer.ogg", "Resource\\Sound\\Ambience\\");


}

void SludgeHeartRoom::StartProcessing()
{
	if (nullptr != FadeInActor &&
		true == FadeInActor->FadeIsEnd())
	{
		StartProcessingIsEnd = true;
		FadeInActor->Death();
		FadeInActor = nullptr;
		SpawnTriggerBox();
	}
}
