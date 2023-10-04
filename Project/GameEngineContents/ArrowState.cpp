#include "PreCompile.h"
#include "Arrow.h"


void Arrow::HoldStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->Off();
}

void Arrow::AimStart()
{
	Renderer->On();
	AimTime = 0.0f;
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

void Arrow::AimUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_RBUTTON) ||
		false == GameEngineInput::IsPress(VK_LBUTTON))
	{
		ChangeState(ARROW_STATE::Hold);
		return;
	}

	// Set Arrow Direction
	float4 Deg;
	Deg.Z = ArrowDegree;
	Transform.SetWorldRotation(Deg);

	float PullingForce = 16.0f;
	AimTime += _Delta;
	if (0.1f < AimTime)
	{
		PullingForce = 12.0f;
	}
	else if (0.2f < AimTime)
	{
		PullingForce = 8.0f;
	}

	float4 SpawnPos = ArrowOwnerPlayer->Transform.GetWorldPosition();
	SpawnPos += float4::GetUnitVectorFromDeg(ArrowDegree - 90.0f) * PullingForce;
	SpawnPos.Y -= 8.0f;
	Transform.SetWorldPosition(SpawnPos);
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