#include "PreCompile.h"
#include "Player.h"


void Player::CreatePlayerbodyAnimation()
{
	// Load "Player.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Player.png", "Resource\\Texture\\PlayerElement\\");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Player);
	BodyRenderer->SetSprite("Player.png");
	BodyRenderer->SetImageScale(PlayerSize);

	// Idle Animations
	BodyRenderer->CreateAnimation("Right_Idle", "Player.png", 1.0f, 0, 0, false);
	BodyRenderer->CreateAnimation("Up_Idle", "Player.png", 1.0f, 32, 32, false);
	BodyRenderer->CreateAnimation("Left_Idle", "Player.png", 1.0f, 64, 64, false);
	BodyRenderer->CreateAnimation("Down_Idle", "Player.png", 1.0f, 96, 96, false);
	BodyRenderer->CreateAnimation("RightDown_Idle", "Player.png", 1.0f, 128, 128, false);
	BodyRenderer->CreateAnimation("LeftDown_Idle", "Player.png", 1.0f, 160, 160, false);
	BodyRenderer->CreateAnimation("LeftUp_Idle", "Player.png", 1.0f, 192, 192, false);
	BodyRenderer->CreateAnimation("RightUp_Idle", "Player.png", 1.0f, 224, 224, false);

	// Walk Animations
	BodyRenderer->CreateAnimation("Right_Walk", "Player.png", 0.1f, 0, 5, true);
	BodyRenderer->CreateAnimation("Up_Walk", "Player.png", 0.1f, 32, 37, true);
	BodyRenderer->CreateAnimation("Left_Walk", "Player.png", 0.1f, 64, 69, true);
	BodyRenderer->CreateAnimation("Down_Walk", "Player.png", 0.1f, 96, 101, true);
	BodyRenderer->CreateAnimation("RightDown_Walk", "Player.png", 0.1f, 128, 133, true);
	BodyRenderer->CreateAnimation("LeftDown_Walk", "Player.png", 0.1f, 160, 165, true);
	BodyRenderer->CreateAnimation("LeftUp_Walk", "Player.png", 0.1f, 192, 197, true);
	BodyRenderer->CreateAnimation("RightUp_Walk", "Player.png", 0.1f, 224, 229, true);

	// Run Animations
	BodyRenderer->CreateAnimation("Right_Run", "Player.png", 0.08f, 270, 275, true);
	BodyRenderer->CreateAnimation("Up_Run", "Player.png", 0.08f, 302, 307, true);
	BodyRenderer->CreateAnimation("Left_Run", "Player.png", 0.08f, 334, 339, true);
	BodyRenderer->CreateAnimation("Down_Run", "Player.png", 0.08f, 366, 371, true);
	BodyRenderer->CreateAnimation("RightDown_Run", "Player.png", 0.08f, 398, 403, true);
	BodyRenderer->CreateAnimation("LeftDown_Run", "Player.png", 0.08f, 430, 435, true);
	BodyRenderer->CreateAnimation("LeftUp_Run", "Player.png", 0.08f, 462, 467, true);
	BodyRenderer->CreateAnimation("RightUp_Run", "Player.png", 0.08f, 494, 499, true);

	// Roll Animations
	BodyRenderer->CreateAnimation("Right_Roll", "Player.png", 0.063f, 6, 11, false);
	BodyRenderer->CreateAnimation("Up_Roll", "Player.png", 0.063f, 38, 43, false);
	BodyRenderer->CreateAnimation("Left_Roll", "Player.png", 0.063f, 70, 75, false);
	BodyRenderer->CreateAnimation("Down_Roll", "Player.png", 0.063f, 102, 107, false);
	BodyRenderer->CreateAnimation("RightDown_Roll", "Player.png", 0.063f, 134, 139, false);
	BodyRenderer->CreateAnimation("LeftDown_Roll", "Player.png", 0.063f, 166, 171, false);
	BodyRenderer->CreateAnimation("LeftUp_Roll", "Player.png", 0.063f, 198, 203, false);
	BodyRenderer->CreateAnimation("RightUp_Roll", "Player.png", 0.063f, 230, 235, false);

	// Death Animations
	BodyRenderer->CreateAnimation("Right_Death", "Player.png", 1.0f, 12, 12, false);
	BodyRenderer->CreateAnimation("Up_Death", "Player.png", 1.0f, 44, 44, false);
	BodyRenderer->CreateAnimation("Left_Death", "Player.png", 1.0f, 76, 76, false);
	BodyRenderer->CreateAnimation("Down_Death", "Player.png", 1.0f, 108, 108, false);
	BodyRenderer->CreateAnimation("RightDown_Death", "Player.png", 1.0f, 140, 140, false);
	BodyRenderer->CreateAnimation("LeftDown_Death", "Player.png", 1.0f, 172, 172, false);
	BodyRenderer->CreateAnimation("LeftUp_Death", "Player.png", 1.0f, 204, 204, false);
	BodyRenderer->CreateAnimation("RightUp_Death", "Player.png", 1.0f, 236, 236, false);

	// Spawn Animations
	BodyRenderer->CreateAnimation("Spawn", "Player.png", 0.15f, 79, 88, true);
}

void Player::CreateBowAnimation()
{
	// Load "Bow.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Bow.png", "Resource\\Texture\\PlayerElement\\");

	BowRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Player);
	BowRenderer->SetSprite("Bow.png");
	BowRenderer->SetImageScale(PlayerSize);

	// Idle Animations
	BowRenderer->CreateAnimation("Right_Idle", "Bow.png", 1.0f, 0, 0, false);
	BowRenderer->CreateAnimation("Up_Idle", "Bow.png", 1.0f, 32, 32, false);
	BowRenderer->CreateAnimation("Left_Idle", "Bow.png", 1.0f, 64, 64, false);
	BowRenderer->CreateAnimation("Down_Idle", "Bow.png", 1.0f, 96, 96, false);
	BowRenderer->CreateAnimation("RightDown_Idle", "Bow.png", 1.0f, 128, 128, false);
	BowRenderer->CreateAnimation("LeftDown_Idle", "Bow.png", 1.0f, 160, 160, false);
	BowRenderer->CreateAnimation("LeftUp_Idle", "Bow.png", 1.0f, 192, 192, false);
	BowRenderer->CreateAnimation("RightUp_Idle", "Bow.png", 1.0f, 224, 224, false);

	// Walk Animations
	BowRenderer->CreateAnimation("Right_Walk", "Bow.png", 0.1f, 0, 5, true);
	BowRenderer->CreateAnimation("Up_Walk", "Bow.png", 0.1f, 32, 37, true);
	BowRenderer->CreateAnimation("Left_Walk", "Bow.png", 0.1f, 64, 69, true);
	BowRenderer->CreateAnimation("Down_Walk", "Bow.png", 0.1f, 96, 101, true);
	BowRenderer->CreateAnimation("RightDown_Walk", "Bow.png", 0.1f, 128, 133, true);
	BowRenderer->CreateAnimation("LeftDown_Walk", "Bow.png", 0.1f, 160, 165, true);
	BowRenderer->CreateAnimation("LeftUp_Walk", "Bow.png", 0.1f, 192, 197, true);
	BowRenderer->CreateAnimation("RightUp_Walk", "Bow.png", 0.1f, 224, 229, true);

	// Run Animations
	BowRenderer->CreateAnimation("Right_Run", "Bow.png", 0.08f, 270, 275, true);
	BowRenderer->CreateAnimation("Up_Run", "Bow.png", 0.08f, 302, 307, true);
	BowRenderer->CreateAnimation("Left_Run", "Bow.png", 0.08f, 334, 339, true);
	BowRenderer->CreateAnimation("Down_Run", "Bow.png", 0.08f, 366, 371, true);
	BowRenderer->CreateAnimation("RightDown_Run", "Bow.png", 0.08f, 398, 403, true);
	BowRenderer->CreateAnimation("LeftDown_Run", "Bow.png", 0.08f, 430, 435, true);
	BowRenderer->CreateAnimation("LeftUp_Run", "Bow.png", 0.08f, 462, 467, true);
	BowRenderer->CreateAnimation("RightUp_Run", "Bow.png", 0.08f, 494, 499, true);

	// Roll Animations
	BowRenderer->CreateAnimation("Right_Roll", "Bow.png", 0.063f, 6, 11, false);
	BowRenderer->CreateAnimation("Up_Roll", "Bow.png", 0.063f, 38, 43, false);
	BowRenderer->CreateAnimation("Left_Roll", "Bow.png", 0.063f, 70, 75, false);
	BowRenderer->CreateAnimation("Down_Roll", "Bow.png", 0.063f, 102, 107, false);
	BowRenderer->CreateAnimation("RightDown_Roll", "Bow.png", 0.063f, 134, 139, false);
	BowRenderer->CreateAnimation("LeftDown_Roll", "Bow.png", 0.063f, 166, 171, false);
	BowRenderer->CreateAnimation("LeftUp_Roll", "Bow.png", 0.063f, 198, 203, false);
	BowRenderer->CreateAnimation("RightUp_Roll", "Bow.png", 0.063f, 230, 235, false);

	// Death Animations
	BowRenderer->CreateAnimation("Right_Death", "Bow.png", 1.0f, 12, 12, false);
	BowRenderer->CreateAnimation("Up_Death", "Bow.png", 1.0f, 44, 44, false);
	BowRenderer->CreateAnimation("Left_Death", "Bow.png", 1.0f, 76, 76, false);
	BowRenderer->CreateAnimation("Down_Death", "Bow.png", 1.0f, 108, 108, false);
	BowRenderer->CreateAnimation("RightDown_Death", "Bow.png", 1.0f, 140, 140, false);
	BowRenderer->CreateAnimation("LeftDown_Death", "Bow.png", 1.0f, 172, 172, false);
	BowRenderer->CreateAnimation("LeftUp_Death", "Bow.png", 1.0f, 204, 204, false);
	BowRenderer->CreateAnimation("RightUp_Death", "Bow.png", 1.0f, 236, 236, false);

	// Spawn Animations
	BowRenderer->CreateAnimation("Spawn", "Bow.png", 0.15f, 79, 88, true);
}

void Player::CreateArrowInBagAnimation()
{
	// Load "Arrow.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Arrow.png", "Resource\\Texture\\PlayerElement\\");

	ArrowInBagRenderer = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Player);
	ArrowInBagRenderer->SetSprite("arrow.png");
	ArrowInBagRenderer->SetImageScale(PlayerSize);

	// Idle Animations
	ArrowInBagRenderer->CreateAnimation("Right_Idle", "Arrow.png", 1.0f, 0, 0, false);
	ArrowInBagRenderer->CreateAnimation("Up_Idle", "Arrow.png", 1.0f, 32, 32, false);
	ArrowInBagRenderer->CreateAnimation("Left_Idle", "Arrow.png", 1.0f, 64, 64, false);
	ArrowInBagRenderer->CreateAnimation("Down_Idle", "Arrow.png", 1.0f, 96, 96, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Idle", "Arrow.png", 1.0f, 128, 128, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Idle", "Arrow.png", 1.0f, 160, 160, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Idle", "Arrow.png", 1.0f, 192, 192, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Idle", "Arrow.png", 1.0f, 224, 224, false);

	// Walk Animations
	ArrowInBagRenderer->CreateAnimation("Right_Walk", "Arrow.png", 0.1f, 0, 5, true);
	ArrowInBagRenderer->CreateAnimation("Up_Walk", "Arrow.png", 0.1f, 32, 37, true);
	ArrowInBagRenderer->CreateAnimation("Left_Walk", "Arrow.png", 0.1f, 64, 69, true);
	ArrowInBagRenderer->CreateAnimation("Down_Walk", "Arrow.png", 0.1f, 96, 101, true);
	ArrowInBagRenderer->CreateAnimation("RightDown_Walk", "Arrow.png", 0.1f, 128, 133, true);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Walk", "Arrow.png", 0.1f, 160, 165, true);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Walk", "Arrow.png", 0.1f, 192, 197, true);
	ArrowInBagRenderer->CreateAnimation("RightUp_Walk", "Arrow.png", 0.1f, 224, 229, true);

	// Run Animations
	ArrowInBagRenderer->CreateAnimation("Right_Run", "Arrow.png", 0.08f, 270, 275, true);
	ArrowInBagRenderer->CreateAnimation("Up_Run", "Arrow.png", 0.08f, 302, 307, true);
	ArrowInBagRenderer->CreateAnimation("Left_Run", "Arrow.png", 0.08f, 334, 339, true);
	ArrowInBagRenderer->CreateAnimation("Down_Run", "Arrow.png", 0.08f, 366, 371, true);
	ArrowInBagRenderer->CreateAnimation("RightDown_Run", "Arrow.png", 0.08f, 398, 403, true);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Run", "Arrow.png", 0.08f, 430, 435, true);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Run", "Arrow.png", 0.08f, 462, 467, true);
	ArrowInBagRenderer->CreateAnimation("RightUp_Run", "Arrow.png", 0.08f, 494, 499, true);

	// Roll Animations
	ArrowInBagRenderer->CreateAnimation("Right_Roll", "Arrow.png", 0.063f, 6, 11, false);
	ArrowInBagRenderer->CreateAnimation("Up_Roll", "Arrow.png", 0.063f, 38, 43, false);
	ArrowInBagRenderer->CreateAnimation("Left_Roll", "Arrow.png", 0.063f, 70, 75, false);
	ArrowInBagRenderer->CreateAnimation("Down_Roll", "Arrow.png", 0.063f, 102, 107, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Roll", "Arrow.png", 0.063f, 134, 139, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Roll", "Arrow.png", 0.063f, 166, 171, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Roll", "Arrow.png", 0.063f, 198, 203, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Roll", "Arrow.png", 0.063f, 230, 235, false);

	// Death Animations
	ArrowInBagRenderer->CreateAnimation("Right_Death", "Arrow.png", 1.0f, 12, 12, false);
	ArrowInBagRenderer->CreateAnimation("Up_Death", "Arrow.png", 1.0f, 44, 44, false);
	ArrowInBagRenderer->CreateAnimation("Left_Death", "Arrow.png", 1.0f, 76, 76, false);
	ArrowInBagRenderer->CreateAnimation("Down_Death", "Arrow.png", 1.0f, 108, 108, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Death", "Arrow.png", 1.0f, 140, 140, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Death", "Arrow.png", 1.0f, 172, 172, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Death", "Arrow.png", 1.0f, 204, 204, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Death", "Arrow.png", 1.0f, 236, 236, false);

	// Spawn Animations
	ArrowInBagRenderer->CreateAnimation("Spawn", "Arrow.png", 0.15f, 79, 88, true);
}
