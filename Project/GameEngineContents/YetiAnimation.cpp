#include "PreCompile.h"
#include "Yeti.h"

void Yeti::CreateYetiAnimation()
{
	GlobalLoad::LoadSpriteCut(10, 10, "Yeti.png", "Resource\\Texture\\Boss\\Yeti\\");
	GlobalLoad::LoadSpriteSingle("YetiShadow.png", "Resource\\Texture\\Boss\\Yeti\\");
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Y_SORT_ENTITY);
	BodyRenderer->SetPivotType(PivotType::Bottom);
	BodyRenderer->SetImageScale({ 192.0f, 192.0f });
	BodyRenderer->Transform.AddLocalPosition(RendererStandardPos);
	BodyRenderer->CreateAnimation("Sleep", "Yeti.png", 1.0f, 73, 73, false);

	BodyRenderer->CreateAnimation("Side_Idle", "Yeti.png", 0.3f, 0, 2, true);
	BodyRenderer->CreateAnimation("Up_Idle", "Yeti.png", 0.3f, 10, 12, true);
	BodyRenderer->CreateAnimation("Down_Idle", "Yeti.png", 0.3f, 20, 22, true);
	BodyRenderer->CreateAnimation("SideUp_Idle", "Yeti.png", 0.3f, 30, 32, true);
	BodyRenderer->CreateAnimation("SideDown_Idle", "Yeti.png", 0.3f, 40, 42, true);

	BodyRenderer->CreateAnimation("Side_Throwing", "Yeti.png", 0.1f, 3, 5, false);
	BodyRenderer->CreateAnimation("Up_Throwing", "Yeti.png", 0.1f, 13, 15, false);
	BodyRenderer->CreateAnimation("Down_Throwing", "Yeti.png", 0.1f, 23, 25, false);
	BodyRenderer->CreateAnimation("SideUp_Throwing", "Yeti.png", 0.1f, 33, 35, false);
	BodyRenderer->CreateAnimation("SideDown_Throwing", "Yeti.png", 0.1f, 43, 45, false);

	BodyRenderer->CreateAnimation("Side_ReadyToRoll", "Yeti.png", 0.08f, 3, 4, false);
	BodyRenderer->CreateAnimation("Up_ReadyToRoll", "Yeti.png", 0.08f, 13, 14, false);
	BodyRenderer->CreateAnimation("Down_ReadyToRoll", "Yeti.png", 0.08f, 23, 24, false);
	BodyRenderer->CreateAnimation("SideUp_ReadyToRoll", "Yeti.png", 0.08f, 33, 34, false);
	BodyRenderer->CreateAnimation("SideDown_ReadyToRoll", "Yeti.png", 0.08f, 43, 44, false);
	
	BodyRenderer->CreateAnimation("Side_Rolling", "Yeti.png", 0.08f, 6, 8, true);
	BodyRenderer->CreateAnimation("Up_Rolling", "Yeti.png", 0.08f, 16, 18, true);
	BodyRenderer->CreateAnimation("Down_Rolling", "Yeti.png", 0.08f, 26, 28, true);
	BodyRenderer->CreateAnimation("SideUp_Rolling", "Yeti.png", 0.08f, 36, 38, true);
	BodyRenderer->CreateAnimation("SideDown_Rolling", "Yeti.png", 0.08f, 46, 48, true);

	BodyRenderer->CreateAnimation("Side_Landing", "Yeti.png", 0.1f, 50, 52, false);
	BodyRenderer->CreateAnimation("Up_Landing", "Yeti.png", 0.1f, 60, 62, false);
	BodyRenderer->CreateAnimation("Down_Landing", "Yeti.png", 0.1f, 70, 72, false);
	BodyRenderer->CreateAnimation("SideUp_Landing", "Yeti.png", 0.1f, 80, 82, false);
	BodyRenderer->CreateAnimation("SideDown_Landing", "Yeti.png", 0.1f, 90, 92, false);

	BodyRenderer->CreateAnimation("Side_Hit", "Yeti.png", 1.0f, 9, 9, false);
	BodyRenderer->CreateAnimation("Up_Hit", "Yeti.png", 1.0f, 19, 19, false);
	BodyRenderer->CreateAnimation("Down_Hit", "Yeti.png", 1.0f, 29, 29, false);
	BodyRenderer->CreateAnimation("SideUp_Hit", "Yeti.png", 1.0f, 39, 39, false);
	BodyRenderer->CreateAnimation("SideDown_Hit", "Yeti.png", 1.0f, 49, 49, false);

	BodyRenderer->CreateAnimation("Side_Death", "Yeti.png", 0.2f, 54, 56, false);
	BodyRenderer->CreateAnimation("Up_Death", "Yeti.png", 0.2f, 64, 66, false);
	BodyRenderer->CreateAnimation("Down_Death", "Yeti.png", 0.2f, 74, 76, false);
	BodyRenderer->CreateAnimation("SideUp_Death", "Yeti.png", 0.2f, 84, 86, false);
	BodyRenderer->CreateAnimation("SideDown_Death", "Yeti.png", 0.2f, 94, 96, false);

	ShadowStandardPos = { 0.0f, -30.0f };
	ShadowStandardScale = { 120.0f, 48.0f, 1.0f };
	ShadowStandardAlpha = 0.5f;
	ShadowScaleConstant = 3.0f;
	ShadowAlphaConstant = 5.0f;

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Shadow);
	ShadowRenderer->SetSprite("YetiShadow.png");
	ShadowRenderer->SetPivotType(PivotType::Bottom);
	ShadowRenderer->SetImageScale(ShadowStandardScale);
	ShadowRenderer->GetColorData().MulColor.A = ShadowStandardAlpha;
}

void Yeti::SetAnimByDir(std::string_view _AnimName, int _Frame /*= 0*/, bool _Force /*= false*/)
{
	std::string AnimationName = "";

	switch (CurDir)
	{
	case YETI_DIRECTION::Right:
		BodyRenderer->RightFlip();
		AnimationName += "Side_";
		break;
	case YETI_DIRECTION::RightUp:
		BodyRenderer->RightFlip();
		AnimationName += "SideUp_";
		break;
	case YETI_DIRECTION::Up:
		AnimationName += "Up_";
		break;
	case YETI_DIRECTION::LeftUp:
		BodyRenderer->LeftFlip();
		AnimationName += "SideUp_";
		break;
	case YETI_DIRECTION::Left:
		BodyRenderer->LeftFlip();
		AnimationName += "Side_";
		break;
	case YETI_DIRECTION::LeftDown:
		BodyRenderer->LeftFlip();
		AnimationName += "SideDown_";
		break;
	case YETI_DIRECTION::Down:
		AnimationName += "Down_";
		break;
	case YETI_DIRECTION::RightDown:
		BodyRenderer->RightFlip();
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