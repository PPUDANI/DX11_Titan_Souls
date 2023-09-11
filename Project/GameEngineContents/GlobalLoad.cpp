#include "PreCompile.h"
#include "GlobalLoad.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineBase/GameEnginePath.h>

bool GlobalLoad::IsLoadPlayerTexture = false;
bool GlobalLoad::IsLoadBowTexutre = false;
bool GlobalLoad::IsLoadArrowInBagTexture = false;
bool GlobalLoad::IsLoadTestMapTexture = false;

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}

void GlobalLoad::LoadPlayerTexture()
{
	if (false == IsLoadPlayerTexture)
	{
		IsLoadPlayerTexture = true;

		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\PlayerElement\\Player.png");
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateCut("Player.png", 32, 32);
	}
}

void GlobalLoad::LoadBowTexture()
{
	if (false == IsLoadBowTexutre)
	{
		IsLoadBowTexutre = true;

		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\PlayerElement\\Bow.png");
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateCut("Bow.png", 32, 32);
	}
}

void GlobalLoad::LoadArrowInBagTexture()
{
	if (false == IsLoadArrowInBagTexture)
	{
		IsLoadArrowInBagTexture = true;

		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\PlayerElement\\Arrow.png");
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateCut("Arrow.png", 32, 32);
	}
}

void GlobalLoad::LoadTestMapTexture()
{
	if (false == IsLoadTestMapTexture)
	{
		IsLoadTestMapTexture = true;

		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Map\\TestMap.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("TestMap.png");
	}
}