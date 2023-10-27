#include "PreCompile.h"
#include "EventPlace.h"

EventPlace::EventPlace()
{
}

EventPlace::~EventPlace()
{
}

void EventPlace::Start()
{
	PlaceCol = CreateComponent<GameEngineCollision>(COLLISION_TYPE::EventPlace);
	PlaceCol->SetCollisionType(ColType::AABBBOX2D);
	PlaceCol->Transform.SetLocalScale({10.0f, 10.0f, 0.0f});
	PlaceCol->Transform.SetLocalPosition({0.0f, 0.0f, 0.0f});

	Param.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			PlayerEnterCheck = true;
			PlaceCol->Off();
		};
}

void EventPlace::Update(float _Delta)
{
	//PlaceCol->CollisionEvent(COLLISION_TYPE::Player, Param);
	if (false == PlaceCol->CollisionEvent(COLLISION_TYPE::Player, Param))
	{
		PlayerEnterCheck = false;
	}
}