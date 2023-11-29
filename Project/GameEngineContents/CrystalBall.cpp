#include "PreCompile.h"
#include "CrystalBall.h"

CrystalBall::CrystalBall()
{
}

CrystalBall::~CrystalBall()
{
}

void CrystalBall::Start()
{
	GlobalLoad::LoadSpriteCut(2, 1, "Player.png", "Resource\\Texture\\PlayerElement\\");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
	BodyRenderer->SetSprite("Player.png", 777);
	BodyRenderer->SetImageScale(LightDefaultScale);

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::UI_BACK);
	LightRenderer->SetSprite("Player.png", 778);
	LightRenderer->SetImageScale(LightDefaultScale);
	
	LightRenderer->RenderBaseInfoValue.Target3 = 1;

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 28.0f, 28.0f, 1.0f });

	ChangeState(BALL_STATE::Idle);
}

void CrystalBall::Update(float _Delta)
{
	switch (CurState)
	{
	case BALL_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case BALL_STATE::Hit:
		HitUpdate(_Delta);
		break;
	case BALL_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}
}

void CrystalBall::ChangeState(BALL_STATE _State)
{
	CurState = _State;

	switch (CurState)
	{
	case BALL_STATE::Idle:
		IdleStart();
		break;
	case BALL_STATE::Hit:
		HitStart();
		break;
	case BALL_STATE::Death:
		DeathStart();
		break;
	default:
		break;
	}
}

void CrystalBall::IdleStart()
{
	LightAlphaRatio = 0.0f;
	AddAlphaDir = 1.0f;
}

void CrystalBall::HitStart()
{
	LightScaleRatio = 1.0f;
	LightAlphaRatio = 0.5f;
	LightRenderer->GetColorData().MulColor.A = LightAlphaRatio;
}

void CrystalBall::DeathStart()
{
	LightRenderer->Off();
}

void CrystalBall::IdleUpdate(float _Delta)
{
	if (true == IsBodyHitByArrow)
	{
		ChangeState(BALL_STATE::Hit);
		return;
	}

	if (0.5f < LightAlphaRatio)
	{
		AddAlphaDir = -1.0f;
	}

	if (0.0f > LightAlphaRatio)
	{
		AddAlphaDir = 1.0f;
	}

	LightAlphaRatio += AddAlphaDir * _Delta * 0.7f;
	LightRenderer->GetColorData().MulColor.A = LightAlphaRatio;
}


void CrystalBall::HitUpdate(float _Delta)
{
	LightScaleRatio = std::lerp(LightScaleRatio, 4.0f, _Delta * 5.0f);
	LightAlphaRatio -= _Delta * 0.4f;
	if (0.0f > LightAlphaRatio)
	{
		ChangeState(BALL_STATE::Death);
		return;
	}

	LightRenderer->GetColorData().MulColor.A = LightAlphaRatio;
	LightRenderer->SetImageScale(LightDefaultScale * LightScaleRatio);
}

void  CrystalBall::DeathUpdate(float _Delta)
{

}