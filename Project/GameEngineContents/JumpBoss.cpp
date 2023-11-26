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
	case JUMPBOSS_STATE::OutOfSludge:
		OutOfSludgeUpdate(_Delta);
		break;
	case JUMPBOSS_STATE::Hit:
		HitUpdate(_Delta);
	case JUMPBOSS_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}

	if (true == GetLevel()->IsDebug)
	{
		GameEngineTransform TData;
		TData.SetLocalRotation(Transform.GetLocalRotationEuler());
		TData.SetLocalScale({ 5.0f, 5.0f });

		TData.SetLocalPosition(JumpStartPos);
		GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

		TData.SetLocalPosition(LeftPos);
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(RightPos);
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(UpPos);
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });

		TData.SetLocalPosition(DownPos);
		GameEngineDebug::DrawBox2D(TData, { 1, 1, 0, 1 });
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
	case JUMPBOSS_STATE::OutOfSludge:
		OutOfSludgeStart();
		break;
	case JUMPBOSS_STATE::Hit:
		HitStart();
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
	float4 StartPosToPlayer = EnymePlayer->Transform.GetLocalPosition() - JumpStartPos;
	float LengthStartPosToPlayer = DirectX::XMVectorGetX(DirectX::XMVector2Length(StartPosToPlayer.DirectXVector));

	if (10.0f > LengthStartPosToPlayer)
	{
		MovePos = float4::ZERO;
	}

	TileColCheck(MovePos);
	
	JumpStartPos += MovePos;
	Transform.AddLocalPosition(MovePos);
}

void JumpBoss::PosUpdate()
{
	LeftPos = JumpStartPos - float4{ ColPosInterval.hX(), 0.0f};
	RightPos = JumpStartPos + float4{ ColPosInterval.hX(), 0.0f };
	UpPos = JumpStartPos + float4{ 0.0f, ColPosInterval.hY() };
	DownPos = JumpStartPos - float4{ 0.0f, ColPosInterval.hY() };
}

void JumpBoss::TileColCheck(float4& _MovePos)
{
	PosUpdate();
	TILE_COLLISION_TYPE Type = TILE_COLLISION_TYPE::EMPTY;

	if (true == CurMap->ColCheck(LeftPos, Type))
	{
		AdjustLeftPosByTileCol(_MovePos);
	}

	if (true == CurMap->ColCheck(RightPos, Type))
	{
		AdjustRightPosByTileCol(_MovePos);
	}

	if (true == CurMap->ColCheck(UpPos, Type))
	{
		AdjustUpPosByTileCol(_MovePos);
	}

	if (true == CurMap->ColCheck(DownPos, Type))
	{
		AdjustDownPosByTileCol(_MovePos);
	}
}

void JumpBoss::AdjustLeftPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(LeftPos + _MovePos))
	{
		_MovePos += float4::RIGHT;
	}
	_MovePos += float4::LEFT;
}

void JumpBoss::AdjustRightPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(RightPos + _MovePos))
	{
		_MovePos += float4::LEFT;
	}
	_MovePos += float4::RIGHT;
}

void JumpBoss::AdjustUpPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(UpPos + _MovePos))
	{
		_MovePos += float4::DOWN;
	}
	_MovePos += float4::UP;
}

void JumpBoss::AdjustDownPosByTileCol(float4& _MovePos)
{
	while (true == CurMap->AllColCheck(DownPos + _MovePos))
	{
		_MovePos += float4::UP;
	}
	_MovePos += float4::DOWN;
}

void JumpBoss::SetMoveDirRandom(const float4& _CheckPos, float _RandomRange)
{
	float4 BossToPlayer = EnymePlayer->Transform.GetLocalPosition() - _CheckPos;
	MoveAngle.Z = DirectX::XMConvertToDegrees(atan2f(BossToPlayer.Y, BossToPlayer.X));
	GameEngineRandom Inst;
	static int RandomCount = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomCount);

	
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

void JumpBoss::AddMoveDirByArrow(float _AddPos)
{
	float4 ArrowAngle = EnymeArrow->GetArrowAngleDeg();
	ArrowAngle.Z -= 90.0f;
	GameEngineRandom Inst;
	int Count = 0;
	Inst.SetSeed(reinterpret_cast<__int64>(this) + ++Count);
	float AddPos = Inst.RandomFloat(_AddPos - 15.0f, _AddPos + 15.0f);
	ArrowAngle.Z += AddPos;

	if (0.0f > ArrowAngle.Z)
	{
		while (0.0f > ArrowAngle.Z)
		{
			ArrowAngle.Z += 360.0f;
		}
	}
	else if (360.0f < ArrowAngle.Z)
	{
		while (360.0f < ArrowAngle.Z)
		{
			ArrowAngle.Z -= 360.0f;
		}
	}
	
	MoveDirBasis = float4::GetUnitVectorFromDeg(ArrowAngle.Z);
}

