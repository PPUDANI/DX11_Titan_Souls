#include "PreCompile.h"
#include "YetiRoom.h"

#include "Yeti.h"
#include "Snowball.h"
#include "Icicle.h"

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

	//ScreenOverlayActor = CreateActor<ScreenOverlay>(UPDATE_ORDER::UI);
	//ScreenOverlayActor->SetColor({ 0.8f, 0.8f, 0.8f });
	//ScreenOverlayActor->SetAlpha(0.1f);

}

void YetiRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	if (false == BossIsDeath)
	{
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
			YetiIsDeath = true;
			BackgroundStop();
			ReleaseIcicle();
			ReleaseSnowball();
		}

		if (true == BossIsDeath &&
			false == BossDeathPrecessingIsEnd)
		{
			BossDeathProcessing();
		}
	}

	if (false == StartProcessingIsEnd)
	{
		StartProcessing();
	}
}


void YetiRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

	StartProcessingIsEnd = false;
	WakeUpProcessingIsEnd = false;

	if (false == BossIsDeath)
	{
		SpawnBoss();
	}

	AmbiencePlay("Dungeon.ogg");
}


void YetiRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	CameraManager::CalCameraPosFromArrowOn();
	CameraManager::AddCameraPosFromBoss = float4::ZERO;

	if (false == BossIsDeath)
	{
		ReleaseBoss();
	}

	ReleaseSnowball();
	ReleaseIcicle();
	ReleaseBossName();
}


void YetiRoom::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1792.0f });
	PlayerActor->ChangeStateFromLevel(PLAYER_STATE::EnterLevel);
	return;
}

void YetiRoom::SpawnBoss()
{
	if (nullptr == YetiActor)
	{
		YetiActor = CreateActor<Yeti>(UPDATE_ORDER::Boss);
		YetiActor->Transform.SetLocalPosition({ 1008.0f, -1092.0f });
		YetiActor->SetEnymePlayer(PlayerActor.get());
		YetiActor->SetEnymeArrow(ArrowActor.get());
		YetiActor->TileMapSetting(TileMapActor.get());
	}
}

void YetiRoom::SpawnTriggerBox()
{
	EnterTheFloor1 = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterTheFloor1");
	EnterTheFloor1->Transform.SetLocalPosition({ 1008.0f, -1808.0f });
	EnterTheFloor1->SetPlaceScale({ 90.0f, 90.0f });
	EnterTheFloor1->SetEnterTriggerFunc(std::bind(&YetiRoom::ExitRoomTriggerFunc, this));
	EnterTheFloor1->SetStayTriggerFunc(std::bind(&YetiRoom::Floor1TriggerFunc, this));
}

void YetiRoom::SpawnSnowBall(const float4& _StartPos, const float4& _Angle, RENDERING_ORDER _Order)
{
	SnowballActor = CreateActor<Snowball>(UPDATE_ORDER::Boss);
	SnowballActor->Init(_StartPos, _Angle, _Order);
	SnowballActor->TileMapSetting(TileMapActor.get());
	SnowballActor->PlayerSetting(PlayerActor.get());
	SnowballActor = nullptr;
}

void YetiRoom::SpawnIcicle(const float4& _FirstTargetPos, const float4& _Angle)
{
	GameEngineRandom Inst;
	static int Count = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);

	float4 TargetPos = _FirstTargetPos;
	float4 DirBasis = float4::GetUnitVectorFromDeg(_Angle.Z);
	float4 VirticalDirBasis = float4::GetUnitVectorFromDeg(_Angle.Z + 90.0f);

	int Index = Inst.RandomInt(10, 15); // 고드름 개수
	float4 StartHeight = { 0.0f, 1000.0f }; // 시작 높이

	for (int i = 0; i < Index; ++i)
	{
		float IcicleSpacing = Inst.RandomFloat(75.0f, 150.0f); // 고드름 간격 편차
		TargetPos += DirBasis * IcicleSpacing; // 방향에 따른 고드름 간격

		float4 VirticalDeviation = VirticalDirBasis * Inst.RandomFloat(-30.0f, 30.0f); // 나열된 고드름 방향의 수직위치 오차(자연스러움)
		if (true == TileMapActor->AllColCheck(TargetPos + VirticalDeviation))
		{
			break;
		}

		StartHeight.Y += 75.0f; // 가까울수록 순서대로 떨어짐(자연스러움)

		IcicleActor = CreateActor<Icicle>(UPDATE_ORDER::Boss);
		IcicleActor->Init(TargetPos + VirticalDeviation, StartHeight);
		IcicleActor->SetEnymePlayer(PlayerActor.get());
		IcicleActor = nullptr;
	}
}

void YetiRoom::Floor1TriggerFunc()
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
	BackgroundPlay("Yeti.ogg", 10000);
	OutputBossName();
}



void YetiRoom::ReleaseBoss()
{
	if (nullptr != YetiActor)
	{
		YetiActor->Death();
		YetiActor = nullptr;
	}
}

void YetiRoom::ReleaseSnowball()
{
	std::vector<std::shared_ptr<Snowball>> ObjectType = GetObjectGroupConvert<Snowball>(UPDATE_ORDER::Boss);

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

void YetiRoom::ReleaseIcicle()
{
	std::vector<std::shared_ptr<Icicle>> ObjectType = GetObjectGroupConvert<Icicle>(UPDATE_ORDER::Boss);

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

void YetiRoom::OutputBossName()
{
	// BossName Actor
	BossNameBack = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	BossNameBack->Init("BossNameBG.png");
	BossNameBack->Transform.SetLocalPosition({ 0.0f, -305.0f });

	BossNameScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossNameScript->Init("YETI", FONT_TYPE::ANCIENT, { 32.0f, 32.0f }, 2.0f);
	BossNameScript->FadeInit();
	BossNameScript->Transform.SetLocalPosition({ 5.0f, -290.0f });

	BossDescriptionScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossDescriptionScript->Init("OLD SNOW BEAST", FONT_TYPE::ANCIENT, { 16.0f, 16.0f });
	BossDescriptionScript->FadeInit();
	BossDescriptionScript->Transform.SetLocalPosition({ 0.0f, -325.0f });
}

void YetiRoom::ReleaseBossName()
{
	if (nullptr != BossNameBack)
	{
		BossNameBack->Death();
		BossNameBack = nullptr;
	}

	if (nullptr != BossNameScript)
	{
		BossNameScript->Death();
		BossNameScript = nullptr;
	}

	if (nullptr != BossDescriptionScript)
	{
		BossDescriptionScript->Death();
		BossDescriptionScript = nullptr;
	}
}

void YetiRoom::ReleaseTriggerBox()
{
	if (nullptr != EnterTheFloor1)
	{
		EnterTheFloor1->Death();
		EnterTheFloor1 = nullptr;
	}
}

void YetiRoom::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	GlobalLoad::LoadSound("Yeti.ogg", "Resource\\Sound\\BGM\\");
	GlobalLoad::LoadSound("Dungeon.ogg", "Resource\\Sound\\Ambience\\");
}

void YetiRoom::StartProcessing()
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
