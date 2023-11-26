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

void BossBase::SetMoveDir(const float4& _CheckPos, const float4& EndPos)
{
	float4 BossToPlayer = EndPos - _CheckPos;
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

void BossBase::ShadowVariableByHeightUpdate(const float4& _JumpStartPos)
{
	float VariationRatio = std::abs(ShadowRenderer->Transform.GetLocalPosition().Y / _JumpStartPos.Y);
	ShadowRenderer->SetImageScale(ShadowStandardScale * (1.0f - (ShadowScaleConstant * VariationRatio)));
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha * (1.0f - (ShadowAlphaConstant * VariationRatio));
}

void BossBase::ShadowAlphaByHeightUpdate(const float4& _JumpStartPos)
{
	float VariationRatio = std::abs(ShadowRenderer->Transform.GetLocalPosition().Y / _JumpStartPos.Y);
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha * (1.0f - (ShadowAlphaConstant * VariationRatio));
}