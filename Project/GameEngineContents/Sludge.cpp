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

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::HasAlpah);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->CreateAnimation("Default", "Sludge.png", 1.0f, 0, 0, false);
	Renderer->CreateAnimation("Hit", "Sludge.png", 0.1f, 0, 1, true);
	Renderer->ChangeAnimation("Default");
	Renderer->SetImageScale({ 256.0f, 256.0f });

	// Collision setting
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale({ 38.0f, 25.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, -8.0f, 0.0f });

	GravityForce = 1200.0f;
	ChangeState(JUMPBOSS_STATE::Idle);
}

void Sludge::Update(float _Delta)
{
	SetMoveDir(JumpStartPos);

	JumpBoss::Update(_Delta);

	Renderer->SetImageScale(RenderScale);

	GameEngineTransform TData;
	TData.SetLocalRotation(Transform.GetLocalRotationEuler());
	TData.SetLocalScale({ 5.0f, 5.0f });

	TData.SetLocalPosition(JumpStartPos);
	GameEngineDebug::DrawBox2D(TData, { 0, 1, 1, 1 });

	float4 RenderPos = float4::ZERO;
	float CameraYPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y;
	float ActorYPos = Transform.GetWorldPosition().Y - 48.0f;
	GlobalCalculator::CalDepthValue(CameraYPos, ActorYPos, RenderPos);
	Renderer->Transform.SetLocalPosition(RenderPos + RenderBasePos);
}


void Sludge::DecreaseY(float _SpeedPerSecond)
{
	if (MaxScale > RenderScale.X)
	{
		ExpandDir = SLUDGE_STATE::Decrease;
		RenderScale.Y -= ExpandDefalutSpeed * _SpeedPerSecond;
		RenderScale.X += ExpandDefalutSpeed * _SpeedPerSecond;
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
	}
	else
	{
		ExpandDir = SLUDGE_STATE::Decrease;
	}
}
