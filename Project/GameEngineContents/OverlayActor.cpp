#include "PreCompile.h"
#include "OverlayActor.h"

OverlayActor::OverlayActor()
{
}

OverlayActor::~OverlayActor()
{
}

void OverlayActor::Start()
{
	GlobalLoad::LoadSpriteSingle("FadeTexture.png", "Resource\\Texture\\UI\\");
	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	FadeRenderer->SetPivotType(PivotType::Bottom);
	FadeRenderer->SetSprite("FadeTexture.png");
}

void OverlayActor::Update(float _Delta)
{

}