#include "PreCompile.h"
#include "ColossusBody.h"

ColossusBody::ColossusBody()
{
}

ColossusBody::~ColossusBody()
{
}

void ColossusBody::Start()
{
	GlobalLoad::LoadSpriteSingle("ColossusBody.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteCut(5, 1, "ColossusHead.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteCut(2, 1, "ColossusShoulder.png", "Resource\\Texture\\Boss\\Colossus\\");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetSprite("ColossusBody.png");
	BodyRenderer->SetImageScale({ 192.0f, 192.0f, 1.0f });
	BodyRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });

	HeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	HeadRenderer->SetPivotType(PivotType::Bottom);
	HeadRenderer->SetSprite("ColossusHead.png", 0);
	HeadRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	HeadRenderer->Transform.SetLocalPosition({ 0.0f, 128.0f });

	HeadRenderer->CreateAnimation("Sleep", "ColossusHead.png", 1.0f, 0, 0, true);
	HeadRenderer->CreateAnimation("WakeUp", "ColossusHead.png", 0.1f, 0, 2, false);
	HeadRenderer->CreateAnimation("Idle", "ColossusHead.png", 1.0f, 2, 2, true);
	HeadRenderer->CreateAnimation("Angry", "ColossusHead.png", 1.0f, 3, 3, true);
	HeadRenderer->CreateAnimation("Death", "ColossusHead.png", 1.0f, 4, 4, true);


	LeftShoulderRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	LeftShoulderRenderer->SetPivotType(PivotType::Bottom);
	LeftShoulderRenderer->SetSprite("ColossusShoulder.png", 0);
	LeftShoulderRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	LeftShoulderRenderer->Transform.SetLocalPosition({ -96.0f, 64.0f });

	RightShoulderRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	RightShoulderRenderer->SetPivotType(PivotType::Bottom);
	RightShoulderRenderer->SetSprite("ColossusShoulder.png", 0);
	RightShoulderRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	RightShoulderRenderer->Transform.SetLocalPosition({ 96.0f, 64.0f });
}

void ColossusBody::Update(float _Delta)
{

}
