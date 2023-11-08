#include "PreCompile.h"
#include "LevelBase.h"

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
	//std::string FPS;
	//FPS = std::to_string(static_cast<int>(1.0f / _Delta));
	//FPS += "\n";
	//OutputDebugStringA(FPS.c_str());
}

void LevelBase::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void LevelBase::LevelEnd(GameEngineLevel* _NextLevel)
{

}

