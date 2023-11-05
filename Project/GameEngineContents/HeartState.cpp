#include "PreCompile.h"
#include "Heart.h"
#include "Sludge.h"

void Heart::InSludgeStart()
{
	BodyRenderer->ChangeAnimation("InSludge");
	Collision->Off();
	ShadowRenderer->Off();
}

void Heart::IdleStart()
{
	BodyRenderer->ChangeAnimation("Idle");
	
	MoveSpeed = 250.0f;
}

void Heart::JumpStart()
{
	BodyRenderer->ChangeAnimation("Jump");
	JumpStartPos = Transform.GetLocalPosition();
	SetMoveDir(JumpStartPos);
	GravityValue = 300.0f;
}

void Heart::FallStart()
{
	Collision->Off();
	ShadowRenderer->On();
}

void Heart::LandingStart()
{
	BodyRenderer->ChangeAnimation("Landing");
	Collision->On();
}

void Heart::OutOfSludgeStart()
{
	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->ChangeAnimation("Jump", true, 1);
	AddMoveDirByArrow(-90.0f);
	JumpStartPos = Transform.GetLocalPosition();
	GravityValue = 500.0f;
	Collision->Off();
}

void Heart::DeathStart()
{
	BodyRenderer->ChangeAnimation("Death");
	Transform.SetLocalPosition(Transform.GetLocalPosition().RoundUpReturn());
}


void Heart::InSludgeUpdate(float _Delta)
{
	if (nullptr == OwnerSludge)
	{
		ChangeState(JUMPBOSS_STATE::Idle);
		return;
	}
}

void Heart::IdleUpdate(float _Delta)
{
	if (0.1f > JumpCooldown)
	{
		JumpCooldown += _Delta;
	}
	else
	{
		JumpCooldown = 0.0f;
		ChangeState(JUMPBOSS_STATE::Jump);
	}
}

void Heart::JumpUpdate(float _Delta)
{
	if (0.0f > GravityValue)
	{
		ChangeState(JUMPBOSS_STATE::Fall);
		return;
	}

	if (1 <= BodyRenderer->GetCurIndex())
	{
		Collision->Off();
		MoveToPlayer(_Delta);
		Gravity(_Delta);
	}
}

void Heart::FallUpdate(float _Delta)
{
	MoveToPlayer(_Delta);
	Gravity(_Delta);
}

void Heart::LandingUpdate(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(JUMPBOSS_STATE::Idle);
		return;
	}
}

void Heart::OutOfSludgeUpdate(float _Delta)
{
	if (0.0f > GravityValue)
	{
		ChangeState(JUMPBOSS_STATE::Fall);
		return;
	}

	MoveToPlayer(_Delta);
	Gravity(_Delta);
}

void Heart::DeathUpdate(float _Delta)
{

}

