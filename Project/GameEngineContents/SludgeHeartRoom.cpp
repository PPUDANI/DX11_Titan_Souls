#include "PreCompile.h"
#include "SludgeHeartRoom.h"

#include "TileMap.h"

SludgeHeartRoom::SludgeHeartRoom()
{
}

SludgeHeartRoom::~SludgeHeartRoom()
{
}

void SludgeHeartRoom::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);
	TileMapActor->Init(60, 80, "SludgeHeart", "Underworld.png");

}

void SludgeHeartRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void SludgeHeartRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	PlayerActor->Transform.SetLocalPosition({ 1008.0f, -1856.0f });

}

void SludgeHeartRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}
