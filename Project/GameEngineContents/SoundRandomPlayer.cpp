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
		MsgBoxAssert("사운드 리스트에 데이터가 없습니다.");
	}

	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomCount);

	SoundPlayer = GameEngineSound::SoundPlay(SoundList[Inst.RandomInt(0, static_cast<int>(SoundList.size()) - 1)]);
}
