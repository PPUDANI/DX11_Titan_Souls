#include "PreCompile.h"
#include "StartDoor.h"
#include "CrystalBall.h"
StartDoor::StartDoor()
{
}

StartDoor::~StartDoor()
{
}

void StartDoor::CollisionOn()
{
	CurMap->SetColTile(Transform.GetLocalPosition() + float4{0.0f, 8.0f}, -1, 1, TILE_COLLISION_TYPE::RECT);
}

void StartDoor::CollisionOff()
{
	CurMap->SetColTile(Transform.GetLocalPosition() + float4{ 0.0f, 8.0f }, -1, 1, TILE_COLLISION_TYPE::EMPTY);
}

void StartDoor::Start()
{
	GlobalLoad::LoadSpriteCut(2, 1, "StartDoor.png", "Resource\\Texture\\Map\\");

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	Renderer->SetSprite("StartDoor.png", 0);
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetImageScale({ 96.0f, 96.0f, 1.0f });

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	LightRenderer->SetSprite("StartDoor.png", 1);
	LightRenderer->SetPivotType(PivotType::Bottom);
	LightRenderer->SetImageScale({ 96.0f, 96.0f, 1.0f });
	LightRenderer->Off();
}

void StartDoor::Update(float _Delta)
{
	if (true == OpenDoorValue)
	{
		if (LightTime > LightTimer)
		{
			LightTimer += _Delta;
			LightRenderer->GetColorData().MulColor.A = LightTimer / LightTime;
			return;
		}

		if (OpenTime < Timer)
		{
			Timer = OpenTime;
			OpenDoorValue = false;
			Renderer->Transform.SetLocalPosition({ 0.0f, 80.0f });
			LightRenderer->Transform.SetLocalPosition({ 0.0f, 80.0f });
		}
		else
		{
			Timer += _Delta;
			Inst.SetSeed(reinterpret_cast<__int64>(this) + ++RandomSeedCount);
			float RandomNumber = Inst.RandomFloat(-1.0f, 1.0f);
			Renderer->Transform.SetLocalPosition({ RandomNumber, 80.0f * Timer / OpenTime });
			LightRenderer->Transform.SetLocalPosition({ RandomNumber, 80.0f * Timer / OpenTime });
		}


	}
}
