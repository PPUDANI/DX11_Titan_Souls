#include "PreCompile.h"
#include "BossBase.h"

BossBase::BossBase()
{
}

BossBase::~BossBase()
{
}

void BossBase::Start()
{
}

void BossBase::Update(float _Delta)
{

}

void BossBase::SetMoveDir(const float4& _CheckPos)
{
	float4 BossToPlayer = EnymePlayer->Transform.GetLocalPosition() - _CheckPos;
	MoveAngle.Z = DirectX::XMConvertToDegrees(atan2f(BossToPlayer.Y, BossToPlayer.X));

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

float4 BossBase::SetMoveDirReturn(const float4& _CheckPos)
{
	float4 BossToPlayer = EnymePlayer->Transform.GetLocalPosition() - _CheckPos;
	float4 MoveAngleRes = float4::ZERO;
	MoveAngleRes.Z = DirectX::XMConvertToDegrees(atan2f(BossToPlayer.Y, BossToPlayer.X));

	if (0.0f > MoveAngleRes.Z)
	{
		while (0.0f > MoveAngleRes.Z)
		{
			MoveAngleRes.Z += 360.0f;
		}
	}
	else if (360.0f < MoveAngleRes.Z)
	{
		while (360.0f < MoveAngleRes.Z)
		{
			MoveAngleRes.Z -= 360.0f;
		}
	}

	return MoveAngleRes;
}

void BossBase::SetDirToDeg(float _Degree)
{
	MoveAngle.Z = _Degree;
	MoveDirBasis = float4::GetUnitVectorFromDeg(MoveAngle.Z);
}

void BossBase::ShakingScreen(float _Delta)
{
	GameEngineRandom Inst;
	ShakingSeedCount;

	if (false == ShakingEnd &&
		ScreenShakingTime > ScreenShakingTimer)
	{
		ScreenShakingTimer += _Delta;
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
		ShakingLerpValue = std::lerp(ShakingLerpValue, 0.0f, (1.0f / ShakingPerFrame) * _Delta);
		CameraManager::AddCameraPosFromShaking.X = Inst.RandomInt(-1, 1) * ShakingLerpValue;
		Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
		CameraManager::AddCameraPosFromShaking.Y = Inst.RandomInt(-1, 1) * ShakingLerpValue;
	}
	else
	{
		CameraManager::AddCameraPosFromShaking = float4::ZERO;
		ShakingEnd = true;
	}
}