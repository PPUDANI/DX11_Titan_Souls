#include "PreCompile.h"
#include "TriggerBox.h"

TriggerBox::TriggerBox()
{
}

TriggerBox::~TriggerBox()
{
}

void TriggerBox::Start()
{
	PlaceCol = CreateComponent<GameEngineCollision>(COLLISION_TYPE::EventPlace);
	PlaceCol->SetCollisionType(ColType::AABBBOX2D);
	PlaceCol->Transform.SetLocalScale({10.0f, 10.0f, 0.0f});
	PlaceCol->Transform.SetLocalPosition({0.0f, 0.0f, 0.0f});

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			ColCheck = true;
		};
}

void TriggerBox::Update(float _Delta)
{
	if (true == ColCheck)
	{
		if (nullptr != TriggerFunc)
		{
			TriggerFunc();
		}
	}
	else
	{
		PlaceCol->CollisionEvent(COLLISION_TYPE::Player, Param);
	}
}