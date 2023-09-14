#include "PreCompile.h"
#include "TileMap.h"

#include <GameEngineCore/GameEngineTileMap.h>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::Start()
{
	FolderPath.MoveParentToExistsChild("Resource");
	FolderPath.MoveChild("Resource\\TileMapData");

}

void TileMap::Update(float _Delta)
{

}

void TileMap::Init(int _IndexX, int _IndexY, std::string_view _FolderName, std::string_view _SpriteName)
{
	FolderPath.MoveChild(_FolderName);
	IndexX = _IndexX;
	IndexY = _IndexY;
	SpriteName = _SpriteName;
	
	MapDataSetting();
	TileTexureSetting();
}


void TileMap::MapDataSetting()
{
	FILE* File = nullptr;

	TileMapInfo.assign(IndexY, std::vector<TileInfo>(IndexX));


	// BackGround Load
	fopen_s(&File, FolderPath.PlusFilePath("BG.tmd").c_str(), "rb");
	if (nullptr == File)
	{
		MsgBoxAssert("BG.tmd 파일을 열지 못했습니다.")
	}
	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&TileMapInfo[y][x].BG_Index, sizeof(unsigned int), 1, File);
			if (0 != TileMapInfo[y][x].BG_Index)
			{
				TileMapInfo[y][x].BG_Index -= 1;
			}
		}
	}
	fclose(File);

	// BackGround Animation Load
	fopen_s(&File, FolderPath.PlusFilePath("BGA.tmd").c_str(), "rb");
	if (nullptr == File)
	{
		MsgBoxAssert("BGA.tmd 파일을 열지 못했습니다.")
	}
	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&TileMapInfo[y][x].BGA_Index, sizeof(unsigned int), 1, File);
			if (0 != TileMapInfo[y][x].BGA_Index)
			{
				TileMapInfo[y][x].BGA_Index -= 1;
			}
		}
	}
	fclose(File);

	// ForeGround Load
	fopen_s(&File, FolderPath.PlusFilePath("FG.tmd").c_str(), "rb");
	if (nullptr == File)
	{
		MsgBoxAssert("FG.tmd 파일을 열지 못했습니다.")
	}
	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&TileMapInfo[y][x].FG_Index, sizeof(unsigned int), 1, File);
			if (0 != TileMapInfo[y][x].FG_Index)
			{
				TileMapInfo[y][x].FG_Index -= 1;
			}
		}
	}
	fclose(File);

	// Collision Load
	fopen_s(&File, FolderPath.PlusFilePath("COL.tmd").c_str(), "rb");
	if (nullptr == File)
	{
		MsgBoxAssert("COL.tmd 파일을 열지 못했습니다.")
	}
	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&TileMapInfo[y][x].COL_Index, sizeof(unsigned int), 1, File);
			if (0 != TileMapInfo[y][x].COL_Index)
			{
				TileMapInfo[y][x].COL_Index -= 4096;
			}
		}
	}
	fclose(File);

	// Material Load
	fopen_s(&File, FolderPath.PlusFilePath("MAT.tmd").c_str(), "rb");
	if (nullptr == File)
	{
		MsgBoxAssert("MAT.tmd 파일을 열지 못했습니다.")
	}
	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&TileMapInfo[y][x].MAT_Index, sizeof(unsigned int), 1, File);
			if (0 != TileMapInfo[y][x].MAT_Index)
			{
				TileMapInfo[y][x].MAT_Index -= 4096;
			}
		}
	}
	fclose(File);
}

void TileMap::TileTexureSetting()
{
	BGTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGMap);
	BGTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	BGTileMap->SetSamplerState(SamplerOption::POINT);

	//BGATileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGAMap);
	//BGATileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	//BGATileMap->SetSamplerState(SamplerOption::POINT);

	//FGTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::FGMap);
	//FGTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	//FGTileMap->SetSamplerState(SamplerOption::POINT);

	//COLTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGMap);
	//COLTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
	//COLTileMap->SetSamplerState(SamplerOption::POINT);

	//MATTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGMap);
	//MATTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
	//MATTileMap->SetSamplerState(SamplerOption::POINT);


	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			BGTileMap->SetTileIndex({ x, y, TileMapInfo[y][x].BG_Index, SpriteName});

			//if (0 == TileMapInfo[y][x].BGA_Index)
			//{
			//	BGATileMap->SetTileIndex({ x, y, TileMapInfo[y][x].BGA_Index, "util.png"});
			//}
			//else
			//{
			//	BGATileMap->SetTileIndex({ x, y, TileMapInfo[y][x].BGA_Index, SpriteName });
			//}
			//
			//if (0 == TileMapInfo[y][x].FG_Index)
			//{
			//	FGTileMap->SetTileIndex({ x, y, TileMapInfo[y][x].FG_Index, "util.png" });
			//}
			//else
			//{
			//	FGTileMap->SetTileIndex({ x, y, TileMapInfo[y][x].FG_Index, SpriteName });
			//}

			//COLTileMap->SetTileIndex({ x, y, TileMapInfo[y][x].COL_Index, "Spectiles.png" });
			//MATTileMap->SetTileIndex({ x, y, TileMapInfo[y][x].MAT_Index, "Spectiles.png" });
		}
	}

}
