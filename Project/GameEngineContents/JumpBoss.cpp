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
	case JUMPBOSS_STATE::Division:
		DivisionUpdate(_Delta);
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
	case JUMPBOSS_STATE::Division:
		DivisionStart();
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
	float4 MovePos;

	MovePos = MoveDirBasis * MoveSpeed * _Delta;

	if (MoveSpeed / 50.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().X - JumpStartPos.X))
	{
		MovePos.X = 0.0f;
	}

	if (MoveSpeed / 50.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().Y - JumpStartPos.Y))
	{
		MovePos.Y = 0.0f;
	}

	JumpStartPos += MovePos;

	if (true == CurMap->AllColCheck(JumpStartPos))
	{
		AdjustPosByTileCol();
	}

	Transform.AddLocalPosition(MovePos);
	
}

void JumpBoss::AdjustPosByTileCol()
{
	while (true == CurMap->AllColCheck(JumpStartPos))
	{
		JumpStartPos -= MoveDirBasis;
	}
}

void JumpBoss::SetMoveDirRandom(float4& _CheckPos, float _RandomRange)
{
	float4 BossToPlayer = EnymePlayer->Transform.GetLocalPosition() - _CheckPos;
	MoveAngle.Z = DirectX::XMConvertToDegrees(atan2f(BossToPlayer.Y, BossToPlayer.X));
	GameEngineRandom Inst;
	MoveAngle.Z += Inst.RandomFloat(-_RandomRange, _RandomRange);

	if (0.0f > MoveAngle.Z)
	{
		while (0.0f > MoveAngle.Z)
		{
			MoveAngle.Z += 360.0f;
		}
	}
	else if (360.0f < MoveAngle.Z)
	{
		while (360.0f < MoveAngle.Z)
		{
			MoveAngle.Z -= 360.0f;
		}
	}

	MoveDirBasis = float4::GetUnitVectorFromDeg(MoveAngle.Z);
}

