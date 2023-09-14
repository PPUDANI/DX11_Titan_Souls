#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "Player.h"

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
	// 타일맵 완성되면 뷰 모드를 세팅해야함
	switch (CurViewMode)
	{
	case VIEW_MODE::Main:
		break;
	case VIEW_MODE::Collision:
		break;
	case VIEW_MODE::Material:
		break;
	default:
		break;
	}
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevelBase::LevelEnd(GameEngineLevel* _PrevLevel)
{

}