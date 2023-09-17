#pragma once

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

	void Init(int _IndexX, int _IndexY, std::string_view _FolderName, std::string_view _SpriteName);
	
	void SetViewMode(VIEW_MODE _Mode);

	bool ColCheck(float4 _Pos);

protected:

private:
	// override
	void Start() override;
	void Update(float _Delta) override;

private:
	void MapDataSetting();
	void TileTexureSetting();
	GameEnginePath FolderPath;
	std::string SpriteName = "";

	unsigned int IndexX = 0;
	unsigned int IndexY = 0;

	std::shared_ptr<class GameEngineTileMap> BGTileMap = nullptr;
	std::shared_ptr<class GameEngineTileMap> BGATileMap = nullptr;
	std::shared_ptr<class GameEngineTileMap> FGTileMap = nullptr;
	std::shared_ptr<class GameEngineTileMap> COLTileMap = nullptr;
	std::shared_ptr<class GameEngineTileMap> MATTileMap = nullptr;

	std::vector<std::vector<class TileInfo>> TileMapInfo;

	VIEW_MODE CurMode = VIEW_MODE::DEFAULT_MODE;
};