#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "Monster.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		// 줄줄이 사탕 식으로 만들려고.
		TestCollision = CreateComponent<GameEngineComponent>(30);
		TestCollision->Transform.SetLocalScale({ 30, 30, 1 });

		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
		MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
		/*MainSpriteRenderer->CreateAnimation("Run", "HoHoYee_AttackABC2", 0.05f, -1, -1, true);
		MainSpriteRenderer->ChangeAnimation("Run");
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

		MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));*/

		// MainSpriteRenderer->Transform.SetLocalScale({5, 5});
		// MainSpriteRenderer->AutoSpriteSizeOn();
		// MainSpriteRenderer->SetAutoScaleRatio(2.0f);
		MainSpriteRenderer->Transform.SetLocalScale({-100.0f, 100.0f, 1.0f});
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	//if (xxxx 상황이 되면)
	//{
	//	MainSpriteRenderer->Death();
	//	MainSpriteRenderer = nullptr;
	//}

	// 충돌했냐 안했냐만 보면

	std::list<std::shared_ptr<Monster>> MonsterList = 
		GetLevel()->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);

	for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	{
		// 랜더러로 하는 이유 => 액터로도 할수있는데
		// 보통 액터는 위치와 기준을 잡아주는 용도로 사용됩니다.
		// MainSpriteRenderer->Transform.Collision(MonsterPtr->Renderer->Transform);

		GameEngineTransform& Left = TestCollision->Transform;
		GameEngineTransform& Right = MonsterPtr->Renderer->Transform;
		Right.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });

		// 콜리전 파라미터를 사용한 이유가. 
		if (GameEngineTransform::Collision({ Left , Right, ColType::OBBBOX2D }))
		{
			MonsterPtr->Death();
			int a = 0;
			// 충돌했다.
		}
	}


	float Speed = 100.0f;

	if (GameEngineInput::IsDown('A'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}


	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	//if (GameEngineColor::RED != Color)
	//{
	//	GrivityForce.Y -= _Delta * 100.0f;
	//	Transform.AddLocalPosition(GrivityForce * _Delta);
	//}
	//else 
	//{
	//	GrivityForce = 0.0f;
	//}
	// 땅에 딱붙게하고 싶다면 while돌려서 올려주세요.


	// float4 Color = GetColor(Transform.GetWorldPosition());
}