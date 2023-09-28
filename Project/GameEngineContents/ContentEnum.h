#pragma once

enum class UPDATE_ORDER
{
	Map,
	Player,
};

enum class RENDERING_ORDER
{
	BGMap,
	BGAMap,
	WALLMap,
	COLMap,
	MATMap,
	Player,
	Arrow,
	FGMap,
};

enum class COLLISION_TYPE
{
	EMPTY = 0,
	RECT = 252,
	LEFTUP_TRIANGLE = 224,
	RIGHTUP_TRIANGLE = 225,
	LEFTDOWN_TRIANGLE = 226,
	RIGHTDOWN_TRIANGLE = 227,
};
