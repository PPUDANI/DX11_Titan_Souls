#include "PreCompile.h"
#include "Heart.h"


Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{
    BossBase::Start();

	Collision->SetCollisionType(ColType::OBBBOX2D);
	Collision->Transform.SetLocalScale({ 50.0f, 40.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -10.0f, 0.0f });
	GlobalLoad::LoadSpriteCut(6, 1, "Heart.png", "Resource\\Texture\\Boss\\SludgeHeart\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->Transform.SetLocalPosition(RenderPosBase);
	Renderer->SetImageScale({ 64.0f, 64.0f });

	Renderer->CreateAnimation("InSludge", "Heart.png", 10.0f, 0, 0, false);
	Renderer->CreateAnimation("Idle", "Heart.png", 10.0f, 1, 1, false);
	Renderer->CreateAnimation("Jump", "Heart.png", 0.2f, 2, 3, false);
	Renderer->CreateAnimation("Landing", "Heart.png", 0.2f, 4, 5, false);
	Renderer->CreateAnimation("Death", "Heart.png", 10.0f, 4, 4, false);

	Renderer->ChangeAnimation("Idle");

	ChangeState(HEART_STATE::Idle);

}

void Heart::Update(float _Delta)
{
	BossBase::Update(_Delta);

	if (true == Collision->Collision(COLLISION_TYPE::Arrow))
	{
		ChangeState(HEART_STATE::Death);
	}


	SetMoveDir(JumpStartPos);

	switch (CurState)
	{
	case HEART_STATE::InSludge:
		InSludgeUpdate(_Delta);
		break;
	case HEART_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case HEART_STATE::Jump:
		JumpUpdate(_Delta);
		break;
	case HEART_STATE::Fall:
		FallUpdate(_Delta);
		break;
	case HEART_STATE::Landing:
		LandingUpdate(_Delta);
		break;
	default:
		break;
	}

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 10.0f, 10.0f });

	TData.SetLocalPosition(JumpStartPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y - 8.0f;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	Renderer->Transform.SetLocalPosition(RenderPos);
}


void Heart::ChangeState(HEART_STATE _State)
{
	if (CurState == _State)
	{
		return;
	}

	CurState = _State;

	switch (CurState)
	{
	case HEART_STATE::InSludge:
		InSludgeStart();
		break;
	case HEART_STATE::Idle:
		IdleStart();
		break;
	case HEART_STATE::Jump:
		JumpStart();
		break;
	case HEART_STATE::Fall:
		FallStart();
		break;
	case HEART_STATE::Landing:
		LandingStart();
		break;
	default:
		break;
	}
}




void Heart::Gravity(float _Delta)
{
	if (JumpStartPos.Y > Transform.GetLocalPosition().Y)
	{
		float4 MovePos = Transform.GetLocalPosition();
		MovePos.Y = JumpStartPos.Y;
		Transform.SetLocalPosition(MovePos);
		ChangeState(HEART_STATE::Landing);
		return;
	}

	GravityValue -= GravityForce * _Delta;
	float4 MovePos = GravityDir * GravityValue * _Delta;
	Transform.AddLocalPosition(MovePos);
}


void Heart::MoveToPlayer(float _Delta)
{
	float4 MovePos = MoveDirBasis * MoveSpeed * _Delta;

	if (2.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().X - JumpStartPos.X))
	{
		MovePos.X = 0.0f;
	}

	if (2.0f > std::abs(EnymePlayer->Transform.GetLocalPosition().Y - JumpStartPos.Y))
	{
		MovePos.Y = 0.0f;
	}

	Transform.AddLocalPosition(MovePos);
	JumpStartPos += MovePos;
}

