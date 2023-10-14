#pragma once

enum class UPDATE_ORDER
{
	Map,
	Player,
	Boss,
	UI,
};

enum class RENDERING_ORDER
{
	AlphaLess,
	HasAlpah,
};


enum class COLLISION_TYPE
{
	Player,
	Arrow,
	Boss,
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
