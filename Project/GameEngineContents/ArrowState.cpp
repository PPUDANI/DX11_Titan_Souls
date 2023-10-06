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
	PullingForce = 0.0f;
	SubPullingForce = 0.0f;
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
	if (PLAYER_STATE::Aim == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Aim);
	}

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));

	ContentsMath::Deceleration(PullingForce, 8.0f * _Delta);
	if (1.0f != ZoomSacle)
	{
		if (1.0f > ZoomSacle)
		{
			GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
		}
		else if (0.95f < ZoomSacle)
		{
			GetLevel()->GetMainCamera()->SetZoomValue(1.0f);
		}
	}
}


void Arrow::AimUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_RBUTTON))
	{
		ChangeState(ARROW_STATE::Hold);
		PullingForce = SubPullingForce;
		return;
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON))
	{
		if (1.2f > SubPullingForce)
		{
			ChangeState(ARROW_STATE::Hold);
			PullingForce = SubPullingForce;
			return;
		}

		ChangeState(ARROW_STATE::Flying);
		PullingForce = SubPullingForce;
		return;
	}

	// Set Arrow Direction
	Transform.SetLocalRotation(ArrowAngleDeg);

	ContentsMath::Deceleration(PullingForce, PullingForceIncreaseSpeed * _Delta);

	if (MaxPullingForce > SubPullingForce)
	{
		SubPullingForce += _Delta * PullingForceIncreaseSpeed;
	}
	else if (MaxPullingForce < PullingForce)
	{
		SubPullingForce = MaxPullingForce;
	}

	FlyingDirection = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
	float4 SpawnPos = OwnerPlayer->Transform.GetLocalPosition();
	SpawnPos += FlyingDirection * (16.0f - SubPullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetLocalPosition(SpawnPos);
	Renderer->On();

	float ZoomSacle = 1.0f - (SubPullingForce / (MaxPullingForce * 5.0f));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + FlyingDirection * SubPullingForce * 10.0f);
}

void Arrow::FlyingUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_LBUTTON) &&
		0.3f > PullingForce)
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}

	if (0.0f == PullingForce)
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}

	ContentsMath::Deceleration(PullingForce, 7.0f * _Delta);
	
	Transform.AddLocalPosition(FlyingDirection * DefaultSpeed * PullingForce * _Delta);

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}

void Arrow::FallenUpdate(float _Delta)
{
	Collision->Off();
	if (PLAYER_STATE::Returning == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Returning);
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
		FlyingDirection = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
		Transform.SetLocalRotation(ArrowAngleDeg);
		Transform.AddLocalPosition(FlyingDirection * DefaultSpeed * PullingForce * _Delta);
		ContentsMath::Acceleration(PullingForce, 1.5f * _Delta, MaxPullingForce);
	}
	else
	{
		AbleReturning = false;
		Transform.AddLocalPosition(FlyingDirection * DefaultSpeed * PullingForce * _Delta);
		ContentsMath::Deceleration(PullingForce, 8.0f * _Delta);
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

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + FlyingDirection * PullingForce * 10.0f);
}

void Arrow::PickUpUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(ARROW_STATE::Hold);
		return;
	}	

	ContentsMath::Deceleration(PullingForce, 8.0f * _Delta);

	float ZoomSacle = 1.0f - (PullingForce / (MaxPullingForce * 5.0f));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomSacle);
}