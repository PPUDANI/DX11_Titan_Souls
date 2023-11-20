#include "PreCompile.h"
#include "Icicle.h"

bool Icicle::SoundIsLoaded = false;

void Icicle::FallingStart()
{
}

void Icicle::StuckStart()
{
	Transform.SetLocalPosition(TargetPos);
	ShadowRenderer->Transform.SetLocalPosition(ShadowStandardPos);

	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetPivotType(PivotType::Center);
	BodyRenderer->SetSprite("Icicle.png", StuckAnimationIndex);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });

	FallingCollision->Off();
	Collision->On();

	LiveTimer = 0.0f;

	LandPlayer.RandomPlay();
}


void Icicle::FallingUpdate(float _Delta)
{
	if (TargetPos.Y < Transform.GetLocalPosition().Y)
	{
		GravityValue -= GravityForce * _Delta;
		Height += float4{ 0.0f, GravityValue * _Delta };

		Transform.SetLocalPosition(TargetPos + Height);
		ShadowRenderer->Transform.SetLocalPosition(-Height + ShadowStandardPos);
		if (20.0f > abs(TargetPos.Y - Transform.GetLocalPosition().Y) )
		{	
			if (false == EnymePlayer->InvincibilityModeIsOn() &&
				true == FallingCollision->Collision(COLLISION_TYPE::Player))
			{
				EffectSoundPlay("Crush.ogg");
				EnymePlayer->ChangeState(PLAYER_STATE::Death);
			}
		}
	}
	else
	{
		ChangeState(ICICLE_STATE::Stuck);
	}

	ShadowVariableByHeight(TargetPos);
}

void Icicle::StuckUpdate(float _Delta)
{
	LiveTimer += _Delta;

	if (LiveTime < LiveTimer ||
		true == Collision->Collision(COLLISION_TYPE::BossBodyAttack) ||
		true == Collision->CollisionEvent(COLLISION_TYPE::Snowball, BlockedColParam))
	{
		//SmashPlayer.RandomPlay();
		Death();
	}
}

