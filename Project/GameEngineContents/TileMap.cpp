#include "PreCompile.h"
#include "TileMap.h"
#include <vector>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::TileMapInit(int _IndexX, int _IndexY, std::string_view _TextureName)
{
	IndexX = _IndexX;
	IndexY = _IndexY;

	TextureName = _TextureName;
	TextureIndex.assign(IndexX * IndexY, 0);
	Tiles.assign(IndexX * IndexY, nullptr);
}

void TileMap::SetTileTexture()
{
	if (TextureName.empty())
	{
		MsgBoxAssert("타일맵의 텍스처를 지정해주지 않았습니다.");
	}
	
	for (int y = 0; y < IndexY; y++)
	{
		for (int x = 0; x < IndexX; x++)
		{
			int CurIndex = (IndexX * y) + x;
			Tiles[CurIndex] = CreateComponent<GameEngineSpriteRenderer>(RENDERING_ORDER::Map);
			Tiles[CurIndex]->SetSprite(TextureName, TextureIndex[CurIndex]);
			Tiles[CurIndex]->SetImageScale({ 32.0f, 32.0f });
			Tiles[CurIndex]->Transform.SetLocalPosition({x * 32.0f , y * -32.0f });
		}
		
		// 자리 세팅 해줘야함
	}
}

void TileMap::Start()
{

}

void TileMap::Update(float _Delta)
{

}