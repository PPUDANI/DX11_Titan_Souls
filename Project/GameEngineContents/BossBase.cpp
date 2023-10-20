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

void BossBase::SetMoveDir(float4& _CheckPos)
{
	float4 MoveAngle;
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