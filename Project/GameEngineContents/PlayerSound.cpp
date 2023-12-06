#include "PreCompile.h"
#include "Player.h"

void Player::SoundLoad() 
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	// Stone Step

	size_t Index = GlobalValue::PlayerStoneStepList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::PlayerStoneStepList[i], "Resource\\Sound\\Player\\Step\\Stone\\");
	}

	Index = GlobalValue::PlayerGrassStepList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::PlayerGrassStepList[i], "Resource\\Sound\\Player\\Step\\Grass\\");
	}

	Index = GlobalValue::PlayerSnowStepList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::PlayerSnowStepList[i], "Resource\\Sound\\Player\\Step\\Snow\\");
	}

	// Roll
	GlobalLoad::LoadSound("Roll.ogg", "Resource\\Sound\\Player\\Roll\\");
	GlobalLoad::LoadSound("Roll_bash.ogg", "Resource\\Sound\\Player\\Roll\\");

	// Death
	GlobalLoad::LoadSound("Crush.ogg", "Resource\\Sound\\Player\\Death\\");

}


void Player::StepSoundPlay()
{
	if (2 != PrevStepInex &&
		2 == BodyRenderer->GetCurIndex())
	{
		PrevStepInex = 2;
	}
	else if (5 != PrevStepInex &&
		5 == BodyRenderer->GetCurIndex())
	{
		PrevStepInex = 5;
	}
	else
	{
		return;
	}

	TILE_MATERIAL_TYPE Type = CurMap->GetCurTileMatIndex(Transform.GetLocalPosition());

	switch (Type)
	{
	case TILE_MATERIAL_TYPE::Grass:
		GrassStepRandomPlayer.RandomPlay(0.5f);
		break;
	case TILE_MATERIAL_TYPE::Snow:
		SnowStepRandomPlayer.RandomPlay(0.5f);
		break;
	default:
		StoneStepRandomPlayer.RandomPlay(0.5f);
		break;
	}

	DustPatricle();
}