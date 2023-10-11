#include "PreCompile.h"
#include "Player.h"


void Player::CreatePlayerbodyAnimation()
{
	// Load "Player.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Player.png", "Resource\\Texture\\PlayerElement\\");

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BodyRenderer->Transform.AddLocalPosition(DepthValue::TempValue);
	BodyRenderer->SetImageScale(GlobalValue::StandardTextureScale);

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

	// Rolling Animations
	BodyRenderer->CreateAnimation("Right_Rolling", "Player.png", 0.07f, 6, 11, true);
	BodyRenderer->CreateAnimation("Up_Rolling", "Player.png", 0.07f, 38, 43, true);
	BodyRenderer->CreateAnimation("Left_Rolling", "Player.png", 0.07f, 70, 75, true);
	BodyRenderer->CreateAnimation("Down_Rolling", "Player.png", 0.07f, 102, 107, true);
	BodyRenderer->CreateAnimation("RightDown_Rolling", "Player.png", 0.07f, 134, 139, true);
	BodyRenderer->CreateAnimation("LeftDown_Rolling", "Player.png", 0.07f, 166, 171, true);
	BodyRenderer->CreateAnimation("LeftUp_Rolling", "Player.png", 0.07f, 198, 203, true);
	BodyRenderer->CreateAnimation("RightUp_Rolling", "Player.png", 0.07f, 230, 235, true);

	//// RollingBlocked Animations
	//BodyRenderer->CreateAnimation("Right_RollingBlocked", "Player.png", 0.07f, 11, 6, false);
	//BodyRenderer->CreateAnimation("Up_RollingBlocked", "Player.png", 0.07f, 43, 38, false);
	//BodyRenderer->CreateAnimation("Left_RollingBlocked", "Player.png", 0.07f, 75, 70, false);
	//BodyRenderer->CreateAnimation("Down_RollingBlocked", "Player.png", 0.07f, 107, 102, false);
	//BodyRenderer->CreateAnimation("RightDown_RollingBlocked", "Player.png", 0.07f, 139, 134, false);
	//BodyRenderer->CreateAnimation("LeftDown_RollingBlocked", "Player.png", 0.07f, 171, 166, false);
	//BodyRenderer->CreateAnimation("LeftUp_RollingBlocked", "Player.png", 0.07f, 203, 198, false);
	//BodyRenderer->CreateAnimation("RightUp_RollingBlocked", "Player.png", 0.07f, 235, 230, false);

	// Bolcked Animations
	BodyRenderer->CreateAnimation("Right_Blocked", "Player.png", 0.1f, 264, 269, true);
	BodyRenderer->CreateAnimation("Up_Blocked", "Player.png", 0.1f, 296, 301, true);
	BodyRenderer->CreateAnimation("Left_Blocked", "Player.png", 0.1f, 328, 333, true);
	BodyRenderer->CreateAnimation("Down_Blocked", "Player.png", 0.1f, 360, 365, true);
	BodyRenderer->CreateAnimation("RightDown_Blocked", "Player.png", 0.1f, 392, 397, true);
	BodyRenderer->CreateAnimation("LeftDown_Blocked", "Player.png", 0.1f, 424, 429, true);
	BodyRenderer->CreateAnimation("LeftUp_Blocked", "Player.png", 0.1f, 456, 461, true);
	BodyRenderer->CreateAnimation("RightUp_Blocked", "Player.png", 0.1f, 488, 493, true);

	// Death Animations
	BodyRenderer->CreateAnimation("Right_Death", "Player.png", 1.0f, 12, 12, false);
	BodyRenderer->CreateAnimation("Up_Death", "Player.png", 1.0f, 44, 44, false);
	BodyRenderer->CreateAnimation("Left_Death", "Player.png", 1.0f, 76, 76, false);
	BodyRenderer->CreateAnimation("Down_Death", "Player.png", 1.0f, 108, 108, false);
	BodyRenderer->CreateAnimation("RightDown_Death", "Player.png", 1.0f, 140, 140, false);
	BodyRenderer->CreateAnimation("LeftDown_Death", "Player.png", 1.0f, 172, 172, false);
	BodyRenderer->CreateAnimation("LeftUp_Death", "Player.png", 1.0f, 204, 204, false);
	BodyRenderer->CreateAnimation("RightUp_Death", "Player.png", 1.0f, 236, 236, false);

	// Aim Animations
	BodyRenderer->CreateAnimation("Right_Aim", "Player.png", 1.0f, 13, 13, false);
	BodyRenderer->CreateAnimation("Up_Aim", "Player.png", 1.0f, 45, 45, false);
	BodyRenderer->CreateAnimation("Left_Aim", "Player.png", 1.0f, 77, 77, false);
	BodyRenderer->CreateAnimation("Down_Aim", "Player.png", 1.0f, 109, 109, false);
	BodyRenderer->CreateAnimation("RightDown_Aim", "Player.png", 1.0f, 141, 141, false);
	BodyRenderer->CreateAnimation("LeftDown_Aim", "Player.png", 1.0f, 173, 173, false);
	BodyRenderer->CreateAnimation("LeftUp_Aim", "Player.png", 1.0f, 205, 205, false);
	BodyRenderer->CreateAnimation("RightUp_Aim", "Player.png", 1.0f, 237, 237, false);

	// Returning Animations
	BodyRenderer->CreateAnimation("Right_Returning", "Player.png", 1.0f, 14, 14, false);
	BodyRenderer->CreateAnimation("Up_Returning", "Player.png", 1.0f, 46, 46, false);
	BodyRenderer->CreateAnimation("Left_Returning", "Player.png", 1.0f, 78, 78, false);
	BodyRenderer->CreateAnimation("Down_Returning", "Player.png", 1.0f, 110, 110, false);
	BodyRenderer->CreateAnimation("RightDown_Returning", "Player.png", 1.0f, 142, 142, false);
	BodyRenderer->CreateAnimation("LeftDown_Returning", "Player.png", 1.0f, 174, 174, false);
	BodyRenderer->CreateAnimation("LeftUp_Returning", "Player.png", 1.0f, 206, 206, false);
	BodyRenderer->CreateAnimation("RightUp_Returning", "Player.png", 1.0f, 238, 238, false);

	// StandUp Animations
	BodyRenderer->CreateAnimation("StandUp", "Player.png", 0.10f, 79, 88, true);
}

void Player::CreateBowAnimation()
{
	// Load "Bow.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Bow.png", "Resource\\Texture\\PlayerElement\\");

	BowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BowRenderer->Transform.AddLocalPosition(DepthValue::TempValue);
	BowRenderer->SetImageScale(GlobalValue::StandardTextureScale);

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

	// Rolling Animations
	BowRenderer->CreateAnimation("Right_Rolling", "Bow.png", 0.07f, 6, 11, true);
	BowRenderer->CreateAnimation("Up_Rolling", "Bow.png", 0.07f, 38, 43, true);
	BowRenderer->CreateAnimation("Left_Rolling", "Bow.png", 0.07f, 70, 75, true);
	BowRenderer->CreateAnimation("Down_Rolling", "Bow.png", 0.07f, 102, 107, true);
	BowRenderer->CreateAnimation("RightDown_Rolling", "Bow.png", 0.07f, 134, 139, true);
	BowRenderer->CreateAnimation("LeftDown_Rolling", "Bow.png", 0.07f, 166, 171, true);
	BowRenderer->CreateAnimation("LeftUp_Rolling", "Bow.png", 0.07f, 198, 203, true);
	BowRenderer->CreateAnimation("RightUp_Rolling", "Bow.png", 0.07f, 230, 235, true);

	//// RollingBlocked Animations
	//BowRenderer->CreateAnimation("Right_RollingBlocked", "Bow.png", 0.07f, 11, 6, false);
	//BowRenderer->CreateAnimation("Up_RollingBlocked", "Bow.png", 0.07f, 43, 38, false);
	//BowRenderer->CreateAnimation("Left_RollingBlocked", "Bow.png", 0.07f, 75, 70, false);
	//BowRenderer->CreateAnimation("Down_RollingBlocked", "Bow.png", 0.07f, 107, 102, false);
	//BowRenderer->CreateAnimation("RightDown_RollingBlocked", "Bow.png", 0.07f, 139, 134, false);
	//BowRenderer->CreateAnimation("LeftDown_RollingBlocked", "Bow.png", 0.07f, 171, 166, false);
	//BowRenderer->CreateAnimation("LeftUp_RollingBlocked", "Bow.png", 0.07f, 203, 198, false);
	//BowRenderer->CreateAnimation("RightUp_RollingBlocked", "Bow.png", 0.07f, 235, 230, false);

	// Bolcked Animations
	BowRenderer->CreateAnimation("Right_Blocked", "Bow.png", 0.1f, 264, 269, true);
	BowRenderer->CreateAnimation("Up_Blocked", "Bow.png", 0.1f, 296, 301, true);
	BowRenderer->CreateAnimation("Left_Blocked", "Bow.png", 0.1f, 328, 333, true);
	BowRenderer->CreateAnimation("Down_Blocked", "Bow.png", 0.1f, 360, 365, true);
	BowRenderer->CreateAnimation("RightDown_Blocked", "Bow.png", 0.1f, 392, 397, true);
	BowRenderer->CreateAnimation("LeftDown_Blocked", "Bow.png", 0.1f, 424, 429, true);
	BowRenderer->CreateAnimation("LeftUp_Blocked", "Bow.png", 0.1f, 456, 461, true);
	BowRenderer->CreateAnimation("RightUp_Blocked", "Bow.png", 0.1f, 488, 493, true);

	// Death Animations
	BowRenderer->CreateAnimation("Right_Death", "Bow.png", 1.0f, 12, 12, false);
	BowRenderer->CreateAnimation("Up_Death", "Bow.png", 1.0f, 44, 44, false);
	BowRenderer->CreateAnimation("Left_Death", "Bow.png", 1.0f, 76, 76, false);
	BowRenderer->CreateAnimation("Down_Death", "Bow.png", 1.0f, 108, 108, false);
	BowRenderer->CreateAnimation("RightDown_Death", "Bow.png", 1.0f, 140, 140, false);
	BowRenderer->CreateAnimation("LeftDown_Death", "Bow.png", 1.0f, 172, 172, false);
	BowRenderer->CreateAnimation("LeftUp_Death", "Bow.png", 1.0f, 204, 204, false);
	BowRenderer->CreateAnimation("RightUp_Death", "Bow.png", 1.0f, 236, 236, false);

	// Aim Animations
	BowRenderer->CreateAnimation("Right_Aim", "Bow.png", 1.0f, 13, 13, false);
	BowRenderer->CreateAnimation("Up_Aim", "Bow.png", 1.0f, 45, 45, false);
	BowRenderer->CreateAnimation("Left_Aim", "Bow.png", 1.0f, 77, 77, false);
	BowRenderer->CreateAnimation("Down_Aim", "Bow.png", 1.0f, 109, 109, false);
	BowRenderer->CreateAnimation("RightDown_Aim", "Bow.png", 1.0f, 141, 141, false);
	BowRenderer->CreateAnimation("LeftDown_Aim", "Bow.png", 1.0f, 173, 173, false);
	BowRenderer->CreateAnimation("LeftUp_Aim", "Bow.png", 1.0f, 205, 205, false);
	BowRenderer->CreateAnimation("RightUp_Aim", "Bow.png", 1.0f, 237, 237, false);

	// Returning Animations
	BowRenderer->CreateAnimation("Right_Returning", "Bow.png", 1.0f, 14, 14, false);
	BowRenderer->CreateAnimation("Up_Returning", "Bow.png", 1.0f, 46, 46, false);
	BowRenderer->CreateAnimation("Left_Returning", "Bow.png", 1.0f, 78, 78, false);
	BowRenderer->CreateAnimation("Down_Returning", "Bow.png", 1.0f, 110, 110, false);
	BowRenderer->CreateAnimation("RightDown_Returning", "Bow.png", 1.0f, 142, 142, false);
	BowRenderer->CreateAnimation("LeftDown_Returning", "Bow.png", 1.0f, 174, 174, false);
	BowRenderer->CreateAnimation("LeftUp_Returning", "Bow.png", 1.0f, 206, 206, false);
	BowRenderer->CreateAnimation("RightUp_Returning", "Bow.png", 1.0f, 238, 238, false);

	// StandUp Animations
	BowRenderer->CreateAnimation("StandUp", "Bow.png", 0.10f, 79, 88, true);
}

void Player::CreateArrowInBagAnimation()
{
	// Load "Arrow.png" Texture
	GlobalLoad::LoadSpriteCut(32, 32, "Arrow.png", "Resource\\Texture\\PlayerElement\\");

	ArrowInBagRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ArrowInBagRenderer->Transform.AddLocalPosition(DepthValue::TempValue);
	ArrowInBagRenderer->SetImageScale(GlobalValue::StandardTextureScale);

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

	// Rolling Animations
	ArrowInBagRenderer->CreateAnimation("Right_Rolling", "Arrow.png", 0.07f, 6, 11, true);
	ArrowInBagRenderer->CreateAnimation("Up_Rolling", "Arrow.png", 0.07f, 38, 43, true);
	ArrowInBagRenderer->CreateAnimation("Left_Rolling", "Arrow.png", 0.07f, 70, 75, true);
	ArrowInBagRenderer->CreateAnimation("Down_Rolling", "Arrow.png", 0.07f, 102, 107, true);
	ArrowInBagRenderer->CreateAnimation("RightDown_Rolling", "Arrow.png", 0.07f, 134, 139, true);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Rolling", "Arrow.png", 0.07f, 166, 171, true);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Rolling", "Arrow.png", 0.07f, 198, 203, true);
	ArrowInBagRenderer->CreateAnimation("RightUp_Rolling", "Arrow.png", 0.07f, 230, 235, true);

	//// RollingBlocked Animations
	//ArrowInBagRenderer->CreateAnimation("Right_RollingBlocked", "Arrow.png", 0.07f, 11, 6, false);
	//ArrowInBagRenderer->CreateAnimation("Up_RollingBlocked", "Arrow.png", 0.07f, 43, 38, false);
	//ArrowInBagRenderer->CreateAnimation("Left_RollingBlocked", "Arrow.png", 0.07f, 75, 70, false);
	//ArrowInBagRenderer->CreateAnimation("Down_RollingBlocked", "Arrow.png", 0.07f, 107, 102, false);
	//ArrowInBagRenderer->CreateAnimation("RightDown_RollingBlocked", "Arrow.png", 0.07f, 139, 134, false);
	//ArrowInBagRenderer->CreateAnimation("LeftDown_RollingBlocked", "Arrow.png", 0.07f, 171, 166, false);
	//ArrowInBagRenderer->CreateAnimation("LeftUp_RollingBlocked", "Arrow.png", 0.07f, 203, 198, false);
	//ArrowInBagRenderer->CreateAnimation("RightUp_RollingBlocked", "Arrow.png", 0.07f, 235, 230, false);

	// Bolcked Animations
	ArrowInBagRenderer->CreateAnimation("Right_Blocked", "Arrow.png", 0.1f, 264, 269, true);
	ArrowInBagRenderer->CreateAnimation("Up_Blocked", "Arrow.png", 0.1f, 296, 301, true);
	ArrowInBagRenderer->CreateAnimation("Left_Blocked", "Arrow.png", 0.1f, 328, 333, true);
	ArrowInBagRenderer->CreateAnimation("Down_Blocked", "Arrow.png", 0.1f, 360, 365, true);
	ArrowInBagRenderer->CreateAnimation("RightDown_Blocked", "Arrow.png", 0.1f, 392, 397, true);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Blocked", "Arrow.png", 0.1f, 424, 429, true);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Blocked", "Arrow.png", 0.1f, 456, 461, true);
	ArrowInBagRenderer->CreateAnimation("RightUp_Blocked", "Arrow.png", 0.1f, 488, 493, true);

	// Death Animations
	ArrowInBagRenderer->CreateAnimation("Right_Death", "Arrow.png", 1.0f, 12, 12, false);
	ArrowInBagRenderer->CreateAnimation("Up_Death", "Arrow.png", 1.0f, 44, 44, false);
	ArrowInBagRenderer->CreateAnimation("Left_Death", "Arrow.png", 1.0f, 76, 76, false);
	ArrowInBagRenderer->CreateAnimation("Down_Death", "Arrow.png", 1.0f, 108, 108, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Death", "Arrow.png", 1.0f, 140, 140, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Death", "Arrow.png", 1.0f, 172, 172, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Death", "Arrow.png", 1.0f, 204, 204, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Death", "Arrow.png", 1.0f, 236, 236, false);

	// Aim Animations
	ArrowInBagRenderer->CreateAnimation("Right_Aim", "Arrow.png", 1.0f, 13, 13, false);
	ArrowInBagRenderer->CreateAnimation("Up_Aim", "Arrow.png", 1.0f, 45, 45, false);
	ArrowInBagRenderer->CreateAnimation("Left_Aim", "Arrow.png", 1.0f, 77, 77, false);
	ArrowInBagRenderer->CreateAnimation("Down_Aim", "Arrow.png", 1.0f, 109, 109, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Aim", "Arrow.png", 1.0f, 141, 141, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Aim", "Arrow.png", 1.0f, 173, 173, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Aim", "Arrow.png", 1.0f, 205, 205, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Aim", "Arrow.png", 1.0f, 237, 237, false);

	// Returning Animations
	ArrowInBagRenderer->CreateAnimation("Right_Returning", "Arrow.png", 1.0f, 14, 14, false);
	ArrowInBagRenderer->CreateAnimation("Up_Returning", "Arrow.png", 1.0f, 46, 46, false);
	ArrowInBagRenderer->CreateAnimation("Left_Returning", "Arrow.png", 1.0f, 78, 78, false);
	ArrowInBagRenderer->CreateAnimation("Down_Returning", "Arrow.png", 1.0f, 110, 110, false);
	ArrowInBagRenderer->CreateAnimation("RightDown_Returning", "Arrow.png", 1.0f, 142, 142, false);
	ArrowInBagRenderer->CreateAnimation("LeftDown_Returning", "Arrow.png", 1.0f, 174, 174, false);
	ArrowInBagRenderer->CreateAnimation("LeftUp_Returning", "Arrow.png", 1.0f, 206, 206, false);
	ArrowInBagRenderer->CreateAnimation("RightUp_Returning", "Arrow.png", 1.0f, 238, 238, false);

	// StandUp Animations
	ArrowInBagRenderer->CreateAnimation("StandUp", "Arrow.png", 0.10f, 79, 88, true);
}
