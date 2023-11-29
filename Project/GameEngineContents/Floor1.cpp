#include "PreCompile.h"
#include "Floor1.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "Hand.h"
#include "ColossusBody.h"
#include "EndingDoor.h"
#include "ClearLight.h"
#include "ClearLight2.h"
#include "OverlayLightMask.h"
#include "CrystalBall.h"
#include "StartDoor.h"

Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Start()
{
	PlayLevelBase::Start();

	GlobalLoad::LoadSpriteCut(6, 1, "BossDust.png", "Resource\\Texture\\Particle\\");

	OverlayLightEffect = GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OverlayLightMask>();
	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "Floor1RenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}


	TileMapActor = CreateActor<TileMap>(static_cast<int>(UPDATE_ORDER::Map), "TileMap");

	TileMapActor->BaseSetting(101, 219, "Floor1", "Overworld.png");

	TileMapActor->CreateTileMap(TILE_TYPE::BG, "BG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::BGA, "BGA.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::FG, "FG.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::WALL, "WALL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::COL, "COL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::TCOL, "TCOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::ACOL, "ACOL.tmd");
	TileMapActor->CreateTileMap(TILE_TYPE::MAT, "MAT.tmd");

	TileMapActor->TileTexureSetting();
	TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);


	// TileMap Setting
	PlayerActor->TileMapSetting(TileMapActor);
	ArrowActor->TileMapSetting(TileMapActor);

	SludgeRoomEntranceOverlayActor = CreateActor<OverlayActor>(UPDATE_ORDER::Map);
	SludgeRoomEntranceOverlayActor->Transform.SetLocalPosition({ 1616.0f, -3232.0f });
	SludgeRoomEntranceOverlayActor->SetScale({ 96.0f, 96.0f });
	SludgeRoomEntranceOverlayActor->SetAlpha(0.4f);

	YetiRoomEntranceOverlayActor = CreateActor<OverlayActor>(UPDATE_ORDER::Map);
	YetiRoomEntranceOverlayActor->Transform.SetLocalPosition({ 1104.0f, -2944.0f });
	YetiRoomEntranceOverlayActor->SetScale({ 96.0f, 96.0f });
	YetiRoomEntranceOverlayActor->SetAlpha(0.4f);



	// Map Actor
	SpaceBarText = CreateActor<TextActor>(UPDATE_ORDER::Map);
	SpaceBarText->Init("SPACE", float4{ 0.13f, 0.15f, 0.22f, 1.0f }, 25.0f);
	SpaceBarText->Transform.SetLocalPosition({ 1638.0f, -4913.0f });

	ShiftText = CreateActor<TextActor>(UPDATE_ORDER::Map);
	ShiftText->Init("SHIFT", float4{ 0.13f, 0.15f, 0.22f, 1.0f }, 25.0f);
	ShiftText->Transform.SetLocalPosition({ 2064.0f, -4726.0f });

	SludgeClearLight = CreateActor<ClearLight>(UPDATE_ORDER::Map);
	SludgeClearLight->Transform.SetLocalPosition({ 1616.0f, -3120.0f });

	YetiClearLight = CreateActor<ClearLight>(UPDATE_ORDER::Map);
	YetiClearLight->Transform.SetLocalPosition({ 1104.0f, -2832.0f });

	ColossusClearLight = CreateActor<ClearLight>(UPDATE_ORDER::Map);
	ColossusClearLight->Transform.SetLocalPosition({ 1616.0f, -2448.0f });

	EmptyClearLight = CreateActor<ClearLight>(UPDATE_ORDER::Map);
	EmptyClearLight->Transform.SetLocalPosition({ 2128.0f, -2832.0f });
	EmptyClearLight->LightOn();

	SludgeClearLight2 = CreateActor<ClearLight2>(UPDATE_ORDER::Map);
	SludgeClearLight2->Transform.SetLocalPosition({ 1616.0f, -1008.0f });

	YetiClearLight2 = CreateActor<ClearLight2>(UPDATE_ORDER::Map);
	YetiClearLight2->Transform.SetLocalPosition({ 1520.0f, -1104.0f });

	ColossusClearLight2 = CreateActor<ClearLight2>(UPDATE_ORDER::Map);
	ColossusClearLight2->Transform.SetLocalPosition({ 1616.0f, -1200.0f  });

	EmptyClearLight2 = CreateActor<ClearLight2>(UPDATE_ORDER::Map);
	EmptyClearLight2->Transform.SetLocalPosition({ 1712.0f, -1104.0f });
	EmptyClearLight2->LightOn();

	CrystalBallActor = CreateActor<CrystalBall>(UPDATE_ORDER::Map);
	CrystalBallActor->Transform.SetLocalPosition({ 1616.0f, -5696.0f });

	StartDoorActor = CreateActor<StartDoor>(UPDATE_ORDER::Map);
	StartDoorActor->Transform.SetLocalPosition({ 1616.0f, -5408.0f });
	StartDoorActor->SetTileMap(TileMapActor.get());

	// Ending Element
	EndingDoorActor = CreateActor<EndingDoor>(UPDATE_ORDER::Map);
	EndingDoorActor->Transform.SetLocalPosition({ 1616.0f ,-896.0f });
	EndingDoorActor->SetPlayer(PlayerActor.get());
	EndingDoorActor->SetTileMap(TileMapActor.get());

	EndingTrigger = CreateActor<TriggerBox>(UPDATE_ORDER::TriggerBox);
	EndingTrigger->Transform.SetLocalPosition({ 1616.0f, -848.0f });
	EndingTrigger->SetPlaceScale({ 352.0f, 32.0f });
	EndingTrigger->SetEnterTriggerFunc(std::bind(&Floor1::EndingFunc, this));
	EndingTrigger->Off();

	LightEffectOverlayActor = CreateActor<FadeScreenOverlay>(UPDATE_ORDER::Map);
	LightEffectOverlayActor->SetAlpha(0.0f);

	OpenDoorTrigger = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToColossusRoom");
	OpenDoorTrigger->Transform.SetLocalPosition({ 1616.0f ,-1100.0f });
	OpenDoorTrigger->SetPlaceScale({ 480.0f, 32.0f });
	OpenDoorTrigger->SetEnterTriggerFunc(std::bind(&Floor1::OpenDoorFunc, this));
	OpenDoorTrigger->Off();
}

void Floor1::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
	BossStateUpdate();

	if (false == StartProcessingIsEnd)
	{
		StartProcessing();
	}
	else
	{
		BossDeathCheck();
	}

	if (true == EndingDoorStart)
	{
		EndingProcessing();
	}

	StartDoorProcessing();

	if (true == GameEngineInput::IsDown('J', this))
	{
		PlayLevelBase::ColossusIsDeath = true;
		PlayLevelBase::SludgeIsDeath = true;
		PlayLevelBase::YetiIsDeath = true;
	}

	if (true == GameEngineInput::IsDown('0', this))
	{
		PlayerActor->Transform.SetLocalPosition({ 1616.0f, -1480.0f });
		PlayerActor->ChangeState(PLAYER_STATE::StandUp);
		return;
	}
}

void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	StartProcessingIsEnd = false;
	GameEngineInput::InputObjectOn(PlayerActor.get());
	if (false == BossIsDeath)
	{
		SpawnBoss();
	}

	BackgroundPlay("Overworld1.ogg", 10000);
	AmbiencePlay("StillLake.ogg", 10000);
}

void Floor1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
	SetBackgroundVolume(0.5f);
	if (false == BossIsDeath)
	{
		ReleaseBoss();
	}

	//if (true == EndingIsOn)
	//{
	//	EndingIsOn = false;
	//	AllBossClear = false;
	//	DoorEndPrecessingIsEnd = false;
	//}
}

void Floor1::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	if (nullptr != _PrevLevel)
	{
		PlayLevelBase* DownCastingLevel = dynamic_cast<PlayLevelBase*>(_PrevLevel);
		if (nullptr != DownCastingLevel)
		{
			if (true == DownCastingLevel->PlayerIsDeath())
			{
				PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3840.0f });
				PlayerActor->ChangeState(PLAYER_STATE::StandUp);
				return;
			}
		}
		
		if ("02.SludgeHeartRoom" == _PrevLevel->GetName())
		{
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::ExitLevel);
			return;
		}
		else if ("03.YetiRoom" == _PrevLevel->GetName())
		{
			PlayerActor->Transform.SetLocalPosition({ 1104.0f, -2882.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::ExitLevel);
			return;
		}
		else
		{
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -6560.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::StandUp);
			return;
		}
	}
}

void Floor1::SpawnBoss()
{
	if (nullptr == LeftHandActor)
	{
		LeftHandActor = CreateActor<Hand>(UPDATE_ORDER::Boss);
		LeftHandActor->Init(HAND_DIR::Left);
		LeftHandActor->SetEnymePlayer(PlayerActor.get());
		LeftHandActor->Transform.SetLocalPosition({ 1488.0f, -1968.0f });
		LeftHandActor->ChangeState(HAND_STATE::Sleep);
	}

	if (nullptr == RightHandActor)
	{
		RightHandActor = CreateActor<Hand>(UPDATE_ORDER::Boss);
		RightHandActor->Init(HAND_DIR::Right);
		RightHandActor->SetEnymePlayer(PlayerActor.get());
		RightHandActor->Transform.SetLocalPosition({ 1744.0f, -1968.0f });
		RightHandActor->ChangeState(HAND_STATE::Sleep);
	}

	if (nullptr == BossBodyActor)
	{
		BossBodyActor = CreateActor<ColossusBody>(UPDATE_ORDER::Boss);
		BossBodyActor->Transform.SetLocalPosition({ 1616.0f, -1888.0f });
		BossBodyActor->ChangeState(BODY_STATE::Sleep);
		BossBodyActor->SetEnymePlayer(PlayerActor.get());
		BossBodyActor->SetEnymeArrow(ArrowActor.get());
		BossBodyActor->SetLeftHand(LeftHandActor.get());
		BossBodyActor->SetRightHand(RightHandActor.get());

		LeftHandActor->SetBodyActor(BossBodyActor.get());
		RightHandActor->SetBodyActor(BossBodyActor.get());
	}

	if (nullptr == LeftHandPlayerDetectionRange)
	{
		LeftHandPlayerDetectionRange = CreateActor<TriggerBox>(UPDATE_ORDER::TriggerBox);
		LeftHandPlayerDetectionRange->Transform.SetLocalPosition({ 1386.0f, -2140.0f });
		LeftHandPlayerDetectionRange->SetPlaceScale({ 410.0f, 524.0f });
		LeftHandPlayerDetectionRange->SetEnterTriggerFunc(std::bind(&Floor1::EnterLeftDetectionRange, this));
	}

	if (nullptr == RightHandPlayerDetectionRange)
	{
		RightHandPlayerDetectionRange = CreateActor<TriggerBox>(UPDATE_ORDER::TriggerBox);
		RightHandPlayerDetectionRange->Transform.SetLocalPosition({ 1846.0f, -2140.0f });
		RightHandPlayerDetectionRange->SetPlaceScale({ 410.0f, 524.0f });
		RightHandPlayerDetectionRange->SetEnterTriggerFunc(std::bind(&Floor1::EnterRightDetectionRange, this));
	}

	BossPageIsFight = false;
	ShowtingProcessingIsEnd = false;
	BossHitProcessingIsEnd = false;
}

void Floor1::SpawnTriggerBox()
{
	EnterTheSludgeRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToSludgeRoom");
	EnterTheSludgeRoom->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
	EnterTheSludgeRoom->SetPlaceScale({ 96.0f, 60.0f });
	EnterTheSludgeRoom->SetEnterTriggerFunc(std::bind(&Floor1::EnterRoomTriggerFunc, this));
	EnterTheSludgeRoom->SetStayTriggerFunc(std::bind(&Floor1::StaySludgeRoomTriggerFunc, this));

	EnterTheYetiRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToYetiRoom");
	EnterTheYetiRoom->Transform.SetLocalPosition({ 1104.0f, -2882.0f });
	EnterTheYetiRoom->SetPlaceScale({ 96.0f, 60.0f });
	EnterTheYetiRoom->SetEnterTriggerFunc(std::bind(&Floor1::EnterRoomTriggerFunc, this));
	EnterTheYetiRoom->SetStayTriggerFunc(std::bind(&Floor1::StayYetiRoomTriggerFunc, this));

	EnterTheColossusRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToColossusRoom");
	EnterTheColossusRoom->Transform.SetLocalPosition({ 1616.0f, -2576.0f });
	EnterTheColossusRoom->SetPlaceScale({ 96.0f, 32.0f });
	EnterTheColossusRoom->SetEnterTriggerFunc(std::bind(&Floor1::EnterColossusRoomTriggerFunc, this));
	EnterTheColossusRoom->Off();

}


void Floor1::StaySludgeRoomTriggerFunc()
{
	PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);

	if (nullptr == FadeOutActor)
	{
		FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
		FadeOutActor->Init(FadeColor::Black, 1.5f);
	}
	
	if (true == FadeOutActor->FadeIsEnd())
	{
		PlayerActor->ChangeState(PLAYER_STATE::Idle);
		GameEngineCore::ChangeLevel("02.SludgeHeartRoom");
	}
}

void Floor1::StayYetiRoomTriggerFunc()
{
	PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);

	if (nullptr == FadeOutActor)
	{
		FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
		FadeOutActor->Init(FadeColor::Black, 1.5f);
	}

	if (true == FadeOutActor->FadeIsEnd())
	{
		PlayerActor->ChangeState(PLAYER_STATE::Idle);
		GameEngineCore::ChangeLevel("03.YetiRoom");
	}
}

void Floor1::ReleaseTriggerBox()
{
	if (nullptr != EnterTheSludgeRoom)
	{
		EnterTheSludgeRoom->Death();
		EnterTheSludgeRoom = nullptr;
	}

	if (nullptr != EnterTheYetiRoom)
	{
		EnterTheYetiRoom->Death();
		EnterTheYetiRoom = nullptr;
	}

	if (nullptr != EnterTheColossusRoom)
	{
		EnterTheColossusRoom->Death();
		EnterTheColossusRoom = nullptr;
	}
}

void Floor1::ReleaseBoss()
{
	if (nullptr != BossBodyActor)
	{
		BossBodyActor->Death();
		BossBodyActor = nullptr;
	}

	if (nullptr != LeftHandActor)
	{
		LeftHandActor->Death();
		LeftHandActor = nullptr;
	}

	if (nullptr != RightHandActor)
	{
		RightHandActor->Death();
		RightHandActor = nullptr;
	}

	if (nullptr != LeftHandPlayerDetectionRange)
	{
		LeftHandPlayerDetectionRange->Death();
		LeftHandPlayerDetectionRange = nullptr;
	}

	if (nullptr != RightHandPlayerDetectionRange)
	{
		RightHandPlayerDetectionRange->Death();
		RightHandPlayerDetectionRange = nullptr;
	}
}

void Floor1::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	// BGM, AMBIENCE
	GlobalLoad::LoadSound("StillLake.ogg", "Resource\\Sound\\Ambience\\");
	GlobalLoad::LoadSound("Overworld1.ogg", "Resource\\Sound\\BGM\\");
	GlobalLoad::LoadSound("Colossus.ogg", "Resource\\Sound\\BGM\\");

	GlobalLoad::LoadSound("OpenBigDoor.ogg", "Resource\\Sound\\Effect\\Door\\");
	GlobalLoad::LoadSound("CloseBigDoor.ogg", "Resource\\Sound\\Effect\\Door\\");
	GlobalLoad::LoadSound("DoorEnd.ogg", "Resource\\Sound\\Effect\\Door\\");

}

void Floor1::EnterLeftDetectionRange()
{
	AttackDir = ATTACKHAND_DIR::Left;
	Hand::AttackModeIsSwitch = true;
}

void Floor1::EnterRightDetectionRange()
{
	AttackDir = ATTACKHAND_DIR::Right;
	Hand::AttackModeIsSwitch = true;
}

void Floor1::SwitchToAttackModeLeftHand()
{
	if (nullptr != LeftHandActor)
	{
		LeftHandActor->ChangeState(HAND_STATE::Hover);
	}

	if (nullptr != RightHandActor)
	{
		RightHandActor->ChangeState(HAND_STATE::Hide);
	}
}

void Floor1::SwitchToAttackModeRightHand()
{
	if (nullptr != LeftHandActor)
	{
		LeftHandActor->ChangeState(HAND_STATE::Hide);
	}

	if (nullptr != RightHandActor)
	{
		RightHandActor->ChangeState(HAND_STATE::Hover);
	}
}


void Floor1::BossPageProcessing()
{
	EnterTheColossusRoom->On();
}


void Floor1::OutputBossName()
{
	// BossName Actor
	BossNameBack = CreateActor<FadeImage>(UPDATE_ORDER::UI);
	BossNameBack->Init("BossNameBG.png");
	BossNameBack->Transform.SetLocalPosition({ 0.0f, -305.0f });

	BossNameScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossNameScript->Init("GOL IATH", FONT_TYPE::ANCIENT, { 32.0f, 32.0f }, 2.0f);
	BossNameScript->FadeInit();
	BossNameScript->Transform.SetLocalPosition({ 5.0f, -290.0f });

	BossDescriptionScript = CreateActor<AncientScript>(UPDATE_ORDER::UI);
	BossDescriptionScript->Init("GUADIAN OF THE FIRST GATE", FONT_TYPE::ANCIENT, { 16.0f, 16.0f });
	BossDescriptionScript->FadeInit();
	BossDescriptionScript->Transform.SetLocalPosition({ 0.0f, -325.0f });
}

void Floor1::BossStateUpdate()
{
	if (false == BossIsDeath)
	{
		if (BODY_STATE::Death == BossBodyActor->GetCurState())
		{
			BossIsDeath = true;
			ColossusIsDeath = true;
			BossDeathProcessing();
			EnterTheColossusRoom->Off();
		}

		if (false == BossHitProcessingIsEnd &&
			BODY_STATE::Hit == BossBodyActor->GetCurState())
		{
			BossHitProcessingIsEnd = true;
			BossHitProcessing();
			return;
		}

		if (BODY_STATE::WakeUp == BossBodyActor->GetCurState())
		{
			SetBackgroundVolume(0.0f);
		}

		if (false == ShowtingProcessingIsEnd && 
			BODY_STATE::Shouting == BossBodyActor->GetCurState())
		{
			ShowtingProcessingIsEnd = true;
			OutputBossName();
			Background2Play("Colossus.ogg", 10000);
		}

		if (BODY_STATE::Idle == BossBodyActor->GetCurState() &&
			false == BossPageIsFight)
		{
			BossPageIsFight = true;
			BossPageProcessing();
		}

		// 공격모드 변경
		if (true == Hand::AttackModeIsSwitch &&
			true == Hand::ModeSwitchIsAble())
		{
			Hand::AttackModeIsSwitch = false;
			switch (AttackDir)
			{
			case ATTACKHAND_DIR::NONE:
			case ATTACKHAND_DIR::Left:
				SwitchToAttackModeLeftHand();
				break;
			case ATTACKHAND_DIR::Right:
				SwitchToAttackModeRightHand();
				break;
			default:
				break;
			}
		}
	}
}

void Floor1::BossHitProcessing()
{
	Background2Stop();
	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::White, 3.0f, 0.5f);
	}
}

void Floor1::BossDeathProcessing()
{
	SetBackgroundVolume(0.5f);
	BackFadeInVolumeOn();
}

void Floor1::BossDeathCheck()
{
	if (true == SludgeIsDeath)
	{
		SludgeClearLight->LightOn();
		SludgeClearLight2->LightOn();
	}

	if (true == YetiIsDeath)
	{
		YetiClearLight->LightOn();
		YetiClearLight2->LightOn();
	}

	if (true == ColossusIsDeath)
	{
		ColossusClearLight->LightOn();
		ColossusClearLight2->LightOn();
	}

	if (false == AllBossClear &&
		true == SludgeIsDeath &&
		true == YetiIsDeath &&
		true == ColossusIsDeath)
	{
		AllBossClear = true;
		OpenDoorTrigger->On();
	}
}

void Floor1::DoorEndPrecessing()
{
	LightEffectOverlayActor->FadeInOn(2.0f);
	EndingDoorActor->FocusOff();
	EndingTrigger->On();
}

void Floor1::EndingProcessing()
{
	if (false == EndingIsOn &&
		false == DoorEndProcessingIsEnd &&
		true == EndingDoorActor->OpenIsEnd())
	{
		DoorEndProcessingIsEnd = true;
		EffectStop();
		EffectPlay("DoorEnd.ogg");
		DoorEndPrecessing();
	}

	if (false == ClearlightEffectOffProcessing &&
		true == DoorEndProcessingIsEnd &&
		true == LightEffectOverlayActor->FadeInIsEnd())
	{
		ClearLight2EffectOff();
		ClearlightEffectOffProcessing = true;
		GameEngineInput::InputObjectOn(PlayerActor.get());
	}

	if (true == EndingIsOn)
	{
		if (nullptr != FadeOutActor &&
			true == FadeOutActor->FadeIsEnd())
		{
			EffectStop();
			EffectPlay("DoorEnd.ogg");
			GameEngineCore::ChangeLevel("04.Ending");
		}
	}
}

void Floor1::ClearLight2EffectOff()
{
	SludgeClearLight2->EffectOff();
	YetiClearLight2->EffectOff();
	ColossusClearLight2->EffectOff();
	EmptyClearLight2->EffectOff();
}


void Floor1::StartProcessing()
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

void Floor1::EnterColossusRoomTriggerFunc()
{
	if (false == BossIsDeath)
	{
		BossBodyActor->ChangeState(BODY_STATE::Sleep);
		LeftHandActor->ChangeState(HAND_STATE::Death);
		RightHandActor->ChangeState(HAND_STATE::Death);

		Background2Stop();
		BossDeathProcessing();

		BossPageIsFight = false;
		ShowtingProcessingIsEnd = false;
		BossHitProcessingIsEnd = false;
		EnterTheColossusRoom->Off();

		PlayerActor->GetArrow();
		ArrowActor->ChangeState(ARROW_STATE::Hold);
	}
}

void Floor1::OpenDoorFunc()
{
	EndingDoorStart = true;
	EffectPlay("OpenBigDoor.ogg");
	OpenDoorTrigger->Off();
	LightEffectOverlayActor->FadeOutOn(0.4f, 2.0f);
	EndingDoorActor->FocusOn();
	EndingDoorActor->OpenDoor();

	SludgeClearLight2->EffectOn();
	YetiClearLight2->EffectOn();
	ColossusClearLight2->EffectOn();
	EmptyClearLight2->EffectOn();

	GameEngineInput::InputObjectOff(PlayerActor.get());
}

void Floor1::EndingFunc()
{
	EndingIsOn = true;
	EndingTrigger->Off();
	EffectPlay("CloseBigDoor.ogg");
	EndingDoorActor->CloseDoor();
	PlayerActor->ChangeState(PLAYER_STATE::EndingLevel);
	GameEngineInput::InputObjectOff(PlayerActor.get());

	if (nullptr == FadeOutActor)
	{
		FadeOutActor = CreateActor<FadeOut>(UPDATE_ORDER::UI);
		FadeOutActor->Init(FadeColor::Black, 4.4f);
	}

	BackFadeOutVolumeOn();
	AmbienceFadeOutVolumeOn();
}

void Floor1::CreateSpreadDustParticle(const float4& _Pos, int _Num)
{
	int Count = _Num;
	while (0 < Count)
	{
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
		SpreadParticleActor = CreateActor<SpreadParticle>(UPDATE_ORDER::Particle);

		float4 DirBasis = float4::GetUnitVectorFromDeg(Inst.RandomFloat(0.0f, 360.0f));

		SpreadParticleActor->SetRenderer("BossDust.png", Inst.RandomInt(0, 5), 64.0f, DirBasis, 1.0f, 0.5f);
		SpreadParticleActor->SetSpeed(100.0f, 400.0f);
		SpreadParticleActor->Transform.SetLocalPosition(_Pos);
		--Count;
	}
}

void Floor1::CreateSpreadDust2Particle(const float4& _Pos, int _Num)
{
	int Count = _Num;
	while (0 < Count)
	{
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
		SpreadParticleActor = CreateActor<SpreadParticle>(UPDATE_ORDER::Particle);

		float4 DirBasis = float4::GetUnitVectorFromDeg(Inst.RandomFloat(0.0f, 360.0f));

		SpreadParticleActor->SetRenderer("Dust.png", Inst.RandomInt(0, 1), 8.0f, DirBasis, 1.0f, 0.6f);
		SpreadParticleActor->SetSpeed(100.0f, 400.0f);
		SpreadParticleActor->Transform.SetLocalPosition(_Pos);
		--Count;
	}
}

void Floor1::StartDoorProcessing()
{
	if (false == StartDoorIsOpen &&
		true == CrystalBallActor->IsHitArrow())
	{
		StartDoorIsOpen = true;
		StartDoorActor->OpenDoor();
	}
}
