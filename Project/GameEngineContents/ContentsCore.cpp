#include "PreCompile.h"
#include "ContentsCore.h"

// All Level
#include "TitleLevel.h"
#include "Jam.h"
#include "Floor1.h"
#include "SludgeHeartRoom.h"
#include "GollathRoom.h"
#include "YetiRoom.h"
#include "KnightElhananRoom.h"
#include "TitleLevel.h"
#include "PlayLevelBase.h"
#include <GameEngineCore/GameEngineRenderTarget.h>
ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	// Clear Color Setting
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 0 });

	// Map Texture Load
	GlobalLoad::LoadSpriteCut(16, 16, "Spectiles.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Jam.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Underworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Overworld.png", "Resource\\Texture\\Map\\");

	// Create Level
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<Jam>("Jam");
	GameEngineCore::CreateLevel<Floor1>("Floor1");
	GameEngineCore::CreateLevel<SludgeHeartRoom>("SludgeHeartRoom");
	GameEngineCore::CreateLevel<GollathRoom>("GollathRoom");
	GameEngineCore::CreateLevel<YetiRoom>("YetiRoom");
	GameEngineCore::CreateLevel<KnightElhananRoom>("KnightElhananRoom");
	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
	// 임시 레벨 변경
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("StartingRuins");
	}
	
	// 임시 레벨 변경
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		GameEngineCore::ChangeLevel("Floor1");
	}
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("SludgeHeartRoom");
	}
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		GameEngineCore::ChangeLevel("Jam");
	}
}

void ContentsCore::Release()
{

}