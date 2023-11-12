#include "PreCompile.h"
#include "Yeti.h"

void Yeti::SleepStart()
{
	BodyRenderer->ChangeAnimation("Sleep");
}

void Yeti::IdleStart()
{
	SetAnimByDir("Idle");
}

void Yeti::ThrowingStart()
{
	ThrowCount = 0;
	SetAnimByDir("Throwing");
}

void Yeti::ReadyToRollStart()
{
	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();

	SetAnimByDir("ReadyToRoll");
}

void Yeti::RollingStart()
{
	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();

	BodyCollisionOff();
	RollingCollision->On();

	SetAnimByDir("Rolling");
}

void Yeti::LandingStart()
{
	LandingTimer = 0.0f;
	BodyCollisionOn();
	RollingCollision->Off();
	SetAnimByDir("Landing");
}

void Yeti::BlockedStart()
{
	ShakingEnd = false;
	ScreenShakingTime = 1.0f;
	ScreenShakingTimer = 0.0f;
	ShakingPerFrame = 0.25f;
	ShakingLerpValue = 10.0f;

	DirReflection();
	GravityValue = 600.0f;
	JumpStartPos = Transform.GetLocalPosition();
}

void Yeti::HitStart()
{
	switch (CurDir)
	{
	case YETI_DIRECTION::LeftDown:
	case YETI_DIRECTION::Down:
	case YETI_DIRECTION::RightDown:
		EnymeArrow->SetOrderToYSort();
		break;
	default:
		break;
	}
	BodyCollisionOff();
	SetAnimByDir("Hit");
}

void Yeti::DeathStart()
{
	//BodyRenderer->Transform.AddLocalPosition(-MoveDirBasis * 50.0f);
	SetAnimByDir("Death");
}



void Yeti::SleepUpdate(float _Delta)
{

}

void Yeti::IdleUpdate(float _Delta)
{
	IdleTimer += _Delta;

	if (IdleDelay < IdleTimer)
	{
		IdleTimer = 0.0f;
		ChangeState(NextStateBuffer);
		return;
	}

	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();

	SetAnimByDir("Idle", BodyRenderer->GetCurIndex());
}

void Yeti::ThrowingUpdate(float _Delta)
{
	if (BodyRenderer->IsCurAnimationEnd())
	{
		++ThrowCount;
		if (ThrowMaxCount == ThrowCount)
		{
			ChangeState(YETI_STATE::Idle);
			NextStateBuffer = YETI_STATE::ReadyToRoll;
			return;
		}

		SetMoveDir(Transform.GetLocalPosition());
		DirectionUpdate();

		SetAnimByDir("Throwing", 0, true);
	}
}

void Yeti::ReadyToRollUpdate(float _Delta)
{
	if (BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(YETI_STATE::Rolling);
		return;
	}
}

void Yeti::RollingUpdate(float _Delta)
{
	float4 MovePos = MoveDirBasis * RollingSpeed * _Delta;
	if (true == TileColCheck(MovePos))
	{
		ChangeState(YETI_STATE::Blocked);
		return;
	}
	else
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void Yeti::LandingUpdate(float _Delta)
{
	LandingTimer += _Delta;
	if (LandingDelay < LandingTimer)
	{
		LandingTimer = 0.0f;
		NextStateBuffer = YETI_STATE::Throwing;
		ChangeState(YETI_STATE::Idle);
		return;
	}
}

void Yeti::BlockedUpdate(float _Delta)
{
	GameEngineRandom Inst;
	static int Count = 0;

	if (false == ShakingEnd &&
		ScreenShakingTime > ScreenShakingTimer)
	{
		ScreenShakingTimer += _Delta;
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
		ShakingLerpValue = std::lerp(ShakingLerpValue, 0.0f, (1.0f / ShakingPerFrame) * _Delta);
		CameraManager::AddCameraPosFromBoss.X = Inst.RandomInt(-1, 1) * ShakingLerpValue;
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
		CameraManager::AddCameraPosFromBoss.Y = Inst.RandomInt(-1, 1) * ShakingLerpValue;
	}
	else
	{
		CameraManager::AddCameraPosFromBoss = float4::ZERO;
		ShakingEnd = true;
	}

	Gravity(_Delta);
	float4 MovePos = MoveDirBasis * RollingSpeed * DecreaseByBlocked * _Delta;
	Transform.AddLocalPosition(MovePos);
	JumpStartPos += MovePos;
}

void Yeti::HitUpdate(float _Delta)
{
	// 임시 코드
	if (ARROW_STATE::PickUp == EnymeArrow->GetCurState())
	{
		ChangeState(YETI_STATE::Death);
	}
}

void Yeti::DeathUpdate(float _Delta)
{

}

