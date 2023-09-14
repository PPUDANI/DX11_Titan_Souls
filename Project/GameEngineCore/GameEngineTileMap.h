#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSpriteRenderer.h"

class Tile 
{
public:
	SpriteData Data;
	int Index = -1;
};

class CreateTileParameter
{
public:
	size_t TileCountX = 10;
	size_t TileCountY = 10;
	float4 TileScale = {50, 50};
	std::string_view SpriteName = "";
};


class SetTileParameterIndex
{
public:
	size_t X = -1;
	size_t Y = -1;
	unsigned int Index = 0;
	std::string_view SpriteName = "";
};

class SetTileParameterPos
{
public:
	float4 Pos;
	unsigned int Index = 0;
	std::string_view SpriteName = "";

	SetTileParameterPos(float4 _Pos, unsigned int _Index = 0, std::string_view _SpriteName = "")
		: Pos(_Pos), Index(_Index), SpriteName(_SpriteName)
	{
	}
};

// ���� :
class GameEngineTileMap : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineTileMap();
	~GameEngineTileMap();

	// delete Function
	GameEngineTileMap(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap(GameEngineTileMap&& _Other) noexcept = delete;
	GameEngineTileMap& operator=(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap& operator=(GameEngineTileMap&& _Other) noexcept = delete;

	//                       100           100            50 50 
	void CreateTileMap(const CreateTileParameter& _Parameter);
	// void SetTile(size_t _TileCountX, size_t _TileCountY, float4 TileScale);

	//size_t X;
	//size_t Y;
	//unsigned int Index = 0;
	//std::string_view SpriteName = "";
	void SetTileIndex(const SetTileParameterIndex& _Parameter);

	void SetTilePos(const SetTileParameterPos& _Parameter);

	void SetSamplerState(SamplerOption _Option);

	void SetTileOverRender(SamplerOption _Option);

	void ExpandRenderedTileMap(int _Size)
	{
		TileMapExpansionSize = _Size;
	}

protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	CreateTileParameter TileData;

	std::shared_ptr<GameEngineSprite> DefaultSprite;

	std::vector<std::vector<Tile>> Tiles;

	std::shared_ptr<class GameEngineSampler> Sampler;

	int TileMapExpansionSize = 0;
};

