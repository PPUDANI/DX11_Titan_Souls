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
	PlaceCol = CreateComponent<GameEngineCollision>(COLLISION_TYPE::EnterPlace);
	PlaceCol->SetCollisionType(ColType::AABBBOX2D);
	PlaceCol->Transform.SetLocalScale({10.0f, 10.0f, 0.0f});
	PlaceCol->Transform.SetLocalPosition({0.0f, 0.0f, 0.0f});
}

void EnterPlace::Update(float _Delta)
{

}