#pragma once
enum class VIEW_MODE
{
	DEFAULT_MODE,
	COLLISION_MODE,
	MATERIAL_MODE1,
	MATERIAL_MODE2
};

enum class TILE_TYPE
{
	BG, // Background
	BGA, // background Animation
	FG, // Foreground
	WALL, // Wall
	COL, // Collision
	TCOL, // Triangle Collision 
	ACOL, // Air Collision (Movable Arrow Only)
	MAT // Material
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

	bool AllColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer);
	bool ColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer);
	bool TriangleColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer);
	bool AirColCheck(float4 _Pos, COLLISION_TYPE& _TypeBuffer);

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
	std::vector<std::shared_ptr<class GameEngineTileMap>> TCOLTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> ACOLTileMaps;
	std::vector<std::shared_ptr<class GameEngineTileMap>> MATTileMaps;

	std::vector<std::vector<std::vector<int>>> BGTileMapInfos;
	std::vector<std::vector<std::vector<int>>> BGATileMapInfos;
	std::vector<std::vector<std::vector<int>>> FGTileMapInfos;
	std::vector<std::vector<std::vector<int>>> WALLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> COLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> TCOLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> ACOLTileMapInfos;
	std::vector<std::vector<std::vector<int>>> MATTileMapInfos;

	//std::shared_ptr<class GameEngineTileMap> BGTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> BGATileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> FGTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COLTileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COL2TileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> COLATileMap = nullptr;
	//std::shared_ptr<class GameEngineTileMap> MATTileMap = nullptr;

	VIEW_MODE CurMode = VIEW_MODE::DEFAULT_MODE;
};