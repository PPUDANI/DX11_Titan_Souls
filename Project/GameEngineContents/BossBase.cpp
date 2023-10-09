#include "PreCompile.h"
#include "BossBase.h"

BossBase::BossBase()
{
}

BossBase::~BossBase()
{
}

void BossBase::Start()
{
	WeakPoint = CreateComponent<GameEngineCollision>(ColType::AABBBOX2D);
	BodyCollision = CreateComponent<GameEngineCollision>(ColType::AABBBOX2D);
}

void BossBase::Update(float _Delta)
{

}