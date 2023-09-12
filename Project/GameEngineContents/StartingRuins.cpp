#include "PreCompile.h"
#include "StartingRuins.h"

#include "Player.h"
#include "TestMap.h"

StartingRuins::StartingRuins()
{
}

StartingRuins::~StartingRuins()
{
}

void StartingRuins::Start()
{
	PlayLevelBase::Start();

	Map = CreateActor<TestMap>(UPDATE_ORDER::Map);
	Map->Transform.SetLocalPosition({ 0.0f, 0.0f });
}

void StartingRuins::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void StartingRuins::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
}

void StartingRuins::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
}
