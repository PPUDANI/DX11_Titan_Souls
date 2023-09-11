#pragma once

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

	void TileMapInit(int _IndexX, int _IndexY, std::string_view _TextureName);

	void SetTileData(std::string_view _FilePath)
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
				TextureIndex[i] -= 1;
			}
		}
		fclose(File);
	}

	void SetTileTexture();

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