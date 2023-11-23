#include "PreCompile.h"
#include "ColossusBody.h"
#include "Hand.h"

ColossusBody::ColossusBody()
{
}

ColossusBody::~ColossusBody()
{
}

void ColossusBody::Start()
{
	GlobalLoad::LoadSpriteSingle("ColossusBody.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteSingle("BodyLight2.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteCut(5, 1, "ColossusHead.png", "Resource\\Texture\\Boss\\Colossus\\");
	GlobalLoad::LoadSpriteCut(2, 1, "ColossusShoulder.png", "Resource\\Texture\\Boss\\Colossus\\");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetSprite("ColossusBody.png");
	BodyRenderer->SetImageScale({ 192.0f, 192.0f, 1.0f });
	BodyRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });

	BodyLightRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	BodyLightRenderer->SetPivotType(PivotType::Bottom);
	BodyLightRenderer->SetSprite("BodyLight2.png");
	BodyLightRenderer->SetImageScale({ 192.0f, 192.0f, 1.0f });
	BodyLightRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });
	BodyLightRenderer->GetColorData().MulColor.A = 0.0f;

	HeadRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	HeadRenderer->SetPivotType(PivotType::Bottom);
	HeadRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	HeadRenderer->Transform.SetLocalPosition({ 0.0f, 128.0f });

	HeadRenderer->CreateAnimation("Sleep", "ColossusHead.png", 1.0f, 0, 0, true);
	HeadRenderer->CreateAnimation("WakeUp", "ColossusHead.png", 0.1f, 0, 2, false);
	HeadRenderer->CreateAnimation("Idle", "ColossusHead.png", 1.0f, 2, 2, true);
	HeadRenderer->CreateAnimation("Angry", "ColossusHead.png", 2.0f, 3, 3, false);
	HeadRenderer->CreateAnimation("Death", "ColossusHead.png", 1.0f, 4, 4, true);

	LeftShoulderRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	LeftShoulderRenderer->SetPivotType(PivotType::Bottom);
	LeftShoulderRenderer->SetSprite("ColossusShoulder.png", 0);
	LeftShoulderRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	LeftShoulderRenderer->Transform.SetLocalPosition({ -88.0f, 56.0f });

	RightShoulderRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY_BACK);
	RightShoulderRenderer->SetPivotType(PivotType::Bottom);
	RightShoulderRenderer->SetSprite("ColossusShoulder.png", 0);
	RightShoulderRenderer->SetImageScale({ 128.0f, 128.0f, 1.0f });
	RightShoulderRenderer->Transform.SetLocalPosition({ 88.0f, 56.0f });

	BodyCollision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetLocalScale({ 128.0f, 64.0f, 1.0f });
	BodyCollision->Transform.SetLocalPosition({ 0.0f, 32.0f });

	BodyCollision2 = CreateComponent<GameEngineCollision>(COLLISION_TYPE::BossBody);
	BodyCollision2->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision2->Transform.SetLocalScale({ 64.0f, 32.0f, 1.0f });
	BodyCollision2->Transform.SetLocalPosition({ 48.0f, 64.0f });
	BodyCollision2->Off();

	Collision = CreateComponent<GameEngineCollision>(COLLISION_TYPE::Weakness);
	Collision->SetCollisionType(ColType::SPHERE2D);
	Collision->Transform.SetLocalScale({ 32.0f, 32.0f, 1.0f });
	Collision->Transform.SetLocalPosition({ 0.0f, 64.0f });
	Collision->Off();

}

void ColossusBody::Update(float _Delta)
{
	switch (CurState)
	{
	case BODY_STATE::Sleep:
		SleepUpdate(_Delta);
		break;
	case BODY_STATE::WakeUp:
		WakeUpUpdate(_Delta);
		break;
	case BODY_STATE::Idle:
		IdleUpdate(_Delta);
		break;
	case BODY_STATE::Hit:
		HitUpdate(_Delta);
		break;
	case BODY_STATE::Death:
		DeathUpdate(_Delta);
		break;
	default:
		break;
	}

	if (BODY_STATE::Sleep != CurState &&
		BODY_STATE::WakeUp != CurState)
	{
		WakeUpRatio = std::lerp(WakeUpRatio, 0.5f, 5.0f * _Delta);
		CameraManager::AddCameraPosFromBoss = (Transform.GetLocalPosition() - EnymePlayer->Transform.GetLocalPosition()) * WakeUpRatio;

		ZoomRatio = std::lerp(ZoomRatio, 1.0f, 5.0f * _Delta);
		CameraManager::AddCameraZoomFromBoss = ZoomRatio;
	}
}


void ColossusBody::ChangeState(BODY_STATE _State)
{
	CurState = _State;

	switch (CurState)
	{
	case BODY_STATE::Sleep:
		SleepStart();
		break;
	case BODY_STATE::WakeUp:
		WakeUpStart();
		break;
	case BODY_STATE::Idle:
		IdleStart();
		break;
	case BODY_STATE::Hit:
		HitStart();
		break;
	case BODY_STATE::Death:
		DeathStart();
		break;
	default:
		break;
	}
}


void ColossusBody::Levitaion(float _Delta)
{
	Radian += Speed * _Delta;

	if (Radian >= GameEngineMath::PI2 + GameEngineMath::PI / 2.0f)
	{
		Radian = GameEngineMath::PI / 2.0f;
	}

	float Ratio = sinf(Radian) * MovingHeight;
	float4 AddPos = { 0.0f, Ratio };

	HeadRenderer->Transform.AddLocalPosition(AddPos * _Delta);

	AddPos.X = Ratio / 2.0f;
	RightShoulderRenderer->Transform.AddLocalPosition(AddPos * _Delta);

	AddPos.X *= -1.0f;
	LeftShoulderRenderer->Transform.AddLocalPosition(AddPos * _Delta);

	if (BODY_STATE::Idle == CurState)
	{
		BodyLightRenderer->GetColorData().MulColor.A = sinf(Radian + 1.5f);
	}
}
