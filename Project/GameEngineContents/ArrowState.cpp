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
	PullingForce = 0.0f;
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
	float4 Angle;
	Angle.Z = ArrowAngleDeg;
	Transform.SetWorldRotation(Angle);

	if (MaxPullingForce > PullingForce)
	{
		PullingForce += _Delta * PullingForceIncreaseSpeed;
	}

	float4 SpawnPos = ArrowOwnerPlayer->Transform.GetWorldPosition();
	SpawnPos += float4::GetUnitVectorFromDeg(ArrowAngleDeg - 90.0f) * (16.0f - PullingForce);
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