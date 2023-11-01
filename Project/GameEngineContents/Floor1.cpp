#include "PreCompile.h"
#include "Floor1.h"

Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Start()
{
	PlayLevelBase::Start();

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

	EnterTheSludgeRoom = CreateActor<TriggerBox>(static_cast<int>(UPDATE_ORDER::TriggerBox), "EnterPlaceToSludgeRoom");
	EnterTheSludgeRoom->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
	EnterTheSludgeRoom->SetPlaceScale({ 90.0f, 60.0f });
	EnterTheSludgeRoom->Off();

	FadeInActor = CreateActor<Fade>(RENDERING_ORDER::UI);
	FadeInActor->SetFadeMode(FadeMode::FadeIn);
	FadeInActor->SetFadeSpeed(0.75f);
	FadeInActor->SetBlackColor();
	FadeInActor->Off();

	FadeOutActor = CreateActor<Fade>(RENDERING_ORDER::UI);
	FadeOutActor->SetFadeMode(FadeMode::FadeOut);
	FadeOutActor->SetFadeSpeed(0.75f);
	FadeOutActor->SetBlackColor();
	FadeOutActor->Off();
}

void Floor1::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);

	if (PLAYER_STATE::ExitLevel == PlayerActor->GetCurState() ||
		PLAYER_STATE::EnterLevel == PlayerActor->GetCurState())
	{
		EnterTheSludgeRoom->Off();
	}
	else
	{
		EnterTheSludgeRoom->On();
	}

	if (true == EnterTheSludgeRoom->EnterCheck())
	{
		EnterTheSludgeRoomUpdate();
	}

}


void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	FadeOutActor->FadeResetByMode();
	FadeOutActor->Off();

	FadeInActor->FadeResetByMode();
	FadeInActor->On();
}

void Floor1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}

void Floor1::SpawnPlayer(GameEngineLevel* _PrevLevel)
{
	if (nullptr != _PrevLevel)
	{
		if ("02.SludgeHeartRoom" == _PrevLevel->GetName())
		{
			PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3170.0f });
			PlayerActor->ChangeState(PLAYER_STATE::ExitLevel);
		}
	}
	else
	{
		//PlayerActor->Transform.SetLocalPosition({ 1616.0f, -6560.0f });
		PlayerActor->Transform.SetLocalPosition({ 1616.0f, -3270.0f });
		PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	}
	return;
}

void Floor1::EnterTheSludgeRoomUpdate()
{
	PlayerActor->ChangeState(PLAYER_STATE::EnterLevel);
	EnterTheSludgeRoom->Off();
	FadeOutActor->On();

	if (true == FadeOutActor->FadeIsEnd())
	{
		PlayerActor->ChangeState(PLAYER_STATE::Idle);
		EnterTheSludgeRoom->EnterCheckReset();
		GameEngineCore::ChangeLevel("02.SludgeHeartRoom");
	}
}
