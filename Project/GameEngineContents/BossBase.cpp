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
	if (ShakingFrame < FrameTimer)
	{
		if (false == ShakingEnd &&
			ScreenShakingTime > ScreenShakingTimer)
		{
			ScreenShakingTimer += FrameTimer;
			Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
			ShakingLerpValue = std::lerp(ShakingLerpValue, 0.0f, (1.0f / ShakingPerFrame) * FrameTimer);
			CameraManager::AddCameraPosFromShaking.X = Inst.RandomInt(-1, 1) * ShakingLerpValue;
			Inst.SetSeed(reinterpret_cast<__int64>(this) + ++ShakingSeedCount);
			CameraManager::AddCameraPosFromShaking.Y = Inst.RandomInt(-1, 1) * ShakingLerpValue;
		}
		else
		{
			CameraManager::AddCameraPosFromShaking = float4::ZERO;
			ShakingEnd = true;
		}

		FrameTimer -= ShakingFrame;
	}
	else
	{
		FrameTimer += _Delta;
	}
	
}

void BossBase::ShadowVariableByHeight(const float4& _JumpStartPos)
{
	float VariationRatio = std::abs(ShadowRenderer->Transform.GetLocalPosition().Y / _JumpStartPos.Y);
	ShadowRenderer->SetImageScale(ShadowStandardScale * (1.0f - (ShadowScaleConstant * VariationRatio)));
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha * (1.0f - (ShadowAlphaConstant * VariationRatio));
}
