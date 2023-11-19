#include "PreCompile.h"
#include "SoundRandomPlayer.h"

SoundRandomPlayer::SoundRandomPlayer()
{
}

SoundRandomPlayer::~SoundRandomPlayer()
{
}

void SoundRandomPlayer::RandomPlay()
{
	if (true == SoundList.empty())
	{
		return;
	}

	if (-1 > RandomCount)
	{
		RandomCount = 0;
	}

	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomCount);

 	SoundPlayer = GameEngineSound::SoundPlay(SoundList[Inst.RandomInt(0, static_cast<int>(SoundList.size()) - 1)]);
	SoundPlayer.SetVolume(LevelBase::GetEffectVolume());
}
