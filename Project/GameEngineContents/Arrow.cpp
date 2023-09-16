#include "PreCompile.h"
#include "Arrow.h"

std::shared_ptr<Arrow> Arrow::MainArrow = nullptr;

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Arrow);
	Renderer->SetSprite("Player.png", 63);
	Renderer->SetImageScale(GlobalValue::StandardTextureScale);

	Renderer->CreateAnimation("Get", "PlayLevel.png", 0.05f, 189, 191, false);

}

void Arrow::Update(float _Delta)
{
	switch (CurState)
	{
	case ARROW_STATE::Hold:
		HoldUpdate(_Delta);
		break;
	case ARROW_STATE::Flying:
		FlyingUpdate(_Delta);
		break;
	case ARROW_STATE::Drop:
		DropUpdate(_Delta);
		break;
	default:
		break;
	}
}

