#include "PreCompile.h"
#include "YetiRoom.h"

#include "Yeti.h"
#include "Snowball.h"

YetiRoom::YetiRoom()
{
}

YetiRoom::~YetiRoom()
{
}

void YetiRoom::Start()
{
	PlayLevelBase::Start();

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(2, "YetiRoomRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

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

	EnterTheFloor1 = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterTheFloor1");
	EnterTheFloor1->Transform.SetLocalPosition({ 1008.0f, -1792.0f });
	EnterTheFloor1->SetPlaceScale({ 90.0f, 60.0f });
	EnterTheFloor1->SetTriggerFunction(std::bind(&YetiRoom::Floor1TriggerFunc, this));

	ScreenOverlayActor = CreateActor<ScreenOverlay>(UPDATE_ORDER::UI);
	ScreenOverlayActor->SetColor({ 1.0f, 1.0f, 1.0f });
	ScreenOverlayActor->SetAlpha(0.1f);
}


void YetiRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	if (false == WakeUpProcessingIsEnd &&
		nullptr != YetiActor &&
		true == YetiActor->YetiIsWakeUp())
	{
		BossWakeUpProcessing();
		WakeUpProcessingIsEnd = true;
	}

	if (YETI_STATE::Hit == YetiActor->GetCurState())
	{
		BossIsDeath = true;
	}

	if (true == BossIsDeath &&
		false == BossDeathPrecessingIsEnd)
	{
		BossDeathProcessing();
	}

	if (nullptr != FadeInActor &&
		true == FadeInActor->FadeIsEnd())
	{
		FadeInActor->Death();
		FadeInActor = nullptr;
	}
}


void YetiRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::Black);
	}
	SpawnBoss();
}


void YetiRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
	CameraManager::CalCameraPosFromArrowOn();
	ReleaseBossEliment();
}


void YetiRoom::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1792.0f });
	PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);
	return;
}

void YetiRoom::SpawnBoss()
{
	if (nullptr == YetiActor)
	{
		YetiActor = CreateActor<Yeti>(UPDATE_ORDER::Boss);
		YetiActor->Transform.SetLocalPosition({ 1008.0f, -1492.0f });
		YetiActor->SetEnymePlayer(PlayerActor.get());
		YetiActor->SetEnymeArrow(ArrowActor.get());
		YetiActor->TileMapSetting(TileMapActor.get());
	}
}

void YetiRoom::SpawnSnowBall(const float4& _StartPos, const float4& _Angle, RENDERING_ORDER _Order)
{
	SnowballActor = CreateActor<Snowball>(UPDATE_ORDER::Boss);
	SnowballActor->Init(_StartPos, _Angle, _Order);
	SnowballActor->TileMapSetting(TileMapActor.get());
	SnowballActor = nullptr;
}

void YetiRoom::Floor1TriggerFunc()
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

void YetiRoom::BossDeathProcessing()
{
	BossDeathPrecessingIsEnd = true;

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::White, 6.0f);
		FadeInActor->SetFadeStartAlpha(0.4f);
	}
}

void YetiRoom::BossWakeUpProcessing()
{
	CameraManager::CalCameraPosFromArrowOff();
	OutputBossName();
}

void YetiRoom::ReleaseBossEliment()
{
	if (nullptr != YetiActor)
	{
		YetiActor->Death();
		YetiActor = nullptr;
	}
}

void YetiRoom::OutputBossName()
{
	// BossName Actor
	BossNameBack = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	BossNameBack->Init("BossNameBG.png");
	BossNameBack->Transform.SetLocalPosition({ 0.0f, -305.0f });

	SludgeHeartScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	SludgeHeartScript->Init("YETI", FONT_TYPE::ANCIENT, { 32.0f, 32.0f }, 2.0f);
	SludgeHeartScript->FadeInit();
	SludgeHeartScript->Transform.SetLocalPosition({ 5.0f, -290.0f });

	GuardianScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	GuardianScript->Init("OLD SNOW BEAST", FONT_TYPE::ANCIENT, { 16.0f, 16.0f });
	GuardianScript->FadeInit();
	GuardianScript->Transform.SetLocalPosition({ 0.0f, -325.0f });
}

void YetiRoom::ReleaseBossName()
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