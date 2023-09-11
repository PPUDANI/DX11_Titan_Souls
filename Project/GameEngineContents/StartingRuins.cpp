#include "PreCompile.h"
#include "StartingRuins.h"

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
	//Map = CreateActor<TestMap>(UPDATE_ORDER::Map);
	//Map->Transform.SetLocalPosition({ 0.0f, 0.0f });

	GlobalLoad::LoadSpriteCut(64, 64, "Underworld.png", "Resource\\Texture\\Map\\");
	Map = CreateActor <TileMap>(UPDATE_ORDER::Map);
	Map->TileMapInit(60, 80, "Underworld.png");
	Map->SetTileData("Resource\\TileMapData\\SludgeHeart\\BG.tmd");
	Map->SetTileTexture();
}

void StartingRuins::Update(float _Delta)
{
	PlayLevelBase::Update(_Delta);
}

void StartingRuins::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void StartingRuins::LevelEnd(GameEngineLevel* _NextLevel)
{

}
