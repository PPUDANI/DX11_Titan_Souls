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
	void Init();


protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::vector<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>> Tiles;
	std::vector<std::vector<TileInfo>> MapInfo;
};