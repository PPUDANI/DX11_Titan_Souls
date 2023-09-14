#pragma once

class SubTileMap : public GameEngineActor
{
public:
	// Constructor Destructor
	SubTileMap();
	~SubTileMap();

	// Delete Function
	SubTileMap(const SubTileMap& _Other) = delete;
	SubTileMap(SubTileMap&& _Other) noexcept = delete;
	SubTileMap& operator=(const TileMap& _Other) = delete;
	SubTileMap& operator=(TileMap&& _Other) noexcept = delete;

	void TileMapInit(int _IndexX, int _IndexY, std::string_view _TextureName);

	void SetTileData(std::string_view _FilePath, int _StartIndex)
	{
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild(_FilePath);

		FILE* File = nullptr;
		int Max = IndexX * IndexY;

		fopen_s(&File, FilePath.GetStringPath().c_str(), "rb");
		for (int i = 0; i < Max; i++)
		{
			fread(&TextureIndex[i], sizeof(unsigned int), 1, File);
			if (0 != TextureIndex[i])
			{
				TextureIndex[i] -= _StartIndex;
			}
		}
		fclose(File);
	}

	void SetTileTexture(RENDERING_ORDER _Order);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	unsigned int IndexX = 0;
	unsigned int IndexY = 0;

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Tiles;
	std::vector<unsigned int> TextureIndex;
	GameEnginePath FilePath;
	std::string TextureName = "";
};