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
	ZoomRatio = 1.0f;
	CameraMovePos = 0.0f;
}

void Arrow::FlyingStart()
{
	FiyTimer = 0.0f;
	Collision->On();
	OwnerPlayer->LostArrow();
	CameraMoveDirectionBasis = FlyingDirectionBasis;
}

void Arrow::FallenStart()
{
	AbleReturning = true;
}

void Arrow::ReturningStart()
{
	PullingForce = 0.0f;
}

void Arrow::PickUpStart()
{
	Renderer->ChangeAnimation("Get"); 
	Collision->Off();
}

void Arrow::PinnedStart()
{
	Renderer->ChangeAnimation("Pinned");
	Collision->Off();
	PinnedRotationDir = Transform.GetLocalRotationEuler().Z;

	MaxDegree = PinnedRotationDir + (DirRange / 2);
	MinDegree = PinnedRotationDir - (DirRange / 2);

	Renderer->Transform.SetLocalPosition(DepthValue::Arrow);
}

void Arrow::HoldUpdate(float _Delta)
{
	if (PLAYER_STATE::Aim == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Aim);
	}

	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.5f, 10.0f * _Delta));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetWorldPosition());
}


void Arrow::AimUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		ChangeState(ARROW_STATE::Hold);
		return;
	}

	if (true == GameEngineInput::IsUp(VK_LBUTTON, this))
	{
		if (0.3f > PullingForce)
		{
			ChangeState(ARROW_STATE::Hold);
			return;
		}

		ChangeState(ARROW_STATE::Flying);
		return;
	}

	FlyingDirectionBasis = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
	PullingForce = std::lerp(PullingForce, 1.0f, 1.0f - std::pow(0.5f, 5.0f * _Delta));

	// Adjust the arrow position
	float4 SpawnPos = OwnerPlayer->Transform.GetLocalPosition();
	SpawnPos += FlyingDirectionBasis * (27.0f - 15.0f * PullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetLocalPosition(SpawnPos);

	// Adjust the arrow direction
	Transform.SetLocalRotation(ArrowAngleDeg);

	// Rendering on
	Renderer->On();

	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 0.8f, 1.0f - std::pow(0.5f, 5.0f * _Delta));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 120.0f, 1.0f - std::pow(0.5f, 5.0f * _Delta));
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + FlyingDirectionBasis * CameraMovePos);
}

void Arrow::FlyingUpdate(float _Delta)
{
	if (0.05f > PullingForce)
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}

	PullingForce = std::lerp(PullingForce, 0.0f, 1.0f - std::pow(0.5f, 7.0f * _Delta));

	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta;
	MoveAndColCheck(MovePos);

	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.5f, 20.0f * _Delta));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 1.0f - std::pow(0.5f, 20.0f * _Delta));
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + CameraMoveDirectionBasis * CameraMovePos);
}


void Arrow::FallenUpdate(float _Delta)
{
	if(PLAYER_STATE::Returning == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Returning);
		return;
	}

	PullingForce = std::lerp(PullingForce, 0.0f, 1.0f - std::pow(0.5f, 5.0f * _Delta));
	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta;
	MoveAndColCheck(MovePos);
	
	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.5f, 10.0f * _Delta));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 1.0f - std::pow(0.5f, 10.0f * _Delta));
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition() + CameraMoveDirectionBasis * CameraMovePos);
}


void Arrow::ReturningUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_LBUTTON, this) &&
		true == AbleReturning)
	{
		FlyingDirectionBasis = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
		Transform.SetLocalRotation(ArrowAngleDeg);
		PullingForce = std::lerp(PullingForce, 0.5f, 1.0f - std::pow(0.01f, 0.2f * _Delta));
		ZoomRatio = std::lerp(ZoomRatio, 0.8f, 1.0f - std::pow(0.01f, 0.2f * _Delta));
	}
	else
	{
		AbleReturning = false;
		PullingForce = std::lerp(PullingForce, 0.0f, 1.0f - std::pow(0.01f, 3.0f * _Delta));
		ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.01f, 0.2f * _Delta));

		if (0.1f > PullingForce)
		{
			ChangeState(ARROW_STATE::Fallen);
			return;
		}
	}

	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * PullingForce * _Delta;
	MoveAndColCheck(MovePos);

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);
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
	IsBlocked = false;
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.5f, 10.0f * _Delta));
	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetWorldPosition());
}


void Arrow::PinnedUpdate(float _Delta)
{
	if (false == RotationReverse)
	{
		PinnedRotationDir += PinnedRotationSpeed * _Delta;
		if (MaxDegree < PinnedRotationDir)
		{
			RotationReverse = true;
		}
	}
	else
	{
		PinnedRotationDir -= PinnedRotationSpeed * _Delta;
		if (MinDegree > PinnedRotationDir)
		{
			RotationReverse = false;
		}
	}

	float4 Degree = float4::ZERO;
	Degree.Z = PinnedRotationDir;
	Transform.SetLocalRotation(Degree);

	if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		if (PullOutDuration < PullOutTimer)
		{
			PullOutTimer = 0.0f;
			ChangeState(ARROW_STATE::PickUp);
		}

		PullOutTimer += _Delta;
		ZoomRatio = std::lerp(ZoomRatio, 0.8f, 1.0f - std::pow(0.01f, 0.2f * _Delta));
	}
	else
	{
		PullOutTimer = 0.0f;
		ZoomRatio = std::lerp(ZoomRatio, 1.0f, 1.0f - std::pow(0.01f, 0.2f * _Delta));
	}

	GetLevel()->GetMainCamera()->SetZoomValue(ZoomRatio);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition());

}