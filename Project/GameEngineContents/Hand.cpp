#include "PreCompile.h"
#include "Hand.h"
#include "ColossusBody.h"

bool Hand::ModeSwitchIsAbleValue = true;
bool Hand::AttackModeIsSwitch = true;

const float4 Hand::HidePos = { 1616.0f, -1928.0f };

SoundRandomPlayer Hand::FistAttackPlayer(GlobalValue::FistAttackList);

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::Init(HAND_DIR _Dir)
{
	PrevState = CurState;
	CurDir = _Dir;
	switch (_Dir)
	{
	case HAND_DIR::Left:
		break;
	case HAND_DIR::Right:
		BodyRenderer->LeftFlip();
		ShadowRenderer->LeftFlip();
		break;
	default:
		break;
	}

	ChangeState(HAND_STATE::Sleep);

}

void Hand::Start()
{
	SoundLoad();
	GlobalLoad::LoadSpriteCut(3, 1, "ColossusHand.png", "Resource\\Texture\\Boss\\Colossus");
	GlobalLoad::LoadSpriteCut(3, 1, "ColossusHandShadow.png", "Resource\\Texture\\Boss\\Colossus");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetImageScale({ 128.0f, 128.0f , 1.0f});
	BodyRenderer->Transform.SetLocalPosition({ 0.0f , -20.0f });
	BodyRenderer->CreateAnimation("Idle", "ColossusHand.png", 10.0f, 0, 0, true);
	BodyRenderer->CreateAnimation("InHide", "ColossusHand.png", 0.25f, 0, 2, false);
	BodyRenderer->CreateAnimation("InHover", "ColossusHand.png", 0.25f, 2, 0, false);

	ShadowStandardPos = { 0.0f, -30.0f };
	ShadowStandardScale = { 128.0f, 128.0f , 1.0f };

	ShadowStandardAlpha = 0.5f;
	ShadowScaleConstant = 3.0f;
	ShadowAlphaConstant = 5.0f;

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetImageScale(ShadowStandardScale);

	ShadowRenderer->CreateAnimation("Idle", "ColossusHandShadow.png", 10.0f, 0, 0, true);
	ShadowRenderer->CreateAnimation("Hide", "ColossusHandShadow.png", 10.0f, 2, 2, true);
	ShadowRenderer->CreateAnimation("InHide", "ColossusHandShadow.png", 0.25f, 0, 2, false);
	ShadowRenderer->CreateAnimation("InHover", "ColossusHandShadow.png", 0.25f, 2, 0, false);

	ChangeAnimaion("Idle");

	AttackCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBodyAttack);
	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	AttackCollision->Transform.SetLocalScale({ 64.0f, 32.0f });
	AttackCollision->Transform.SetLocalPosition({ 0.0f, 0.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 64.0f, 32.0f });

	GravityForce = 3000.0f;


	CSObj.Init(0.5f, 0.15f, 10.0f);
}

void Hand::Update(float _Delta)
{
	switch (CurState)
	{
	case HAND_STATE::Sleep:
		SleepUpdate(_Delta);
		break;
	case HAND_STATE::Hide:
		HideUpdate(_Delta);
		break;
	case HAND_STATE::Hover:
		HoverUpdate(_Delta);
		break;
	case HAND_STATE::Fall:
		FallUpdate(_Delta);
		break;
	case HAND_STATE::Land:
		LandUpdate(_Delta);
		break;
	case HAND_STATE::Hit:
		HitUpdate(_Delta);
		break;
	case HAND_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}

	ShadowRenderer->Transform.SetWorldPosition(FloorCheckPos + ShadowStandardPos);
	ShadowVariableByHeightUpdate(FloorCheckPos);

	if (true == GetLevel()->IsDebug)
	{
		GameEngineTransform TData;
		TData.SetLocalRotation(Transform.GetLocalRotationEuler());
		TData.SetLocalScale({ 5.0f, 5.0f });

		TData.SetLocalPosition(FloorCheckPos);
		GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });
	}
}

void Hand::ChangeState(HAND_STATE _State)
{
	PrevState = CurState;
	CurState = _State;

	switch (CurState)
	{
	case HAND_STATE::Sleep:
		SleepStart();
		break;
	case HAND_STATE::Hide:
		HideStart();
		break;
	case HAND_STATE::Hover:
		HoverStart();
		break;
	case HAND_STATE::Fall:
		FallStart();
		break;
	case HAND_STATE::Land:
		LandStart();
		break;
	case HAND_STATE::Hit:
		HitStart();
		break;
	case HAND_STATE::Death:
		DeathStart();
		break;
	default:
		break;
	}
}

void Hand::Gravity(float _Delta)
{
	if (FloorCheckPos.Y > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = FloorCheckPos.Y;
		Transform.SetLocalPosition(MovePos);

		ChangeState(HAND_STATE::Land);
		return;
	}

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);
}


void Hand::MoveToPlayer(float _Delta, const float4& _StartPos)
{
	float4 MovePos = _StartPos - FloorCheckPos;

	if (0.9f > MoveRatio)
	{
		MoveRatio = std::lerp(MoveRatio, 1.0f, _Delta);
		MovePos *= MoveRatio * MoveSpeed;

		FloorCheckPos += MovePos * _Delta;
		Transform.AddLocalPosition(MovePos * _Delta);
	}

	float4 VectorHandFromBody = FloorCheckPos - Body->Transform.GetLocalPosition() - float4{0.0f, -50.0f};
	float DistanceFromBody = DirectX::XMVectorGetX(DirectX::XMVector2Length(VectorHandFromBody.DirectXVector));

	while (450.0f < DistanceFromBody)
	{
		VectorHandFromBody = FloorCheckPos - Body->Transform.GetLocalPosition() - float4{ 0.0f, -50.0f };
		DistanceFromBody = DirectX::XMVectorGetX(DirectX::XMVector2Length(VectorHandFromBody.DirectXVector));
		FloorCheckPos -= Body->MoveDirBasis;
		Transform.AddLocalPosition(-Body->MoveDirBasis);
	}
}

void Hand::ChangeAnimaion(std::string_view _AnimationName)
{
	BodyRenderer->ChangeAnimation(_AnimationName);
	ShadowRenderer->ChangeAnimation(_AnimationName);
}

void Hand::HoverRotationUpdate(float _Delta)
{
	HoverMaxRotationValueUpdate();

	CurRotation.Z = std::lerp(CurRotation.Z, HoverRotation, HoverRotationSpeed * _Delta);

	Transform.SetLocalRotation(CurRotation);
}

void Hand::FallRotationUpdate(float _Delta)
{
	CurRotation.Z = std::lerp(CurRotation.Z, FallMaxRotation, FallRotationSpeed * _Delta);

	Transform.SetLocalRotation(CurRotation);
}

void Hand::HoverMaxRotationValueUpdate()
{
	float4 VectorBodyToHand = Body->Transform.GetLocalPosition() - FloorCheckPos;

	float AngleBodyToHand;
	AngleBodyToHand = DirectX::XMConvertToDegrees(atan2f(VectorBodyToHand.Y, VectorBodyToHand.X));

	while (-90.0f > AngleBodyToHand)
	{
		AngleBodyToHand += 360.0f;
	}

	AngleBodyToHand -= 90.0;


	// -90 ~ 90µµ°¡ ³ª¿È
	float Ratio = (AngleBodyToHand / 90);

	HoverRotation = HoverMaxRotation * Ratio;
}


void Hand::Levitaion(float _Delta)
{
	Radian += Speed * _Delta;

	if (Radian >= GameEngineMath::PI2 + GameEngineMath::PI / 2.0f)
	{
		Radian = GameEngineMath::PI / 2.0f;
	}

	float Ratio = cosf(Radian) * MovingHeight;
	float4 AddPos = { 0.0f, Ratio };

	Transform.AddLocalPosition(AddPos * _Delta);
}

void Hand::SoundLoad()
{
	if(true == SoundIsLoaded)
	{
		return;
	}

	SoundIsLoaded = true;

	size_t Index = GlobalValue::FistAttackList.size();
	for (size_t i = 0; i < Index; ++i)
	{
		GlobalLoad::LoadSound(GlobalValue::FistAttackList[i], "Resource\\Sound\\Boss\\Colossus\\");
	}
}
