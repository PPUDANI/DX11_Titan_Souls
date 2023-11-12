#include "PreCompile.h"
#include "GlobalLoad.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineResources.h>

#include <GameEngineBase/GameEnginePath.h>

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}


void GlobalLoad::LoadSpriteCut(int _IndexX, int _IndexY, std::string_view _FileName, std::string_view _FilePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resource");
	Path.MoveChild(_FilePath);
	if (nullptr == GameEngineTexture::Find(_FileName))
	{
		GameEngineTexture::Load(Path.PlusFilePath(_FileName));
		GameEngineSprite::CreateCut(_FileName, _IndexX, _IndexY);
	}
}

void GlobalLoad::LoadSpriteSingle(std::string_view _FileName, std::string_view _FilePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resource");
	Path.MoveChild(_FilePath);
	if (nullptr == GameEngineTexture::Find(_FileName))
	{
		GameEngineTexture::Load(Path.PlusFilePath(_FileName));
		GameEngineSprite::CreateSingle(_FileName);
	}
}
