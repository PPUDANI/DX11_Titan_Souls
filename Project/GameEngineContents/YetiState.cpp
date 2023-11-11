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
	SetAnimByDir("Throwing");
}

void Yeti::ReadyToRollStart()
{
	SetAnimByDir("Throwing");
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
		ChangeState(YETI_STATE::Throwing);
		return;
	}
	else
	{
		IdleTimer += _Delta;
		SetAnimByDir("Idle", BodyRenderer->GetCurIndex());
	}
}

void Yeti::ThrowingUpdate(float _Delta)
{
	SetAnimByDir("Throwing", BodyRenderer->GetCurIndex());
}

void Yeti::ReadyToRollUpdate(float _Delta)
{

}

void Yeti::RollingUpdate(float _Delta)
{
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

