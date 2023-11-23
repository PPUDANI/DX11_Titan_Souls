#include "PreCompile.h"
#include "Hand.h"

bool Hand::ModeSwitchIsAbleValue = true;
bool Hand::AttackModeIsSwitch = true;
const float4 Hand::HidePos = { 1616.0f, -1850.0f };

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
		Renderer->LeftFlip();
		break;
	default:
		break;
	}

	ChangeState(HAND_STATE::Sleep);

}

void Hand::Start()
{
	GlobalLoad::LoadSpriteCut(3, 1, "ColossusHand.png", "Resource\\Texture\\Boss\\Colossus");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetImageScale({ 128.0f, 128.0f , 1.0f});
	Renderer->Transform.SetLocalPosition({ 0.0f , -50.0f });
	Renderer->CreateAnimation("Idle", "ColossusHand.png", 10.0f, 0, 0, true);
	Renderer->CreateAnimation("Hide", "ColossusHand.png", 10.0f, 2, 2, true);
	Renderer->CreateAnimation("InHide", "ColossusHand.png", 0.2f, 0, 2, false);
	Renderer->CreateAnimation("InHover", "ColossusHand.png", 0.2f, 2, 0, false);

	Renderer->ChangeAnimation("Idle");

	AttackCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBodyAttack);
	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	AttackCollision->Transform.SetLocalScale({ 64.0f, 36.0f });
	AttackCollision->Transform.SetLocalPosition({ 0.0f, -10.0f });

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 64.0f, 36.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -10.0f });

	GravityForce = 1500.0f;
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
	default:
		break;
	}

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
	//float4 MovePos = MoveDirBasis * MoveSpeed * _Delta;
	//float4 StartPos = _StartPos - FloorCheckPos;
	//float LengthStartPosToPlayer = DirectX::XMVectorGetX(DirectX::XMVector2Length(StartPos.DirectXVector));
	float4 MovePos = _StartPos - FloorCheckPos;

	MoveRatio = std::lerp(MoveRatio, 1.0f, _Delta * MoveSpeed);
	MovePos *= MoveRatio;
	FloorCheckPos += MovePos;
	Transform.AddLocalPosition(MovePos);

	//if (5.0f > LengthStartPosToPlayer)
	//{
	//	FloorCheckPos = _StartPos;
	//	float4 SetPos = Transform.GetLocalPosition();
	//	SetPos.X = FloorCheckPos.X;
	//	Transform.SetLocalPosition(SetPos);
	//}
	//else
	//{
	//	FloorCheckPos += MovePos;
	//	Transform.AddLocalPosition(MovePos);
	//}
}
