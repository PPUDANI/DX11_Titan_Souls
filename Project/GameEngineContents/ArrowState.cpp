#include "PreCompile.h"
#include "Arrow.h"


void Arrow::HoldStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->Off();
}

void Arrow::AimStart()
{
	Renderer->ChangeAnimation("Idle");

	PullingForce = 0.0f;

	ZoomValue = 1.0f;
	ZoomRatio = 1.0f;

	CameraMovePos = 1.0f;
	CameraMoveScale = 250.0f;
}

void Arrow::FlyingStart()
{
	Collision->On();
	OwnerPlayer->LostArrow();

	ZoomRatio = 1.0f - ZoomValue;
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

	ZoomValue = 1.0f;
	ZoomRatio = 0.8f;

	CameraMovePos = 1.0f;
	CameraMoveScale = 1.0f;
}

void Arrow::PickUpStart()
{
	Renderer->ChangeAnimation("Get");
	Collision->Off();
}

void Arrow::HoldUpdate(float _Delta)
{
	if (PLAYER_STATE::Aim == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Aim);
	}

	ContentsMath::Deceleration(PullingForce, 5.0f * _Delta);

	ZoomValue += PullingForce * 2.0f * _Delta;
	if (1.0f < ZoomValue)
	{
		ZoomValue = 1.0f;
	}

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetWorldPosition());
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
		if (1.2f > PullingForce)
		{
			ChangeState(ARROW_STATE::Hold);
			return;
		}

		ChangeState(ARROW_STATE::Flying);
		return;
	}


	FlyingDirectionBasis = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
	ContentsMath::Acceleration(PullingForce, _Delta * PullingForceIncreaseSpeed, MaxPullingForce);

	// Adjust the arrow position
	float4 SpawnPos = OwnerPlayer->Transform.GetLocalPosition();
	SpawnPos += FlyingDirectionBasis * (16.0f - PullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetLocalPosition(SpawnPos);

	// Adjust the arrow direction
	Transform.SetLocalRotation(ArrowAngleDeg);

	// Rendering on
	Renderer->On();

	// Calculating Zoom Ratio 
	if (0.8f < ZoomValue)
	{
		ContentsMath::Deceleration(ZoomRatio, 5.0f * _Delta);
		ZoomValue -= ZoomRatio * _Delta;
		GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);
	}

	// Calculating CameraMove
	ContentsMath::Deceleration(CameraMoveScale, 2.0f * _Delta);
	CameraMovePos += CameraMoveScale * _Delta;

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + FlyingDirectionBasis * CameraMovePos);
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
	
	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta;

	if (true == NextColCkeck(MovePos))
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}

	// Calculating Zoom Ratio 
	if (1.0f > ZoomValue)
	{
		ZoomValue += (PullingForce * 0.3f) * _Delta;

		if (1.0f < ZoomValue)
		{
			ZoomValue = 1.0f;
		}
	}
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);

	// Calculating CameraMove
	if (0.0f < CameraMovePos)
	{
		CameraMovePos -= (PullingForce * 180.0f) * _Delta;

		if (0.0f > CameraMovePos)
		{
			CameraMovePos = 0.0f;
		}
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + FlyingDirectionBasis * CameraMovePos);
}

void Arrow::FallenUpdate(float _Delta)
{
	if (PLAYER_STATE::Returning == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Returning);
	}

	if (true == Collision->Collision(COLLISION_TYPE::Player))
	{
		ChangeState(ARROW_STATE::PickUp);
		return;
	}

	// Calculating Zoom Ratio 
	if (1.0f > ZoomValue)
	{
		ZoomValue += 0.5f * _Delta;
	}

	if (1.0f < ZoomValue)
	{
		ZoomValue = 1.0f;
	}

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition());
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
		FlyingDirectionBasis = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
		Transform.SetLocalRotation(ArrowAngleDeg);
		Transform.AddLocalPosition(FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta);
		ContentsMath::Acceleration(PullingForce, 1.5f * _Delta, MaxPullingForce - 4.0f);

		ContentsMath::Deceleration(ZoomRatio, 3.0f * _Delta);

		if (0.8f < ZoomValue)
		{
			ZoomValue -= ZoomRatio * 0.5f *_Delta;
		}
	}
	else
	{
		AbleReturning = false;
		Transform.AddLocalPosition(FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta);
		ContentsMath::Deceleration(PullingForce, 5.0f * _Delta);
		if (0.1f > PullingForce)
		{
			ChangeState(ARROW_STATE::Fallen);
			return;
		}

		ZoomValue += 0.5f * _Delta;

		if (1.0f < ZoomValue)
		{
			ZoomValue = 1.0f; 
		}
	}
	
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition());
}

void Arrow::PickUpUpdate(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(ARROW_STATE::Hold);
		OwnerPlayer->GetArrow();
		return;
	}	

	ContentsMath::Deceleration(PullingForce, 5.0f * _Delta);

	ZoomValue += PullingForce * 2.0f * _Delta;
	if (1.0f < ZoomValue)
	{
		ZoomValue = 1.0f;
	}

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomValue);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetWorldPosition());
}

