#include "PreCompile.h"


PlayLevelBase::PlayLevelBase()
{
}

PlayLevelBase::~PlayLevelBase()
{
}

void PlayLevelBase::Start()
{
	GlobalLoad::PlayerLoad();
	PlayerActor = CreateActor<Player>(OBJECT_ELEMENT::Player);
	PlayerActor->Transform.SetLocalPosition({ 100.0f, 100.0f});
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