#include "PreCompile.h"
#include "YetiRoom.h"

YetiRoom::YetiRoom()
{
}

YetiRoom::~YetiRoom()
{
}

void YetiRoom::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);
	TileMapActor->BaseSetting(60, 60, "Yeti", "Underworld.png");
}

void YetiRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void YetiRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1824.0f });
}

void YetiRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
}
