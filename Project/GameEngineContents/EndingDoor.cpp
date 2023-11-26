#include "PreCompile.h"
#include "EndingDoor.h"

EndingDoor::EndingDoor()
{
}

EndingDoor::~EndingDoor()
{
}

void EndingDoor::Start()
{
	GlobalLoad::LoadSpriteCut(2, 1, "EndingDoor.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(2, 1, "EndingDoorLight.png", "Resource\\Texture\\Map\\");

	LeftDoor = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	LeftDoor->SetSprite("EndingDoor.png", 0);
	LeftDoor->SetPivotType(PivotType::Bottom);
	LeftDoor->SetImageScale({ 176.0f, 448.0f, 1.0f});
	LeftDoor->Transform.SetLocalPosition({ -88.0f, 0.0f });

	RightDoor = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	RightDoor->SetSprite("EndingDoor.png", 1);
	RightDoor->SetPivotType(PivotType::Bottom);
	RightDoor->SetImageScale({ 176.0f, 448.0f, 1.0f });
	RightDoor->Transform.SetLocalPosition({ 88.0f, 0.0f });

	LeftDoorLight = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	LeftDoorLight->SetSprite("EndingDoorLight.png", 0);
	LeftDoorLight->SetPivotType(PivotType::Bottom);
	LeftDoorLight->SetImageScale({ 176.0f, 448.0f, 1.0f });
	LeftDoorLight->Transform.SetLocalPosition({ -88.0f, 0.0f });
	LeftDoorLight->GetColorData().MulColor.A = 0.0f;

	RightDoorLight = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	RightDoorLight->SetSprite("EndingDoorLight.png", 1);
	RightDoorLight->SetPivotType(PivotType::Bottom);
	RightDoorLight->SetImageScale({ 176.0f, 448.0f, 1.0f });
	RightDoorLight->Transform.SetLocalPosition({ 88.0f, 0.0f });
	RightDoorLight->GetColorData().MulColor.A = 0.0f;
}

void EndingDoor::Update(float _Delta)
{
	if (true == OpenDoorValue)
	{
		if (LightingTime > LightingTimer)
		{
			LightingTimer += _Delta;

			LeftDoorLight->GetColorData().MulColor.A = LightingTimer / LightingTime;
			RightDoorLight->GetColorData().MulColor.A = LightingTimer / LightingTime;

			return;
		}

		float MovePos = OpenSpeed * _Delta;
		MovedDistance += MovePos;
		if (MaxOpenDistance < MovedDistance)
		{
			MovedDistance = MaxOpenDistance + 88.0f;
			LeftDoor->Transform.SetLocalPosition({ -MovedDistance, 0.0f });
			LeftDoorLight->Transform.SetLocalPosition({ -MovedDistance, 0.0f });
			RightDoor->Transform.SetLocalPosition({ MovedDistance, 0.0f });
			RightDoorLight->Transform.SetLocalPosition({ MovedDistance, 0.0f });
			OpenDoorValue = false;
		}
		else
		{
			LeftDoor->Transform.AddLocalPosition({ -MovePos, 0.0f });
			LeftDoorLight->Transform.AddLocalPosition({ -MovePos, 0.0f });
			RightDoor->Transform.AddLocalPosition({ MovePos, 0.0f });
			RightDoorLight->Transform.AddLocalPosition({ MovePos, 0.0f });
		}
	}
}
