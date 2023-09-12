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
	GlobalLoad::LoadSpriteCut(16, 16, "Spectiles.png", "Resource\\Texture\\Map\\");
	BGMap = CreateActor<TileMap>(UPDATE_ORDER::Map);
	BGMap->TileMapInit(60, 80, "Underworld.png");
	BGMap->SetTileData("Resource\\TileMapData\\SludgeHeart\\BG.tmd", 1);
	BGMap->Transform.SetLocalPosition({ -976.0f, 700.0f });
	BGMap->SetTileTexture(RENDERING_ORDER::BGMap);

	FGMap = CreateActor<TileMap>(UPDATE_ORDER::Map);
	FGMap->TileMapInit(60, 80, "Underworld.png");
	FGMap->SetTileData("Resource\\TileMapData\\SludgeHeart\\FG.tmd", 1);
	FGMap->Transform.SetLocalPosition({ -976.0f, 700.0f });
	FGMap->SetTileTexture(RENDERING_ORDER::FGMap);

	//COLMap = CreateActor<TileMap>(UPDATE_ORDER::Map);
	//COLMap->TileMapInit(60, 80, "Spectiles.png");
	//COLMap->SetTileData("Resource\\TileMapData\\SludgeHeart\\COL.tmd", 4097);
	//COLMap->Transform.SetLocalPosition({ -976.0f, 700.0f });
	//COLMap->SetTileTexture(RENDERING_ORDER::BGMap);

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
