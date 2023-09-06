#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "StartingRuins.h"
#include "SludgeHeartRoom.h"
#include "GollathRoom.h"
#include "YetiRoom.h"
#include "KnightElhananRoom.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
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
	
}

void ContentsCore::Release()
{

}