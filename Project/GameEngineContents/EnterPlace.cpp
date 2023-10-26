#include "PreCompile.h"
#include "EnterPlace.h"

EnterPlace::EnterPlace()
{
}

EnterPlace::~EnterPlace()
{
}

void EnterPlace::Start()
{
	EnterCol = CreateComponent<GameEngineCollision>(COLLISION_TYPE::EnterPlace);
	EnterCol->Transform.SetLocalScale({200.0f, 100.0f, 0.0f});
	EnterCol->Transform.SetLocalPosition({0.0f, 0.0f, 0.0f});
}

void EnterPlace::Update(float _Delta)
{

}