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

void Arrow::ReturningStart()
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
	if (true == GameEngineInput::IsPress(VK_RBUTTON))
	{
		ChangeState(ARROW_STATE::Hold);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		if (0.8f > PullingForce)
		{
			ChangeState(ARROW_STATE::Hold);
			return;
		}

		ChangeState(ARROW_STATE::Flying);
		return;
	}

	// Set Arrow Direction
	Transform.SetWorldRotation(ArrowAngleDeg);

	if (MaxPullingForce > PullingForce)
	{
		PullingForce += _Delta * PullingForceIncreaseSpeed;
	}
	else if (MaxPullingForce < PullingForce)
	{
		PullingForce = MaxPullingForce;
	}

	FiyingDirection = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);

	float4 SpawnPos = OwnerPlayer->Transform.GetWorldPosition();
	SpawnPos += FiyingDirection * (16.0f - PullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetWorldPosition(SpawnPos);

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::FlyingUpdate(float _Delta)
{
	Transform.AddWorldPosition(FiyingDirection * DefaultSpeed * PullingForce * _Delta);

	if (2.0f > PullingForce)
	{
		Deceleration(5.0f * _Delta);
	}
	else
	{
		Deceleration(3.0f * _Delta);
	}
	
	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::DropUpdate(float _Delta)
{

}

void Arrow::ReturningUpdate(float _Delta)
{

}

void Arrow::PickUpUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(ARROW_STATE::Hold);
	}
}