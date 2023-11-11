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
	if (IdleDelay < IdleTimer)
	{
		IdleTimer = 0.0f;
		ChangeState(NextStateBuffer);
		return;
	}

	IdleTimer += _Delta;
	SetAnimByDir("Idle", BodyRenderer->GetCurIndex());
}

void Yeti::ThrowingUpdate(float _Delta)
{
	if (ThrowMaxCount == ThrowCount)
	{
		ChangeState(YETI_STATE::Idle);
		NextStateBuffer = YETI_STATE::ReadyToRoll;
		return;
	}

	if (BodyRenderer->IsCurAnimationEnd())
	{
		++ThrowCount;
		SetAnimByDir("Throwing", 0, true);
		return;
	}

	SetAnimByDir("Throwing", BodyRenderer->GetCurIndex());
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
	if (RollingDelay < RollingTimer)
	{
		RollingTimer = 0.0f;
		NextStateBuffer = YETI_STATE::Throwing;
		ChangeState(YETI_STATE::Idle);
		return;
	}

	RollingTimer += _Delta;
	SetAnimByDir("Rolling", BodyRenderer->GetCurIndex());
}

void Yeti::LandingUpdate(float _Delta)
{
	SetAnimByDir("Landing", BodyRenderer->GetCurIndex());
}

void Yeti::BlockedUpdate(float _Delta)
{
}

void Yeti::HitUpdate(float _Delta)
{
	SetAnimByDir("Hit");
}

void Yeti::DeathUpdate(float _Delta)
{

}

