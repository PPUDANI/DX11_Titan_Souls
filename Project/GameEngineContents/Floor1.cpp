#include "PreCompile.h"
#include "Floor1.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

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

	if (nullptr != FadeInActor &&
		true == FadeInActor->FadeIsEnd())
	{
		SpawnTriggerBox();
		FadeInActor->Death();
		FadeInActor = nullptr;
	}
}


void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);

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
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3270.0f });
			PlayerActor->ChangeStateFromLevel(PLAYER_STATE::StandUp);
		}
	}
	else
	{
		PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3270.0f });
		PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	}
	return;
}

void Floor1::SpawnTriggerBox()
{
	EnterTheSludgeRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToSludgeRoom");
	EnterTheSludgeRoom->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
	EnterTheSludgeRoom->SetPlaceScale({ 90.0f, 60.0f });
	EnterTheSludgeRoom->SetEnterTriggerFunc(std::bind(&Floor1::EnterRoomTriggerFunc, this));
	EnterTheSludgeRoom->SetStayTriggerFunc(std::bind(&Floor1::SludgeRoomStayTriggerFunc, this));

	EnterTheYetiRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToYetiRoom");
	EnterTheYetiRoom->Transform.SetLocalPosition({ 1104.0f, -2882.0f });
	EnterTheYetiRoom->SetPlaceScale({ 90.0f, 60.0f });
	EnterTheYetiRoom->SetEnterTriggerFunc(std::bind(&Floor1::EnterRoomTriggerFunc, this));
	EnterTheYetiRoom->SetStayTriggerFunc(std::bind(&Floor1::YetiRoomStayTriggerFunc, this));

}

void Floor1::SludgeRoomStayTriggerFunc()
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

void Floor1::YetiRoomStayTriggerFunc()
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
}

void Floor1::SoundLoad()
{
	// BGM, AMBIENCE
	GlobalLoad::LoadSound("StillLake.ogg", "Resource\\Sound\\Ambience\\");
	GlobalLoad::LoadSound("Overworld1.ogg", "Resource\\Sound\\BGM\\");
	GlobalLoad::LoadSound("Colossus.ogg", "Resource\\Sound\\BGM\\");

}
