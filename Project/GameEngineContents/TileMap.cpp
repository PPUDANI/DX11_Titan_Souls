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

void TileMap::BaseSetting(int _IndexX, int _IndexY, std::string_view _FolderName, std::string_view _SpriteName)
{
	FolderPath.MoveChild(_FolderName);
	IndexX = _IndexX;
	IndexY = _IndexY;
	SpriteName = _SpriteName;
	
}

void TileMap::CreateTileMap(TILE_TYPE _Type, std::string_view _FileName)
{
	FILE* File = nullptr;

	std::vector<std::vector<int>> Info;
	Info.assign(IndexY, std::vector<int>(IndexX, 0));

	// Load

	fopen_s(&File, FolderPath.PlusFilePath(_FileName).c_str(), "rb");

	if (nullptr == File)
	{
		return;
	}
	
	// 현재 제작한 엔진 구조의 Sprite Data Index 시작값은 0이다.
	// 하지만 분석한 타일의 TextureIndex 시작값이 1이므로 수정이 필요하다.
	// 받아온 정보들을 전부 1만큼 빼주는데 Info가 음수가 될 가능성이 있다.
	// 만약 음수일 경우 출력 되지 않게 했다.

	int Nomalizer = 1;

	// 타일 데이터 중 Collision, Material은 TextureIndex 시작값이 4097이다.
    // 타일의 정보 아틀라스가 16X16으로 따로 저장되어 있기 때문에 엔진 구조상 4097을 빼주어 표준화 하였다.
	// 마찬가지로 음수일 경우 출력되지 않는다.

	if (TILE_TYPE::COL == _Type ||
		TILE_TYPE::COLA == _Type || 
		TILE_TYPE::MAT == _Type)
	{
		Nomalizer = 4097;
	}

	for (unsigned int y = 0; y < IndexY; ++y)
	{
		for (unsigned int x = 0; x < IndexX; ++x)
		{
			fread(&Info[y][x], sizeof(int), 1, File);
			Info[y][x] -= Nomalizer;
		}
	}

	fclose(File);

	switch (_Type)
	{
	case TILE_TYPE::BG:
		BGTileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::BGA:
		BGATileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::FG:
		FGTileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::WALL:
		WALLTileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::COL:
		COLTileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::COLA:
		COLATileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::MAT:
		MATTileMapInfos.push_back(Info);
		break;
	default:
		break;
	}
}


void TileMap::SetViewMode(VIEW_MODE _Mode)
{
	switch (_Mode)
	{
	case VIEW_MODE::DEFAULT_MODE:
		for (size_t i = 0; i < BGTileMaps.size(); i++)
		{
			BGTileMaps[i]->On();
		}
		for (size_t i = 0; i < BGATileMaps.size(); i++)
		{
			BGATileMaps[i]->On();
		}
		for (size_t i = 0; i < WALLTileMaps.size(); i++)
		{
			WALLTileMaps[i]->On();
		}
		for (size_t i = 0; i < FGTileMaps.size(); i++)
		{
			FGTileMaps[i]->On();
		}
		for (size_t i = 0; i < COLTileMaps.size(); i++)
		{
			COLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < COLATileMaps.size(); i++)
		{
			COLATileMaps[i]->Off();
		}
		for (size_t i = 0; i < MATTileMaps.size(); i++)
		{
			MATTileMaps[i]->Off();
		}
		break;

	case VIEW_MODE::COLLISION_MODE:
		for (size_t i = 0; i < BGTileMaps.size(); i++)
		{
			BGTileMaps[i]->Off();
		}
		for (size_t i = 0; i < BGATileMaps.size(); i++)
		{
			BGATileMaps[i]->Off();
		}
		for (size_t i = 0; i < WALLTileMaps.size(); i++)
		{
			WALLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < FGTileMaps.size(); i++)
		{
			FGTileMaps[i]->Off();
		}
		for (size_t i = 0; i < COLTileMaps.size(); i++)
		{
			COLTileMaps[i]->On();
		}
		for (size_t i = 0; i < COLATileMaps.size(); i++)
		{
			COLATileMaps[i]->On();
		}
		for (size_t i = 0; i < MATTileMaps.size(); i++)
		{
			MATTileMaps[i]->Off();
		}

		break;
	case VIEW_MODE::MATERIAL_MODE1:
		for (size_t i = 0; i < BGTileMaps.size(); i++)
		{
			BGTileMaps[i]->On();
		}
		for (size_t i = 0; i < BGATileMaps.size(); i++)
		{
			BGATileMaps[i]->On();
		}
		for (size_t i = 0; i < WALLTileMaps.size(); i++)
		{
			WALLTileMaps[i]->On();
		}
		for (size_t i = 0; i < FGTileMaps.size(); i++)
		{
			FGTileMaps[i]->On();
		}
		for (size_t i = 0; i < COLTileMaps.size(); i++)
		{
			COLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < COLATileMaps.size(); i++)
		{
			COLATileMaps[i]->Off();
		}
		for (size_t i = 0; i < MATTileMaps.size(); i++)
		{
			MATTileMaps[i]->On();
		}
		break;

	case VIEW_MODE::MATERIAL_MODE2:
		for (size_t i = 0; i < BGTileMaps.size(); i++)
		{
			BGTileMaps[i]->Off();
		}
		for (size_t i = 0; i < BGATileMaps.size(); i++)
		{
			BGATileMaps[i]->On();
		}
		for (size_t i = 0; i < WALLTileMaps.size(); i++)
		{
			WALLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < FGTileMaps.size(); i++)
		{
			FGTileMaps[i]->Off();
		}
		for (size_t i = 0; i < COLTileMaps.size(); i++)
		{
			COLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < COLATileMaps.size(); i++)
		{
			COLATileMaps[i]->Off();
		}
		for (size_t i = 0; i < MATTileMaps.size(); i++)
		{
			MATTileMaps[i]->Off();
		}

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
	std::string Path = FolderPathString;
	Path += "\\BG.tmd";
	fopen_s(&File, Path.c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].BG_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].BG_Index -= 1;
			}
		}
	}
	fclose(File);

	// BackGround Animation Load
	fopen_s(&File, FolderPath.PlusFilePath("BGA.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].BGA_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].BGA_Index -= 1;
			}
		}
	}
	fclose(File);

	// ForeGround Load
	fopen_s(&File, FolderPath.PlusFilePath("FG.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].FG_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].FG_Index -= 1;
			}
		}
	}
	fclose(File);

	// Collision Load
	fopen_s(&File, FolderPath.PlusFilePath("COL.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].COL_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].COL_Index -= 4097;
			}
		}
	}
	fclose(File);

	// Collision Load
	fopen_s(&File, FolderPath.PlusFilePath("COL2.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].COL2_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].COL2_Index -= 4097;
			}
		}
	}
	fclose(File);

	// Collision Load
	fopen_s(&File, FolderPath.PlusFilePath("COLA.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].COLA_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].COLA_Index -= 4097;
			}
		}
	}
	fclose(File);

	// Material Load
	fopen_s(&File, FolderPath.PlusFilePath("MAT.tmd").c_str(), "rb");
	if (nullptr != File)
	{
		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				fread(&TileMapInfo[y][x].MAT_Index, sizeof(int), 1, File);
				TileMapInfo[y][x].MAT_Index -= 4097;
			}
		}
	}
	fclose(File);
}

void TileMap::TileTexureSetting()
{
	// Background Create & Texture Setting
	for (int i = 0; i < BGTileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= BGTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(BGTileMapInfos[i][y][x]), SpriteName });
				}
			}
		}
		NewTileMap->Off();
		BGTileMaps.push_back(NewTileMap);
	}

	// Background Animation Create & Texture Setting
	for (int i = 0; i < BGATileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::BGAMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= BGATileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(BGATileMapInfos[i][y][x]), SpriteName});
				}
			}
		}
		NewTileMap->Off();
		BGATileMaps.push_back(NewTileMap);
	}

	// Foreground Create & Texture Setting
	for (int i = 0; i < FGTileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::FGMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= FGTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(FGTileMapInfos[i][y][x]), SpriteName });
				}
			}
		}
		NewTileMap->Off();
		FGTileMaps.push_back(NewTileMap);
	}

	// Wall Create & Texture Setting
	for (int i = 0; i < WALLTileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::WALLMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, SpriteName });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= WALLTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(WALLTileMapInfos[i][y][x]), SpriteName });
				}
			}
		}
		NewTileMap->Off();
		WALLTileMaps.push_back(NewTileMap);
	}

	// Collision Create & Texture Setting
	for (int i = 0; i < COLTileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::COLMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= COLTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(COLTileMapInfos[i][y][x]), "Spectiles.png" });
				}
			}
		}
		NewTileMap->Off();
		COLTileMaps.push_back(NewTileMap);
	}

	// Collision Air Create & Texture Setting
	for (int i = 0; i < COLATileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::COLMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= COLATileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(COLATileMapInfos[i][y][x]), "Spectiles.png" });
				}
			}
		}
		NewTileMap->Off();
		COLATileMaps.push_back(NewTileMap);
	}

	// Material Create & Texture Setting
	for (int i = 0; i < MATTileMapInfos.size(); ++i)
	{
		std::shared_ptr<GameEngineTileMap> NewTileMap;

		NewTileMap = CreateComponent<GameEngineTileMap>(RENDERING_ORDER::MATMap);
		NewTileMap->CreateTileMap({ IndexX, IndexY, GlobalValue::StandardTextureScale, "Spectiles.png" });
		NewTileMap->SetSamplerState(SAMPLER_OBJECT::POINT);
		NewTileMap->ExpandRenderedTileMap(3);

		for (unsigned int y = 0; y < IndexY; ++y)
		{
			for (unsigned int x = 0; x < IndexX; ++x)
			{
				if (0 <= MATTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(MATTileMapInfos[i][y][x]), "Spectiles.png" });
				}
			}
		}
		NewTileMap->Off();
		MATTileMaps.push_back(NewTileMap);
	}


	/*for (unsigned int y = 0; y < IndexY; ++y)
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

			if (0 <= TileMapInfo[y][x].COL2_Index)
			{
				COL2TileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].COL2_Index), "Spectiles.png" });
			}

			if (0 <= TileMapInfo[y][x].COLA_Index)
			{
				COLATileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].COLA_Index), "Spectiles.png" });
			}

			if (0 <= TileMapInfo[y][x].MAT_Index)
			{
				MATTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TileMapInfo[y][x].MAT_Index), "Spectiles.png" });
			}
		}
	}*/
}

bool TileMap::ColCheck(float4 _Pos)
{
	//float4 Index = COLTileMap->PosToIndex(_Pos);
	//Index.Y = -Index.Y;

	//int Xsize = static_cast<int>(TileMapInfo[0].size());
	//int Ysize = static_cast<int>(TileMapInfo.size());

	//if (Xsize < Index.iX() ||
	//	0 > Index.iX())
	//{
	//	return false;
	//}
	//else if(Ysize < Index.iY() ||
	//	    0 > Index.iY())
	//{
	//	return false;
	//}

	//int ColIndex = TileMapInfo[Index.iY()][Index.iX()].COL_Index;

	//if (252 == ColIndex)
	//{
	//	return true;
	//}
	//else
	{
		return false;
	}
}