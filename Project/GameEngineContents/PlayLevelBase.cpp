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
	PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
	PlayerActor->Transform.SetLocalPosition({0.0f, 0.0f});

	Player::MainPlayer = PlayerActor;
}

void PlayLevelBase::Update(float _Delta)
{
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

}

void PlayLevelBase::LevelEnd(GameEngineLevel* _PrevLevel)
{

}