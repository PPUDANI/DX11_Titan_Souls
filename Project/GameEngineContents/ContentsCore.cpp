#include "PreCompile.h"
#include "ContentsCore.h"

// All Level
#include "TitleLevel.h"
#include "StartingRuins.h"
#include "SludgeHeartRoom.h"
#include "GollathRoom.h"
#include "YetiRoom.h"
#include "KnightElhananRoom.h"
#include "TitleLevel.h"
#include "PlayLevelBase.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GlobalLoad::LoadSpriteCut(64, 64, "Underworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(16, 16, "Spectiles.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(1, 1, "util.png", "Resource\\Texture\\Map\\");

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<StartingRuins>("StartingRuins");
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
		GameEngineCore::ChangeLevel("SludgeHeartRoom");
	}

}

void ContentsCore::Release()
{

}