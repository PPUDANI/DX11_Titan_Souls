#include "PreCompile.h"
#include "TestMap.h"

TestMap::TestMap()
{
}

TestMap::~TestMap()
{
}

void TestMap::Start()
{
	GlobalLoad::MapLoad();
	MainRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Map);
	MainRenderer->SetSprite("TestMap.png");
	MainRenderer->SetImageScale(GlobalValue::WindowScale * 1.5f);
}

void TestMap::Update(float _Delta)
{

}