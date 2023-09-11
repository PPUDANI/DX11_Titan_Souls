#pragma once
#include "PlayLevelBase.h"

class StartingRuins : public PlayLevelBase
{
public:
	// Constructor Destructor
	StartingRuins();
	~StartingRuins();

	// Delete Function
	StartingRuins(const StartingRuins& _Other) = delete;
	StartingRuins(StartingRuins&& _Other) noexcept = delete;
	StartingRuins& operator=(const StartingRuins& _Other) = delete;
	StartingRuins& operator=(StartingRuins&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<TileMap> BGMap = nullptr;
	std::shared_ptr<TileMap> FGMap = nullptr;
};