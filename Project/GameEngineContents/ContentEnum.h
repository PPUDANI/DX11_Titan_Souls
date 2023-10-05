#pragma once

enum class UPDATE_ORDER
{
	Map,
	Player,
	UI,
};

enum class RENDERING_ORDER
{
	BGMap,
	BGAMap,
	WALLMap,
	COLMap,
	MATMap,
	ArrowBack,
	Player,
	Arrow,
	FGMap,
	UI,
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
