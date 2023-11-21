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
			if (nullptr != EnterTriggerFunc)
			{
				EnterTriggerFunc();
			}
		};

	Param.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			if (nullptr != StayTriggerFunc)
			{
				StayTriggerFunc();
			}
		};

	Param.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			if (nullptr != ExitTriggerFunc)
			{
				ExitTriggerFunc();
			}
		};
}

void TriggerBox::Update(float _Delta)
{
	PlaceCol->CollisionEvent(COLLISION_TYPE::Player, Param);
}