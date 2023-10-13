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
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Boss);
}

void BossBase::Update(float _Delta)
{

}

void BossBase::SetMoveDir(float4& _CheckPos)
{
	float4 HeartAngle;
	float4 PlayerFromHeart = EnymePlayer->Transform.GetLocalPosition() - _CheckPos;
	HeartAngle.Z = DirectX::XMConvertToDegrees(atan2f(PlayerFromHeart.Y, PlayerFromHeart.X));

	if (0.0f > HeartAngle.Z)
	{
		while (0.0f > HeartAngle.Z)
		{
			HeartAngle.Z += 360.0f;
		}
	}
	else if (360.0f < HeartAngle.Z)
	{
		while (360.0f < HeartAngle.Z)
		{
			HeartAngle.Z -= 360.0f;
		}
	}

	MoveDirBasis = float4::GetUnitVectorFromDeg(HeartAngle.Z);
}