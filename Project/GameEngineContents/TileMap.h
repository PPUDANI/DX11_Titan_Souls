#pragma once

enum class TILE_TYPE
{
	BG,
	BGA,
	FG,
	WALL,
	COL,
	COLA,
	MAT
};

enum class VIEW_MODE
{
	DEFAULT_MODE,
	COLLISION_MODE,
	MATERIAL_MODE1,
	MATERIAL_MODE2
};

class TileMap : public GameEngineActor
{
public:
	// Constructor Destructor
	TileMap();
	~TileMap();

	// Delete Function
	TileMap(const TileMap& _Other) = delete;
	TileMap(TileMap&& _Other) noexcept = delete;
	TileMap& operator=(const TileMap& _Other) = delete;
	TileMap& operator=(TileMap&& _Other) noexcept = delete;

	void BaseSetting(int _IndexX, int _IndexY, std::string_view _FolderName, std::string_view _SpriteName);
	void CreateTileMap(TILE_TYPE _Type, std::string_view _FileName);
	void TileTexureSetting();

	void SetViewMode(VIEW_MODE _Mode);

	bool ColCheck(float4 _Pos);
	
protected:

private:
	// override
	void Start() override;
	void Update(float _Delta) override;

private:

	GameEnginePath FolderPath;
	std::string FolderPathString = "";
	std::string SpriteName = "";

	unsigned int IndexX = 0;
	unsigned int IndexY = 0;

	std::vector<std::shared_ptr<class GameEngineTileMap>> BGTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> BGATileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> FGTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> WALLTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> COLTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> COLATileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> MATTileMaps;

	std::vector<std::vector<std::vector<int>>> BGTileMapInfos;
	std::vector<std::vector<std::vector<int>>> BGATileMapInfos;
	std::vector<std::vector<std::vector<int>>> FGTileMapInfos;
	std::vector<std::vector<std::vector<int>>> WALLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> COLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> COLATileMapInfos;
	std::vector<std::vector<std::vector<int>>> MATTileMapInfos;

	//std::shared_ptr<class GameEngineTileMap> BGTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> BGATileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> FGTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COLTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COL2TileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COLATileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> MATTileMap = nullptr;

	std::vector<std::vector<class TileInfo>> TileMapInfo;

	VIEW_MODE CurMode = VIEW_MODE::DEFAULT_MODE;
};