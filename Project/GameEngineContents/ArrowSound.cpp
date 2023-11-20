#include "PreCompile.h"
#include "Arrow.h"

void Arrow::SoundLoad()
{
	if (true == SoundIsLoad)
	{
		return;
	}

	SoundIsLoad = true;

	GlobalLoad::LoadSound("arrow_charge.ogg", "Resource\\Sound\\Player\\Arrow\\");
	GlobalLoad::LoadSound("arrow_shoot.ogg", "Resource\\Sound\\Player\\Arrow\\");
	GlobalLoad::LoadSound("Pickuparrow.ogg", "Resource\\Sound\\Player\\Arrow\\");

}