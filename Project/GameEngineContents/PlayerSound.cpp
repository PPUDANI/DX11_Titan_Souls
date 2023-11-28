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
	GlobalLoad::LoadSound("Stone_Step1.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step2.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step3.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step4.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step5.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step6.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step7.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");
	GlobalLoad::LoadSound("Stone_Step8.ogg", "Resource\\Sound\\Player\\Step\\Stone\\");

    GlobalLoad::LoadSound("Grass_Step1.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step2.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step3.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step4.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step5.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step6.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step7.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");
    GlobalLoad::LoadSound("Grass_Step8.ogg", "Resource\\Sound\\Player\\Step\\Grass\\");

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
		break;
	case TILE_MATERIAL_TYPE::Vine:
		break;
	case TILE_MATERIAL_TYPE::Floor1Tile:
	case TILE_MATERIAL_TYPE::YetiRock:
	case TILE_MATERIAL_TYPE::SludgeTile:
	case TILE_MATERIAL_TYPE::Empty:
	default:
		StoneStepRandomPlayer.RandomPlay(0.5f);
		break;
	}

	DustPatricle();
}