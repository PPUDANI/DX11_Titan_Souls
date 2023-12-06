#include "PreCompile.h"
#include "Icicle.h"

bool Icicle::SoundIsLoaded = false;

void Icicle::FallingStart()
{
}

void Icicle::StuckStart()
{
	Transform.SetLocalPosition(TargetPos);
	float4 PivotSetting = { 0.0f, 16.0f };
	ShadowRenderer->Transform.SetLocalPosition(ShadowStandardPos + PivotSetting);

	BodyRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetSprite("Icicle.png", StuckAnimationIndex);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });
	BodyRenderer->Transform.AddLocalPosition(PivotSetting);
	FallingCollision->Off();
	Collision->On();

	LiveTimer = 0.0f;

	LandPlayer.RandomPlay();

	IclcleParticle();
}


void Icicle::FallingUpdate(float _Delta)
{
	if (TargetPos.Y < Transform.GetLocalPosition().Y)
	{
		GravityValue -= GravityForce * _Delta;
		Height += float4{ 0.0f, GravityValue * _Delta };

		Transform.SetLocalPosition(TargetPos + Height);
		ShadowRenderer->Transform.SetLocalPosition(-Height + ShadowStandardPos);
		if (50.0f > abs(TargetPos.Y - Transform.GetLocalPosition().Y) )
		{	
			FallingCollision->On();
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

	ShadowVariableByHeightUpdate(TargetPos);
}

void Icicle::StuckUpdate(float _Delta)
{
	LiveTimer += _Delta;

	if (LiveTime < LiveTimer ||
		true == Collision->Collision(COLLISION_TYPE::BossBodyAttack))
	{
		LandPlayer.RandomPlay();
		IclcleParticle();
		Death();
	}
	else if (true == Collision->CollisionEvent(COLLISION_TYPE::Snowball, BlockedColParam))
	{
		EffectSoundPlay("Impact.ogg");
		IclcleParticle();
		SnowSpreadParticle();
		Death();
	}
}

