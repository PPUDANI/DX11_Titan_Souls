#include "PreCompile.h"
#include "GlobalLoad.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineBase/GameEnginePath.h>

bool GlobalLoad::PlayerIsLoad = false;

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}

void GlobalLoad::PlayerLoad()
{
	if (false == PlayerIsLoad)
	{
		PlayerIsLoad = true;

		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Player\\PlayerMove.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateCut("PlayerMove.png", 15, 8);
	}
	
}

void GlobalLoad::MapLoad()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Map\\TestMap.png");
	GameEngineTexture::Load(Path.GetStringPath());
	GameEngineSprite::CreateSingle("TestMap.png");
}