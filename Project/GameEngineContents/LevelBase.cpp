#include "PreCompile.h"
#include "LevelBase.h"

float LevelBase::BackgroundVolume = 1.0f;
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
	SetBackgroundVolume(0.5f);
	GetMainCamera()->SetYSort(RENDERING_ORDER::Y_SORT_ENTITY);
	CursorActor = CreateActor<MouseCursor>(UPDATE_ORDER::UI);
	OffDebug();
	GameEngineInput::AddInputObject(this);
}

void LevelBase::Update(float _Delta)
{
	if (true == FadeInVolume)
	{
		BackFadeInVolume(_Delta);
	}
	else if (true == FadeOutVolume)
	{
		BackFadeOutVolume(_Delta);
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

