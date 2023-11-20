#include "PreCompile.h"
#include "Icicle.h"

SoundRandomPlayer Icicle::LandPlayer(GlobalValue::IcicleLandList);
SoundRandomPlayer Icicle::SmashPlayer(GlobalValue::IcicleSmashList);

Icicle::Icicle()
{

}

Icicle::~Icicle()
{

}

void Icicle::Init(const float4& _TargetPos, const float4& _Height)
{
	TargetPos = _TargetPos.RoundUpReturn();
	Height = _Height;

	Transform.SetLocalPosition(TargetPos + Height);
}

void Icicle::Start()
{
	GlobalLoad::LoadSpriteCut(8, 1, "Icicle.png", "Resource\\Texture\\Boss\\Yeti\\");
	GlobalLoad::LoadSpriteSingle("IcicleShadow.png", "Resource\\Texture\\Boss\\Yeti\\");
	SoundLoad();

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	GameEngineRandom Inst;
	Inst.SetSeed(reinterpret_cast<__int64>(this));
	RandomIndex = Inst.RandomInt(0, 3);
	StuckAnimationIndex = RandomIndex + 4;

	BodyRenderer->SetSprite("Icicle.png", RandomIndex);
	BodyRenderer->SetImageScale({ 64.0f, 64.0f });

	switch (RandomIndex)
	{
	case 0:
		ShadowStandardPos = { 0.0f, -3.0f };
		ShadowStandardScale = { 80.0f, 80.0f, 1.0f };
		break;
	case 1:
		ShadowStandardPos = { 0.0f, -5.0f };
		ShadowStandardScale = { 64.0f, 64.0f, 1.0f };
		break;
	case 2:
		ShadowStandardPos = { 0.0f, -5.0f };
		ShadowStandardScale = { 64.0f, 64.0f, 1.0f };
		break;
	case 3:
		ShadowStandardPos = { 0.0f, -3.0f };
		ShadowStandardScale = { 80.0f, 80.0f, 1.0f };
		break;
	default:
		break;
	}

	ShadowStandardAlpha = 0.5f;
	ShadowScaleConstant = 1.0f;
	ShadowAlphaConstant = 1.0f;

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetSprite("IcicleShadow.png");
	ShadowRenderer->SetImageScale(ShadowStandardScale);
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha;

	FallingCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Icicle);
	FallingCollision->SetCollisionType(ColType::SPHERE2D);
	FallingCollision->Transform.SetLocalScale({ 16.0f, 16.0f });
	FallingCollision->Transform.SetLocalPosition({ 0.0f, -4.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 36.0f, 20.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 8.0f });
	Collision->Off();

	BlockedColParam.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Collisions)
		{
			_Collisions->GetActor()->Death();
			Collision->Death();
			Death();
		};
}

void Icicle::Update(float _Delta)
{
	switch (CurState)
	{
	case ICICLE_STATE::Falling:
		FallingUpdate(_Delta);
		break;
	case ICICLE_STATE::Stuck:
		StuckUpdate(_Delta);
		break;
	default:
		break;
	}

	if (true == GetLevel()->IsDebug)
	{
		GameEngineTransform TData;
		TData.SetLocalRotation(Transform.GetLocalRotationEuler());
		TData.SetLocalScale({ 5.0f, 5.0f });

		TData.SetLocalPosition(TargetPos);
		GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	}
}

void Icicle::ChangeState(ICICLE_STATE _State)
{
	CurState = _State;

	switch (CurState)
	{
	case ICICLE_STATE::Falling:
		FallingStart();
		break;
	case ICICLE_STATE::Stuck:
		StuckStart();
		break;
	default:
		break;
	}
}

void Icicle::SoundLoad()
{
	if (true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	GlobalLoad::LoadSound("Crush.ogg", "Resource\\Sound\\Player\\Death\\");

	size_t Index = GlobalValue::IcicleLandList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::IcicleLandList[i], "Resource\\Sound\\Boss\\Yeti\\");
	}

	Index = GlobalValue::IcicleSmashList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::IcicleSmashList[i], "Resource\\Sound\\Boss\\Yeti\\");
	}
}
