#include "PreCompile.h"
#include "Floor1.h"

Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Start()
{
	PlayLevelBase::Start();

	TileMapActor = CreateActor<TileMap>();
	TileMapActor->Init(101, 219, "Floor1", "Overworld.png");
	
}

void Floor1::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void Floor1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PlayLevelBase::LevelStart(_PrevLevel);
	PlayerActor->Transform.SetLocalPosition({ 1616.0f, -6560.0f });
	GetMainCamera()->Transform.SetLocalPosition(PlayerActor->Transform.GetWorldPosition());
}

void Floor1::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayLevelBase::LevelEnd(_NextLevel);

	// ���� �����̵� ����
}