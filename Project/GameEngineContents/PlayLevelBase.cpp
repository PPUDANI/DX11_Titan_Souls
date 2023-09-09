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
	GlobalLoad::PlayerLoad();
	PlayerActor = CreateActor<Player>(UPDATE_ORDER::Player);
	PlayerActor->Transform.SetLocalPosition({0.0f, 0.0f});
}

void PlayLevelBase::Update(float _Delta)
{
	GetMainCamera()->Transform.SetLocalPosition(PlayerActor->Transform.GetWorldPosition());
}

void PlayLevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevelBase::LevelEnd(GameEngineLevel* _PrevLevel)
{

}