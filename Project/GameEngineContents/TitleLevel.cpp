#include "PreCompile.h"
#include "TitleLevel.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -100.0f}); // z가 음수여야 다 보임.
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void TitleLevel::Update(float _Delta)
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}
