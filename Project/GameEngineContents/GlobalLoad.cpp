#include "PreCompile.h"
#include "GlobalLoad.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineBase\GameEnginePath.h>

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}

void GlobalLoad::PlayerLoad()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Player\\PlayerMove.png");
	GameEngineTexture::Load(Path.GetStringPath());

	GameEngineSprite::CreateCut("PlayerMove.png", 15, 8);
}
