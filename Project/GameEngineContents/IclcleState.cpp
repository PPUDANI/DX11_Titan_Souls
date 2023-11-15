#include "PreCompile.h"
#include "Icicle.h"

void Icicle::FallingStart()
{
}

void Icicle::StuckStart()
{
	Transform.SetLocalPosition(TargetPos);

	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetPivotType(PivotType::Center);
	BodyRenderer->SetSprite("Icicle.png", StuckAnimationIndex);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });

	FallingCollision->Off();
	Collision->On();

}


void Icicle::FallingUpdate(float _Delta)
{
	if (TargetPos.Y < Transform.GetLocalPosition().Y)
	{
		GravityValue -= GravityForce * _Delta;
		Transform.AddLocalPosition({ 0.0f, GravityValue * _Delta });

		if (20.0f > abs(TargetPos.Y - Transform.GetLocalPosition().Y) )
		{	
			if (false == EnymePlayer->InvincibilityModeIsOn() &&
				true == FallingCollision->Collision(COLLISION_TYPE::Player))
			{
				EnymePlayer->ChangeState(PLAYER_STATE::Death);
			}
		}
	}
	else
	{
		ChangeState(ICICLE_STATE::Stuck);
	}
}

void Icicle::StuckUpdate(float _Delta)
{

	Collision->CollisionEvent(COLLISION_TYPE::Snowball, BlockedColParam);
	if (true == Collision->Collision(COLLISION_TYPE::BossBodyAttack))
	{
		Death();
	}
}
