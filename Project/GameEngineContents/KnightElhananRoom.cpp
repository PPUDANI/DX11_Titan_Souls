#include "PreCompile.h"
#include "KnightElhananRoom.h"

KnightElhananRoom::KnightElhananRoom()
{
}

KnightElhananRoom::~KnightElhananRoom()
{
}

void KnightElhananRoom::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>(UPDATE_ORDER::Map);
	TileMapActor->BaseSetting(59, 60, "KnightElhanan", "Underworld.png");
}

void KnightElhananRoom::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void KnightElhananRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	PlayerActor->Transform.SetLocalPosition({ 944.0f, -1760.0f });
}

void KnightElhananRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);
}
