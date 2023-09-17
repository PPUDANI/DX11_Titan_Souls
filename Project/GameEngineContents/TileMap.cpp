#include "PreCompile.h"
#include "TileMap.h"

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
	SetViewMode(VIEW_MODE::DEFAULT_MODE);
}

void TileMap::SetViewMode(VIEW_MODE _Mode)
{
	switch (_Mode)
	{
	case VIEW_MODE::DEFAULT_MODE:
		BGTileMap->On();
		BGATileMap->On();
		FGTileMap->On();
		COLTileMap->Off();
		MATTileMap->Off();
		break;
	case VIEW_MODE::COLLISION_MODE:
		BGTileMap->Off();
		BGATileMap->Off();
		FGTileMap->Off();
		COLTileMap->On();
		MATTileMap->Off();
		break;
	case VIEW_MODE::MATERIAL_MODE1:
		BGTileMap->On();
		BGATileMap->Off();
		FGTileMap->Off();
		COLTileMap->Off();
		MATTileMap->On();
		break;
	case VIEW_MODE::MATERIAL_MODE2:
		BGTileMap->On();
		BGATileMap->Off();
		FGTileMap->On();
		COLTileMap->Off();
		MATTileMap->On();
		break;
	default:
		break;
	}
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
			fread(&TileMapInfo[y][x].BG_Index, sizeof(int), 1, File);
			TileMapInfo[y][x].BG_Index -= 1;
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
			fread(&TileMapInfo[y][x].BGA_Index, sizeof(int), 1, File);
			TileMapInfo[y][x].BGA_Index -= 1;
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
			fread(&TileMapInfo[y][x].FG_Index, sizeof(int), 1, File);
			TileMapInfo[y][x].FG_Index -= 1;
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
			fread(&TileMapInfo[y][x].COL_Index, sizeof(int), 1, File);
			TileMapInfo[y][x].COL_Index -= 4097;
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
			fread(&TileMapInfo[y][x].MAT_Index, sizeof(int), 1, File);
			TileMapInfo[y][x].MAT_Index -= 4097;
		}
	}
	fclose(File);
}

void TileMap::TileTexureSetting()
{
	BGTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGMap);
	BGTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	BGTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
	BGTileMap->ExpandRenderedTileMap(3);

	BGATileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGAMap);
	BGATileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	BGATileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
	BGATileMap->ExpandRenderedTileMap(3);

	FGTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::FGMap);
	FGTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
	FGTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
	FGTileMap->ExpandRenderedTileMap(3);

	COLTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::COLMap);
	COLTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
	COLTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
	COLTileMap->ExpandRenderedTileMap(3);

	MATTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::MATMap);
	MATTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
	MATTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
	MATTileMap->ExpandRenderedTileMap(3);

	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			if (0 <= TileMapInfo[y][x].BG_Index)
			{
				BGTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].BG_Index), SpriteName });
			}

			if (0 <= TileMapInfo[y][x].BGA_Index)
			{
				BGATileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].BGA_Index), SpriteName });
			}

			if (0 <= TileMapInfo[y][x].FG_Index)
			{
				FGTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].FG_Index), SpriteName });
			}

			if (0 <= TileMapInfo[y][x].COL_Index)
			{
				COLTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].COL_Index), "Spectiles.png" });
			}
			
			if (0 <= TileMapInfo[y][x].MAT_Index)
			{
				MATTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].MAT_Index), "Spectiles.png" });
			}
		}
	}
}

bool TileMap::ColCheck(float4 _Pos)
{
	float4 Index = COLTileMap->PosToIndex(_Pos);
	Index.Y = -Index.Y;

	int Xsize = TileMapInfo[0].size();
	int Ysize = TileMapInfo.size();

	if (Xsize < Index.iX() ||
		0 > Index.iX())
	{
		return false;
	}
	else if(Ysize < Index.iY() ||
		    0 > Index.iY())
	{
		return false;
	}



	int ColIndex = TileMapInfo[Index.iY()][Index.iX()].COL_Index;

	if (252 == ColIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}