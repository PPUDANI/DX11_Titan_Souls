#include "PreCompile.h"
#include "Sludge.h"

Sludge::Sludge()
{
}

Sludge::~Sludge()
{
}

void Sludge::Start()
{
	JumpBoss::Start();

	GlobalLoad::LoadSpriteCut(2, 1, "Sludge.png", "Resource\\Texture\\Boss\\SludgeHeart");
	GlobalLoad::LoadSpriteSingle("SludgeShadow.png", "Resource\\Texture\\Boss\\SludgeHeart");
	RenderPosBase.Y = -64.0f;

	// Renderer
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->CreateAnimation("Default", "Sludge.png", 1.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Hit", "Sludge.png", 0.1f, 0, 1, true);
	BodyRenderer->ChangeAnimation("Default");
	BodyRenderer->SetImageScale({ 256.0f, 256.0f });
	BodyRenderer->Transform.AddLocalPosition(RenderPosBase);


	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetSprite("SludgeShadow.png");
	ShadowRenderer->SetImageScale({ 128.0f, 128.0f });
	ShadowRenderer->Transform.AddLocalPosition(RenderPosBase);

	// Collision setting
	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Boss);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 230.0f, 128.0f, -10.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 96.0f, -10.0f });

	GravityForce = 1200.0f;
	MoveSpeed = 200.0f;
	ChangeState(JUMPBOSS_STATE::Idle);
}

void Sludge::Update(float _Delta)
{
	if (float4::ZERO == JumpStartPos)
	{
		JumpStartPos = Transform.GetLocalPosition();
	}
	SetMoveDir(JumpStartPos);

	ShadowRenderer->Transform.SetLocalPosition(JumpStartPos - Transform.GetLocalPosition() + RenderPosBase);

	JumpBoss::Update(_Delta);

	BodyRenderer->SetImageScale(RenderScale / DividedCount);
	ShadowRenderer->SetImageScale(ShadowRenderScale / DividedCount);

	//GameEngineTransform TData;
	//TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	//TData.SetLocalScale({ 5.0f, 5.0f });
	//TData.SetLocalPosition(JumpStartPos);
	//GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y + RenderPosBase.Y;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	BodyRenderer->Transform.SetLocalPosition(RenderPos + RenderPosBase);
}


void Sludge::DecreaseY(float _SpeedPerSecond)
{
	if (MaxScale > RenderScale.X)
	{
		ExpandDir = SLUDGE_STATE::Decrease;
		RenderScale.Y -= ExpandDefalutSpeed * _SpeedPerSecond;
		RenderScale.X += ExpandDefalutSpeed * _SpeedPerSecond;

		ShadowRenderScale.X = RenderScale.X * 0.85f;
		ShadowRenderScale.Y = 128.0f * 0.85f + ShadowRenderScale.X * 0.1f;
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Increase;
	}
}

void Sludge::IncreaseY(float _SpeedPerSecond)
{
	if (MaxScale > RenderScale.Y)
	{
		ExpandDir = SLUDGE_STATE::Increase;
		RenderScale.Y += ExpandDefalutSpeed * _SpeedPerSecond;
		RenderScale.X -= ExpandDefalutSpeed * _SpeedPerSecond;

		ShadowRenderScale.X = RenderScale.X * 0.85f;
		ShadowRenderScale.Y = 128.0f * 0.85f + ShadowRenderScale.X * 0.1f;
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Decrease;
	}
}
