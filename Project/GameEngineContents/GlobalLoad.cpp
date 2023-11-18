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
	if (nullptr != GameEngineTexture::Find(_FileName))
	{
		return;
	}

	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resource");
	Path.MoveChild(_FilePath);

	GameEngineTexture::Load(Path.PlusFilePath(_FileName));
	GameEngineSprite::CreateCut(_FileName, _IndexX, _IndexY);
}

void GlobalLoad::LoadSound(std::string_view _FileName, std::string_view _FilePath)
{
	if (nullptr != GameEngineSound::FindSound(_FileName))
	{
		return;
	}

	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resource");

	Path.MoveChild(_FilePath);

	GameEngineSound::SoundLoad(_FileName, Path.PlusFilePath(_FileName));
}

void GlobalLoad::LoadSpriteSingle(std::string_view _FileName, std::string_view _FilePath)
{
	if (nullptr != GameEngineTexture::Find(_FileName))
	{
		return;
	}

	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resource");
	Path.MoveChild(_FilePath);

	GameEngineTexture::Load(Path.PlusFilePath(_FileName));
	GameEngineSprite::CreateSingle(_FileName);
}
