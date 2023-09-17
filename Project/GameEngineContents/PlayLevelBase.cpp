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
	CreatePlayerElement();
}

void PlayLevelBase::Update(float _Delta)
{
	std::string FPS;
	FPS = std::to_string(static_cast<int>(1.0f / _Delta));
	FPS += "\n";
	OutputDebugStringA(FPS.c_str());

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
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayerActor->ChangeState(PLAYER_STATE::StandUp);
	PlayerActor->SetTileMap(TileMapActor);
}

void PlayLevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void PlayLevelBase::CreatePlayerElement()
{
	// PlayerActor Setting
	if (nullptr == PlayerActor)
	{
		PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
		//if (nullptr == Player::MainPlayer)
		//{
		//	PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
		//	Player::MainPlayer = PlayerActor;
		//}
		//else
		//{
		//	PlayerActor = Player::MainPlayer;
		//}
	}

}
