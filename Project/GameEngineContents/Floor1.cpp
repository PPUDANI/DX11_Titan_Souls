#include "PreCompile.h"
#include "Floor1.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "Hand.h"
#include "ColossusBody.h"


Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Start()
{
	PlayLevelBase::Start();
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

}

void Floor1::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
	BossStateUpdate();

	if (false == StartProcessingIsEnd)
	{
		StartProcessing();
	}
}


void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	StartProcessingIsEnd = false;

	if (false == BossIsDeath)
	{
		SpawnBoss();
	}

	if (nullptr == FadeInActor)
	{
		FadeInActor = CreateActor<FadeIn>(UPDATE_ORDER::UI);
		FadeInActor->Init(FadeColor::Black, 1.5f);
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

}

void Floor1::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	if (nullptr != _PrevLevel)
	{
		if("00.TitleLevel" == _PrevLevel->GetName())
		{
			//PlayerActor->Transform.SetLocalPosition({ 1616.0f, -6560.0f });
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3270.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::StandUp);
		}
		else if ("02.SludgeHeartRoom" == _PrevLevel->GetName())
		{
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::ExitLevel);
		}
		else if ("03.YetiRoom" == _PrevLevel->GetName())
		{
			PlayerActor->Transform.SetLocalPosition({ 1104.0f, -2882.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::ExitLevel);
		}
		else
		{
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -2670.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::StandUp);
		}
	}
	else
	{
		PlayerActor->Transform.SetLocalPosition({ 1616.0f, -2670.0f });
		PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	}
	return;
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
			BossDeathProcessing();
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

		if (false == BossPageIsFight &&
			BODY_STATE::Idle == BossBodyActor->GetCurState())
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
	}
}
