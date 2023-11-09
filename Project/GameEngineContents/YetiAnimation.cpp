#include "PreCompile.h"
#include "Yeti.h"

void Yeti::CreateYetiAnimation()
{
	GlobalLoad::LoadSpriteCut(10, 10, "Yeti.png", "Resource\\Texture\\Boss\\Yeti\\");
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->CreateAnimation("Sleep", "Yeti.png", 1.0f, 73, 73, false);

	BodyRenderer->CreateAnimation("Side_Idle", "Yeti.png", 1.0f, 0, 2, false);
	BodyRenderer->CreateAnimation("Down_Idle", "Yeti.png", 1.0f, 10, 12, false);
	BodyRenderer->CreateAnimation("Up_Idle", "Yeti.png", 1.0f, 20, 22, false);
	BodyRenderer->CreateAnimation("SideUp_Idle", "Yeti.png", 1.0f, 30, 32, false);
	BodyRenderer->CreateAnimation("SideDown_Idle", "Yeti.png", 1.0f, 40, 42, false);

	BodyRenderer->CreateAnimation("Side_Throwing", "Yeti.png", 1.0f, 3, 5, false);
	BodyRenderer->CreateAnimation("Down_Throwing", "Yeti.png", 1.0f, 13, 15, false);
	BodyRenderer->CreateAnimation("Up_Throwing", "Yeti.png", 1.0f, 23, 25, false);
	BodyRenderer->CreateAnimation("SideUp_Throwing", "Yeti.png", 1.0f, 33, 35, false);
	BodyRenderer->CreateAnimation("SideDown_Throwing", "Yeti.png", 1.0f, 43, 45, false);

	BodyRenderer->CreateAnimation("Side_Rolling", "Yeti.png", 1.0f, 6, 8, true);
	BodyRenderer->CreateAnimation("Down_Rolling", "Yeti.png", 1.0f, 16, 18, true);
	BodyRenderer->CreateAnimation("Up_Rolling", "Yeti.png", 1.0f, 26, 28, true);
	BodyRenderer->CreateAnimation("SideUp_Rolling", "Yeti.png", 1.0f, 36, 38, true);
	BodyRenderer->CreateAnimation("SideDown_Rolling", "Yeti.png", 1.0f, 46, 48, true);

	BodyRenderer->CreateAnimation("Side_Landing", "Yeti.png", 1.0f, 50, 52, false);
	BodyRenderer->CreateAnimation("Down_Landing", "Yeti.png", 1.0f, 60, 62, false);
	BodyRenderer->CreateAnimation("Up_Landing", "Yeti.png", 1.0f, 73, 75, false);
	BodyRenderer->CreateAnimation("SideUp_Landing", "Yeti.png", 1.0f, 80, 82, false);
	BodyRenderer->CreateAnimation("SideDown_Landing", "Yeti.png", 1.0f, 90, 92, false);

	BodyRenderer->CreateAnimation("Side_Hit", "Yeti.png", 1.0f, 9, 9, false);
	BodyRenderer->CreateAnimation("Down_Hit", "Yeti.png", 1.0f, 19, 19, false);
	BodyRenderer->CreateAnimation("Up_Hit", "Yeti.png", 1.0f, 29, 29, false);
	BodyRenderer->CreateAnimation("SideUp_Hit", "Yeti.png", 1.0f, 39, 39, false);
	BodyRenderer->CreateAnimation("SideDown_Hit", "Yeti.png", 1.0f, 49, 49, false);

	BodyRenderer->CreateAnimation("Side_Death", "Yeti.png", 1.0f, 0, 2, false);
	BodyRenderer->CreateAnimation("Down_Death", "Yeti.png", 1.0f, 10, 12, false);
	BodyRenderer->CreateAnimation("Up_Death", "Yeti.png", 1.0f, 23, 25, false);
	BodyRenderer->CreateAnimation("SideUp_Death", "Yeti.png", 1.0f, 30, 32, false);
	BodyRenderer->CreateAnimation("SideDown_Death", "Yeti.png", 1.0f, 40, 42, false);
}

void Yeti::SetAnimByDir(std::string_view _AnimName, int _Frame /*= 0*/, bool _Force /*= false*/)
{
	std::string AnimationName = "";

	switch (CurDir)
	{
	case YETI_DIRECTION::Left:
		AnimationName += "Left_";
		break;
	case YETI_DIRECTION::Right:
		AnimationName += "Right_";
		break;
	case YETI_DIRECTION::Up:
		AnimationName += "Up_";
		break;
	case YETI_DIRECTION::Down:
		AnimationName += "Down_";
		break;
	case YETI_DIRECTION::RightUp:
	case YETI_DIRECTION::LeftUp:
		AnimationName += "SideUp_";
		break;
	case YETI_DIRECTION::LeftDown:
	case YETI_DIRECTION::RightDown:
		AnimationName += "SideDown_";
		break;
	default:
		break;
	}

	AnimationName += _AnimName;

	if (0 != _Frame)
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force, _Frame);
	}
	else
	{
		BodyRenderer->ChangeAnimation(AnimationName, _Force);
	}
}