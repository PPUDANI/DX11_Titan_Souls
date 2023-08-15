#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({0.0f, 0.0f, -500.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();

	// GetMainCamera()->SetParent(NewPlayer);
	// CreateActor<GameEngineRenderer>();
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}