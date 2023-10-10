#pragma once

enum class UPDATE_ORDER
{
	Map,
	Player,
	Monster,
	UI,
};

enum class RENDERING_ORDER
{
	BGMap,
	BGAMap,
	WALLMap,
	COLMap,
	MATMap,
	Shadow,

	Monster,
	Monster2,

	Arrow,
	Player,
	Arrow2,

	FGMap,
	UI,
};

enum class COLLISION_TYPE
{
	Player,
	Arrow,
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
