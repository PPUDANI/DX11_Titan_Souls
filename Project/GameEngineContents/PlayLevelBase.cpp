#include "PreCompile.h"
#include "PlayLevelBase.h"

PlayLevelBase::PlayLevelBase()
{
}

PlayLevelBase::~PlayLevelBase()
{
}

void PlayLevelBase::Start()
{
	LevelBase::Start();

	CreatePlayerElement();
}

void PlayLevelBase::Update(float _Delta)
{
	LevelBase::Update(_Delta);

	if (true == GameEngineInput::IsDown('1'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::COLLISION_MODE);
	}
	if (true == GameEngineInput::IsDown('3'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE1);
	}
	if (true == GameEngineInput::IsDown('4'))
	{
		TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE2);
	}

	if (true == GameEngineInput::IsDown('R'))
	{
		SpawnPlayer();
	}
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelBase::LevelStart(_PrevLevel);
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	PlayerActor->SetTileMap(TileMapActor);
	SpawnPlayer();
}

void PlayLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	LevelBase::LevelEnd(_NextLevel);
}

void PlayLevelBase::CreatePlayerElement()
{
	// PlayerActor Setting
	if (nullptr == PlayerActor)
	{
		PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
		ArrowActor = CreateActor<Arrow>(UPDATE_ORDER::Player);
	}
}

void PlayLevelBase::SpawnPlayer()
{
	PlayerActor->Transform.SetLocalPosition(PlayerSpawnPos);
	ArrowActor->Transform.SetLocalPosition(PlayerSpawnPos);
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	return;
}
