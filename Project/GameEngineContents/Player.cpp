#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{

		GameEngineTexture::Load("힝", "응애");

		Renderer0 = CreateComponent<GameEngineSpriteRenderer>(0);

		// 자동으로 내부에서 트랜스폼을 이미지 크기로 변경까지 할것이다.
		Renderer0->SetSprite("NSet.png");

		/*Renderer0->Transform.SetLocalPosition({ 0, 150, 0 });
		Renderer0->Transform.SetLocalScale({ 50, 50, 100 });*/

		// Renderer0->SetSprite("NSet.png");

		// NewRender->SetSprite("AAA.png", 0);
		{
			//NewRender->SetConstnetbuffer("");
			//NewRender->SetTextureSetting("");
			//NewRender->SetTextureCurtingdataSetting("");
			//NewRender->SetConstnetResSetting("");
			//NewRender->SetConstnetResSetting("");
			//NewRender->SetConstnetResSetting("");
			//NewRender->SetConstnetResSetting("");
			//NewRender->SetConstnetResSetting("");
			//NewRender->SetConstnetResSetting("");

		}



	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ 0, -150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ -150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ 150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}
}

void Player::Update(float _Delta)
{
	float Speed = 100.0f;

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
}