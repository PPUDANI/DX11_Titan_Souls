#include "PreCompile.h"
#include "Yeti.h"
#include "YetiRoom.h"

void Yeti::SleepStart()
{
	BodyRenderer->ChangeAnimation("Sleep");
}

void Yeti::IdleStart()
{
	BodyCollisionOn();
	SetAnimByDir("Idle");
}

void Yeti::ThrowingStart()
{
	ThrowCount = 0;
	IsThrowing = false;
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
	RollPlayer.RandomPlay();

	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();

	BodyCollisionOff();
	RollingCollision->On();

	SetAnimByDir("Rolling");
}

void Yeti::LandingStart()
{
	LandPlayer.RandomPlay();
	ShakingScreenInit();

	LandingTimer = 0.0f;
	BodyCollisionOn();

	RollingCollision->Off();
	SetAnimByDir("Landing");

	ShadowRenderer->SetImageScale(ShadowStandardScale);
}

void Yeti::BlockedStart()
{
	RollPlayer.Stop();
	BlockedPlayer.RandomPlay();
	DropIcicle();
	ShakingScreenInit();
	DirReflection();
	GravityValue = 600.0f;
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

	BodyRenderer->GetColorData().MulColor = { 0.8f, 0.8f, 0.8f };
	Transform.SetLocalPosition(Transform.GetLocalPosition().RoundUpReturn());
	SetAnimByDir("Hit");
}

void Yeti::DeathStart()
{
	SetAnimByDir("Death");
	BodyCollisionOff();
	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
}

void Yeti::SleepUpdate(float _Delta)
{
	if (YETI_STATE::Sleep == CurState &&
		true == IsBodyHitByArrow)
	{
		WakeUpYeti();
	}
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
	if (false == IsThrowing &&
		1 == BodyRenderer->GetCurIndex())
	{
		ThrowSnowball();
		++ThrowCount;
		IsThrowing = true;
	}

	if (BodyRenderer->IsCurAnimationEnd())
	{
		IsThrowing = false;
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
	ShakingScreen(_Delta);

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
	ShakingScreen(_Delta);

	Gravity(_Delta);
	float4 MovePos = MoveDirBasis * RollingSpeed * DecreaseByBlocked * _Delta;
	Transform.AddLocalPosition(MovePos);
	JumpStartPos += MovePos;

	ShadowVariableByHeight(JumpStartPos);
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

