#include "PreCompile.h"
#include "Arrow.h"


void Arrow::HoldStart()
{
	PullingForce = 0.0f;
	Renderer->ChangeAnimation("Idle");
	Renderer->Off();
	Collision->Off();
	PickUpCollision->Off();
}

void Arrow::AimStart()
{
	Renderer->ChangeAnimation("Idle");
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
	PickUpCollision->On();
	AbleReturning = true;
}

void Arrow::ReturningStart()
{
	Collision->On();
	PullingForce = 0.0f;
}

void Arrow::PickUpStart()
{
	Renderer->ChangeAnimation("Get");
	Collision->Off();
	PickUpCollision->Off();
}

void Arrow::PinnedStart()
{
	Renderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
	Renderer->ChangeAnimation("Pinned");
	Collision->Off();
	PickUpCollision->Off();
	PinnedRotationDir = Transform.GetLocalRotationEuler().Z;

	ShakingPerFrame = 0.0f;
	//Renderer->Transform.SetLocalPosition(DepthValue::PinnedArrow);
}

void Arrow::HoldUpdate(float _Delta)
{
	if (PLAYER_STATE::Aim == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Aim);
	}

	Transform.SetLocalPosition(OwnerPlayer->Transform.GetLocalPosition());

	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);
	CameraManager::AddCameraZoomFromArrow = ZoomRatio;

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 10.0f * _Delta);
	CameraManager::AddCameraPosFromArrow = CameraMoveDirectionBasis * CameraMovePos;
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
	PullingForce = std::lerp(PullingForce, 1.0f, 3.0f * _Delta);

	// Adjust the arrow position
	float4 SpawnPos = OwnerPlayer->Transform.GetLocalPosition();
	SpawnPos += FlyingDirectionBasis * (28.0f - 16.0f * PullingForce);
	SpawnPos.Y -= 8.0f;
	Transform.SetLocalPosition(SpawnPos);

	// Adjust the arrow direction
	Transform.SetLocalRotation(ArrowAngleDeg);

	// Rendering on
	Renderer->On();

	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 0.8f, 2.0f * _Delta);
	CameraManager::AddCameraZoomFromArrow = ZoomRatio;

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 120.0f, 5.0f * _Delta);
	CameraManager::AddCameraPosFromArrow = FlyingDirectionBasis * CameraMovePos;
}

void Arrow::FlyingUpdate(float _Delta)
{
	if (0.2f > PullingForce)
	{
		ChangeState(ARROW_STATE::Fallen);
		return;
	}

	PullingForce = std::lerp(PullingForce, 0.0f, 3.0f * _Delta);

	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * std::powf(PullingForce, 2) * _Delta;
	MoveAndColCheck(MovePos);

	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);
	CameraManager::AddCameraZoomFromArrow = ZoomRatio;

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 10.0f * _Delta);
	CameraManager::AddCameraPosFromArrow = CameraMoveDirectionBasis * CameraMovePos;
}


void Arrow::FallenUpdate(float _Delta)
{
	if (PLAYER_STATE::Returning == OwnerPlayer->GetCurState())
	{
		ChangeState(ARROW_STATE::Returning);
		return;
	}

	PullingForce = std::lerp(PullingForce, 0.0f, 5.0f * _Delta);

	if (0.05f > PullingForce)
	{
		Collision->Off();
	}
	else
	{
		Collision->On();
	}

	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * std::powf(PullingForce, 2) * _Delta;
	MoveAndColCheck(MovePos);

	// Calculating Zoom Ratio 
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);
	CameraManager::AddCameraZoomFromArrow = ZoomRatio;

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 10.0f * _Delta);
	CameraManager::AddCameraPosFromArrow = CameraMoveDirectionBasis * CameraMovePos;
}


void Arrow::ReturningUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_LBUTTON, this) &&
		true == AbleReturning)
	{
		FlyingDirectionBasis = float4::GetUnitVectorFromDeg(ArrowAngleDeg.Z - 90.0f);
		Transform.SetLocalRotation(ArrowAngleDeg);
		PullingForce = std::lerp(PullingForce, 0.7f, 2.0f * _Delta);
		ZoomRatio = std::lerp(ZoomRatio, 0.8f, 2.0f * _Delta);
	}
	else
	{
		AbleReturning = false;
		PullingForce = std::lerp(PullingForce, 0.0f, 5.0f * _Delta);
		ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);

		if (0.1f > PullingForce)
		{
			ChangeState(ARROW_STATE::Fallen);
			return;
		}
	}

	float4 MovePos = FlyingDirectionBasis * DefaultSpeed * std::powf(PullingForce, 2) * _Delta;
	MoveAndColCheck(MovePos);

	CameraManager::AddCameraZoomFromArrow = ZoomRatio;
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
	ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);
	CameraManager::AddCameraZoomFromArrow = ZoomRatio;
}


void Arrow::PinnedUpdate(float _Delta)
{
	GameEngineRandom Inst;
	static int Count = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
	AddRange = Inst.RandomFloat(-2.0f, 2.0f) * DirRangeValue;


	float4 Degree = float4::ZERO;
	Degree.Z = PinnedRotationDir + AddRange;
	Transform.SetLocalRotation(Degree);

	if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		if (PullOutDuration < PullOutTimer)
		{
			PullOutTimer = 0.0f;
			ChangeState(ARROW_STATE::PickUp);
		}

		PullOutTimer += _Delta;
		ZoomRatio = std::lerp(ZoomRatio, 0.8f, 1.0f * _Delta);
	}
	else
	{
		PullOutTimer = 0.0f;
		ZoomRatio = std::lerp(ZoomRatio, 1.0f, 10.0f * _Delta);
	}

	CameraManager::AddCameraZoomFromArrow = ZoomRatio;

	// Calculating CameraMove
	CameraMovePos = std::lerp(CameraMovePos, 0.0f, 10.0f * _Delta);
	CameraManager::AddCameraPosFromArrow = CameraMoveDirectionBasis * CameraMovePos;
}