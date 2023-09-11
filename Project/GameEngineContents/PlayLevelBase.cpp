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
}

void PlayLevelBase::Update(float _Delta)
{
	
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevelBase::LevelEnd(GameEngineLevel* _PrevLevel)
{

}