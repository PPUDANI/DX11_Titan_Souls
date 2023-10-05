#include "PreCompile.h"
#include "Arrow.h"


void Arrow::HoldStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->Off();
	Collision->Off();
}

void Arrow::AimStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->On();
	PullingForce = 0.0f;
}

void Arrow::FlyingStart()
{
	Collision->On();
	OwnerPlayer->LostArrow();
}

void Arrow::FallenStart()
{
	AbleReturning = true;

	Collision->On();
}

void Arrow::ReturningStart()
{
	Collision->On();
	PullingForce = 0.0f;
}

void Arrow::PickUpStart()
{
	OwnerPlayer->GetArrow();
	Renderer->ChangeAnimation("Get");
}

void Arrow::HoldUpdate(float _Delta)
{
	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 1.5f));

	if (1.0f > ZoomSacle)
	{
		GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
		Deceleration(10.0f * _Delta);
	}
	else if (0.95f < ZoomSacle)
	{
		GetLevel()->GetMainCamera()->SetZoomValue(1.0f);
	}
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
	Transform.SetLocalRotation(ArrowAngleDeg);

	if (MaxPullingForce > PullingForce)
	{
		PullingForce += _Delta * PullingForceIncreaseSpeed;
	}
	else if (MaxPullingForce < PullingForce)
	{
		PullingForce = MaxPullingForce;
	}

	FiyingDirection = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
	float4 SpawnPos = OwnerPlayer->Transform.GetLocalPosition();
	SpawnPos += FiyingDirection * (16.0f - PullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetLocalPosition(SpawnPos);

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::FlyingUpdate(float _Delta)
{
	if (0.0f == PullingForce)
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}

	if (2.0f > PullingForce)
	{
		Deceleration(8.0f * _Delta);
	}
	else
	{
		Deceleration(5.0f * _Delta);
	}
	
	Transform.AddLocalPosition(FiyingDirection * DefaultSpeed * PullingForce * _Delta);

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::FallenUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(ARROW_STATE::Returning);
		return;
	}

	if (true == Collision->Collision(COLLISION_TYPE::Player))
	{
		ChangeState(ARROW_STATE::PickUp);
		return;
	}
}

void Arrow::ReturningUpdate(float _Delta)
{
	if (true == Collision->Collision(COLLISION_TYPE::Player))
	{
		ChangeState(ARROW_STATE::PickUp);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LBUTTON) &&
		true == AbleReturning)
	{
		FiyingDirection = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
		Transform.SetLocalRotation(ArrowAngleDeg);
		Transform.AddLocalPosition(FiyingDirection * DefaultSpeed * PullingForce * _Delta);
		Acceleration(1.3f * _Delta);
	}
	else
	{
		AbleReturning = false;
		Transform.AddLocalPosition(FiyingDirection * DefaultSpeed * PullingForce * _Delta);
		Deceleration(8.0f * _Delta);
		if (0.0f == PullingForce)
		{
			ChangeState(ARROW_STATE::Fallen);
			return;
		}
	}
	
	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 1.5f));

	if (0.8f > ZoomSacle)
	{
		ZoomSacle = 0.8f;
	}

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::PickUpUpdate(float _Delta)
{
	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 1.5f));

	if (1.0f > ZoomSacle)
	{
		GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
		Deceleration(10.0f * _Delta);
	}
	else if (0.95f < ZoomSacle)
	{
		GetLevel()->GetMainCamera()->SetZoomValue(1.0f);
	}

	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(ARROW_STATE::Hold);
		return;
	}
}