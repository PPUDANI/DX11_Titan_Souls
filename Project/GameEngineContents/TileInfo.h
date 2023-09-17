#pragma once

enum class MATERIAL_TYPE
{
	EMPTY = 0,
	GRASS = 1,
	SNOW = 8,
	ROCK = 14,
	TILE = 12,
	TILE_IN_WATER = 3,
	WATER = 19,

	LEFTUP_STAIRS = 48,
	RIGHTUP_STAIRS = 49,
	UP_STAIRS = 52,

	BIDIRECTIONAL_VINE = 51,
};

class TileInfo
{
public:
	static TileInfo DefaultInfo;

	int BG_Index = 0;
	int BGA_Index = 0;
	int FG_Index = 0;
	int COL_Index = 0;
	int MAT_Index = 0;
};
