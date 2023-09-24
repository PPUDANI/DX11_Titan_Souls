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
	std::vector<std::vector<int>> Info;
	Info.assign(IndexY, std::vector<int>(IndexX, 0));

	// ���� ������ ���� ������ Sprite Data Index ���۰��� 0�̴�.
	// ������ �м��� Ÿ���� TextureIndex ���۰��� 1�̹Ƿ� ������ �ʿ��ϴ�.
	// �޾ƿ� �������� ���� 1��ŭ ���ִµ� Info�� ������ �� ���ɼ��� �ִ�.
	// ���� ������ ��� ��� ���� �ʰ� �ߴ�.

	int Nomalizer = 1;

	// Ÿ�� ������ �� Collision, Material�� TextureIndex ���۰��� 4097�̴�.
    // Ÿ���� ���� ��Ʋ�󽺰� 16X16���� ���� ����Ǿ� �ֱ� ������ ���� ������ 4097�� ���־� ǥ��ȭ �Ͽ���.
	// ���������� ������ ��� ��µ��� �ʴ´�.

	if (TILE_TYPE::COL == _Type ||
		TILE_TYPE::TCOL == _Type ||
		TILE_TYPE::ACOL == _Type ||
		TILE_TYPE::MAT == _Type)
	{
		Nomalizer = 4097;
	}

	// Load
	FILE* File = nullptr;
	fopen_s(&File, FolderPath.PlusFilePath(_FileName).c_str(), "rb");

	if (nullptr == File)
	{
		return;
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
	case TILE_TYPE::TCOL:
		TCOLTileMapInfos.push_back(Info);
		break;
	case TILE_TYPE::ACOL:
		ACOLTileMapInfos.push_back(Info);
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
		for (size_t i = 0; i < TCOLTileMaps.size(); i++)
		{
			TCOLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < ACOLTileMaps.size(); i++)
		{
			ACOLTileMaps[i]->Off();
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
		for (size_t i = 0; i < TCOLTileMaps.size(); i++)
		{
			TCOLTileMaps[i]->On();
		}
		for (size_t i = 0; i < ACOLTileMaps.size(); i++)
		{
			ACOLTileMaps[i]->On();
		}
		for (size_t i = 0; i < MATTileMaps.size(); i++)
		{
			MATTileMaps[i]->Off();
		}

		break;
	case VIEW_MODE::MATERIAL_MODE1:
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
			COLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < TCOLTileMaps.size(); i++)
		{
			TCOLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < ACOLTileMaps.size(); i++)
		{
			ACOLTileMaps[i]->Off();
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
			COLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < TCOLTileMaps.size(); i++)
		{
			TCOLTileMaps[i]->Off();
		}
		for (size_t i = 0; i < ACOLTileMaps.size(); i++)
		{
			ACOLTileMaps[i]->Off();
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

void TileMap::TileTexureSetting()
{
	// Background Create & Texture Setting
	for (size_t i = 0; i < BGTileMapInfos.size(); ++i)
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
	for (size_t i = 0; i < BGATileMapInfos.size(); ++i)
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
	for (size_t i = 0; i < FGTileMapInfos.size(); ++i)
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
	for (size_t i = 0; i < WALLTileMapInfos.size(); ++i)
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
	for (size_t i = 0; i < COLTileMapInfos.size(); ++i)
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

	// Triangle Collision Create & Texture Setting
	for (size_t i = 0; i < TCOLTileMapInfos.size(); ++i)
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
				if (0 <= TCOLTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(TCOLTileMapInfos[i][y][x]), "Spectiles.png" });
				}
			}
		}
		NewTileMap->Off();
		TCOLTileMaps.push_back(NewTileMap);
	}

	// Air Collision Create & Texture Setting
	for (size_t i = 0; i < ACOLTileMapInfos.size(); ++i)
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
				if (0 <= ACOLTileMapInfos[i][y][x])
				{
					NewTileMap->SetTileIndex({ x, y, static_cast<unsigned int>(ACOLTileMapInfos[i][y][x]), "Spectiles.png" });
				}
			}
		}
		NewTileMap->Off();
		ACOLTileMaps.push_back(NewTileMap);
	}

	// Material Create & Texture Setting
	for (size_t i = 0; i < MATTileMapInfos.size(); ++i)
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
}


bool TileMap::AllColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer)
{
	if (true == ColCheck(_Pos, _TypeBuffer))
	{
		return true;
	}

	if (true == AirColCheck(_Pos, _TypeBuffer))
	{
		return true;
	}

	if (true == TriangleColCheck(_Pos, _TypeBuffer))
	{
		return true;
	}

	_TypeBuffer = COLLISION_TYPE::EMPTY;
	return false;
}

bool TileMap::ColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer)
{
	// COL Ÿ���� �ߺ��� ���� ���� ������ �߰��� return�ص� ��� ����.
	for (size_t i = 0; i < COLTileMaps.size(); ++i)
	{
		float4 CheckIndex = COLTileMaps[i]->PosToIndex(_Pos);
		CheckIndex.Y = -CheckIndex.Y;

		if (static_cast<int>(IndexX) < CheckIndex.iX() ||
			0 > CheckIndex.iX())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}
		else if (static_cast<int>(IndexY) < CheckIndex.iY() ||
			0 > CheckIndex.iY())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}

		int IndexColInfo = COLTileMapInfos[i][CheckIndex.iY()][CheckIndex.iX()];

		if (0 > IndexColInfo ||
			255 < IndexColInfo)
		{
			IndexColInfo = 0;
		}

		switch (static_cast<COLLISION_TYPE>(IndexColInfo))
		{
		case COLLISION_TYPE::EMPTY:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			break;
		case COLLISION_TYPE::RECT:
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			return true;
		default:
			MsgBoxAssert("Rect Collision����ó������ ���� Collision Type �Դϴ�.")
		}
	}
	return false;
}

bool TileMap::TriangleColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer)
{
	// COL Ÿ���� �ߺ��� ���� ���� ������ �߰��� return�ص� ��� ����.
	for (size_t i = 0; i < TCOLTileMaps.size(); ++i)
	{
		float4 CheckIndex = TCOLTileMaps[i]->PosToIndex(_Pos);
		CheckIndex.Y = -CheckIndex.Y;

		if (static_cast<int>(IndexX) < CheckIndex.iX() ||
			0 > CheckIndex.iX())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}
		else if (static_cast<int>(IndexY) < CheckIndex.iY() ||
			0 > CheckIndex.iY())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}

		int IndexColInfo = TCOLTileMapInfos[i][CheckIndex.iY()][CheckIndex.iX()];

		if (0 > IndexColInfo ||
			255 < IndexColInfo)
		{
			IndexColInfo = 0;
		}

		switch (static_cast<COLLISION_TYPE>(IndexColInfo))
		{
		case COLLISION_TYPE::EMPTY:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			break;
		case COLLISION_TYPE::LEFTUP_TRIANGLE:
		case COLLISION_TYPE::RIGHTUP_TRIANGLE:
		case COLLISION_TYPE::LEFTDOWN_TRIANGLE:
		case COLLISION_TYPE::RIGHTDOWN_TRIANGLE:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			return true;
		default:
			MsgBoxAssert("Triangle Collision���� ó������ ���� Collision Type �Դϴ�.")
		}
	}
	return false;
}

bool TileMap::AirColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer)
{
	// COL Ÿ���� �ߺ��� ���� ���� ������ �߰��� return�ص� ��� ����.
	for (size_t i = 0; i < ACOLTileMaps.size(); ++i)
	{
		float4 CheckIndex = ACOLTileMaps[i]->PosToIndex(_Pos);
		CheckIndex.Y = -CheckIndex.Y;

		if (static_cast<int>(IndexX) < CheckIndex.iX() ||
			0 > CheckIndex.iX())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}
		else if (static_cast<int>(IndexY) < CheckIndex.iY() ||
			0 > CheckIndex.iY())
		{
			_TypeBuffer = COLLISION_TYPE::EMPTY;
			return false;
		}

		int IndexColInfo = ACOLTileMapInfos[i][CheckIndex.iY()][CheckIndex.iX()];

		if (0 > IndexColInfo ||
			255 < IndexColInfo)
		{
			IndexColInfo = 0;
		}

		switch (static_cast<COLLISION_TYPE>(IndexColInfo))
		{
		case COLLISION_TYPE::EMPTY:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			break;
		case COLLISION_TYPE::RECT:
			_TypeBuffer = static_cast<COLLISION_TYPE>(IndexColInfo);
			return true;
		default:
			MsgBoxAssert("Air Collision���� ó������ ���� Collision Type �Դϴ�.")
		}
	}
	return false;
}
