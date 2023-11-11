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
	SetAnimByDir("ReadyToRoll");
	SetMoveDir(Transform.GetLocalPosition());
	DirectionUpdate();
}

void Yeti::RollingStart()
{
	SetAnimByDir("Rolling");
}

void Yeti::LandingStart()
{
	SetAnimByDir("Landing");
}

void Yeti::BlockedStart()
{
	DirReflection();
	GravityValue = 600.0f;
	JumpStartPos = Transform.GetLocalPosition();
}

void Yeti::HitStart()
{
	SetAnimByDir("Hit");
}

void Yeti::DeathStart()
{
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
	SetAnimByDir("Landing", BodyRenderer->GetCurIndex());

	if (true == BodyRenderer->IsCurAnimationEnd()) 
	{
		NextStateBuffer = YETI_STATE::Throwing;
		ChangeState(YETI_STATE::Idle);
		return;
	}
}

void Yeti::BlockedUpdate(float _Delta)
{
	Gravity(_Delta);
	float4 MovePos = MoveDirBasis * RollingSpeed * DecreaseByBlocked * _Delta;
	Transform.AddLocalPosition(MovePos);
	JumpStartPos += MovePos;
}

void Yeti::HitUpdate(float _Delta)
{
	SetAnimByDir("Hit");
}

void Yeti::DeathUpdate(float _Delta)
{

}

