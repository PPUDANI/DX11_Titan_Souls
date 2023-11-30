#include "PreCompile.h"
#include "LevelBase.h"
#include "ContentsCore.h"
float LevelBase::BackgroundVolume = 0.5f;
float LevelBase::Background2Volume = 0.5f;
float LevelBase::AmbienceVolume = 1.0f;
float LevelBase::EffectVolume = 1.0f;

LevelBase::LevelBase()
{
}

LevelBase::~LevelBase()
{
}

void LevelBase::Start()
{
	GetMainCamera()->SetYSort(RENDERING_ORDER::Y_SORT_ENTITY);
	CursorActor = CreateActor<MouseCursor>(UPDATE_ORDER::UI);
	OffDebug();
	GameEngineInput::AddInputObject(this);
}

void LevelBase::Update(float _Delta)
{
	DeltaTime = _Delta;
	if (true == BackFadeInVolumeValue)
	{
		BackFadeInVolume(_Delta);
	}
	else if (true == BackFadeOutVolumeValue)
	{
		BackFadeOutVolume(_Delta);
	}

	if (true == AmbienceFadeInVolumeValue)
	{
		AmbienceFadeInVolume(_Delta);
	}
	else if (true == AmbienceFadeOutVolumeValue)
	{
		AmbienceFadeOutVolume(_Delta);
	}

	if (true == EffectFadeInVolumeValue)
	{
		EffectFadeInVolume(_Delta);
	}
	else if (true == EffectFadeOutVolumeValue)
	{
		EffectFadeOutVolume(_Delta);
	}

	if (true == GameEngineCore::MainWindow.IsFocus())
	{
		ContentsCore::CursorOff();
	}

}

void LevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void LevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{
	BackgroundPlayer.Stop();
	BackgroundPlayer2.Stop();
	AmbiencePlayer.Stop();
}

