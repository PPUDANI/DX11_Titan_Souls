#include "PreCompile.h"
#include "Jam.h"

Jam::Jam()
{
}

Jam::~Jam()
{
}

void Jam::Start()
{
	PlayLevelBase::Start();

	//Map = CreateActor<TestMap>(UPDATE_ORDER::Map);
	//Map->Transform.SetLocalPosition({ 0.0f, 0.0f });

	TileMapActor = CreateActor<TileMap>();
	//TileMapActor->BaseSetting(185, 160, "Jam", "Jam.png");
}

void Jam::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void Jam::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	PlayerActor->Transform.SetLocalPosition({ 2768.0f, -2688.0f });
}

void Jam::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// 액터 레벨이동 구현
}
