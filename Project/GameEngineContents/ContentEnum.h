#pragma once

enum class UPDATE_ORDER
{
	Map,
	TriggerBox,
	Boss,
	Arrow,
	Player,
	UI,
};

enum class RENDERING_ORDER
{
	BG_Tile,
	COL_Tile,
	MAT_Tile,
	BGA_Tile,
	WALL_Tile,
	Shadow,

	Y_SORT_ENTITY_BACK,
	Y_SORT_ENTITY,
	Y_SORT_ENTITY_FRONT,

	Overlay,
	FG_Tile,

	UI_BACK,
	UI,
	UI_FRONT,
	UI_FRONT2,
};

//enum class RENDERING_ORDER
//{
//	AlphaLess,
//
//	HasAlpah,
//	Shadow,
//	PressMark,
//	Sludge,
//};

enum class COLLISION_TYPE
{
	Player,
	PlayerDir,
	GetArrow,
	AttackArrow,
	Weakness,
	BossBody,
	BossBodyAttack,
	Snowball,
	Icicle,
	DetectionRange,
	EventPlace,
};

enum class TILE_COLLISION_TYPE
{
	EMPTY = 0,
	RECT = 252,
	LEFTUP_TRIANGLE = 224,
	RIGHTUP_TRIANGLE = 225,
	LEFTDOWN_TRIANGLE = 226,
	RIGHTDOWN_TRIANGLE = 227,
};

enum class FadeColor
{
	Black,
	White,
};
