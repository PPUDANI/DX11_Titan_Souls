#include "PreCompile.h" 
#include "JumpBoss.h"

JumpBoss::JumpBoss()
{
}

JumpBoss::~JumpBoss()
{
}

void JumpBoss::Start()
{
	BossBase::Start();
}

void JumpBoss::Update(float _Delta)
{
	BossBase::Update(_Delta);

	switch (CurState)
	{
	case JUMPBOSS_STATE::InSludge:
		InSludgeUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Jump:
		JumpUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Fall:
		FallUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Landing:
		LandingUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}

	RendererSetting();

	if (true == GetLevel()->IsDebug)
	{
		GameEngineTransform TData;
		TData.SetLocalRotation(Transform.GetLocalRotationEuler());
		TData.SetLocalScale({ 5.0f, 5.0f });
		TData.SetLocalPosition(JumpStartPos + GlobalValue::DebugDepth);
		GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	}
}

void JumpBoss::ChangeState(JUMPBOSS_STATE _State)
{
	if (CurState == _State)
	{
		return;
	}

	CurState = _State;

	switch (CurState)
	{
	case JUMPBOSS_STATE::InSludge:
		InSludgeStart();
		break;
	case JUMPBOSS_STATE::Idle:
		IdleStart();
		break;
	case JUMPBOSS_STATE::Jump:
		JumpStart();
		break;
	case JUMPBOSS_STATE::Fall:
		FallStart();
		break;
	case JUMPBOSS_STATE::Landing:
		LandingStart();
		break;
	case JUMPBOSS_STATE::Death:
		DeathStart();
		break;

	default:
		break;
	}
}

void JumpBoss::Gravity(float _Delta)
{
	if (JumpStartPos.Y > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = JumpStartPos.Y;
		Transform.SetLocalPosition(MovePos);

		ChangeState(JUMPBOSS_STATE::Landing);
		return;
	}

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);
}


void JumpBoss::MoveToPlayer(float _Delta)
{
	float4 MovePos = MoveDirBasis * MoveSpeed * _Delta;

	if (MoveSpeed / 50.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().X - JumpStartPos.X))
	{
		MovePos.X = 0.0f;
	}

	if (MoveSpeed / 50.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().Y - JumpStartPos.Y))
	{
		MovePos.Y = 0.0f;
	}

	Transform.AddLocalPosition(MovePos);
	JumpStartPos += MovePos;
}

