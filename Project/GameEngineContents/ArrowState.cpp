#include "PreCompile.h"
#include "Arrow.h"


void Arrow::HoldStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->Off();
}

void Arrow::ZoomStart()
{
}

void Arrow::FlyingStart()
{

}

void Arrow::DropStart()
{

}

void Arrow::PickUpStart()
{
	Renderer->ChangeAnimation("Get");
}

void Arrow::HoldUpdate(float _Delta)
{

}

void Arrow::ZoomUpdate(float _Delta)
{

}

void Arrow::FlyingUpdate(float _Delta)
{

}

void Arrow::DropUpdate(float _Delta)
{

}

void Arrow::PickUpUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(ARROW_STATE::Hold);
	}
}