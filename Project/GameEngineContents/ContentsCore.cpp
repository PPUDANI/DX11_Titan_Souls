#include "PreCompile.h"
#include "ContentsCore.h"
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
	GameEngineCore::CreateLevel<TitleLevel>("StartingRuins");
	GameEngineCore::CreateLevel<TitleLevel>("SludgeHeartRoom");
	GameEngineCore::CreateLevel<TitleLevel>("GollathRoom");
	GameEngineCore::CreateLevel<TitleLevel>("YetiRoom");
	GameEngineCore::CreateLevel<TitleLevel>("KnightElhananRoom");
	GameEngineCore::CreateLevel<TitleLevel>("Room");

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
	// �ӽ� ���� ����
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("StartingRuins");
	}
	
}

void ContentsCore::Release()
{

}