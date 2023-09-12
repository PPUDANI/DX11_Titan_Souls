#pragma once

class PlayLevelBase: public GameEngineLevel
{
public:
	// Constructor Destructor
	PlayLevelBase();
	~PlayLevelBase();

	// Delete Function
	PlayLevelBase(const PlayLevelBase& _Other) = delete;
	PlayLevelBase(PlayLevelBase&& _Other) noexcept = delete;
	PlayLevelBase& operator=(const PlayLevelBase& _Other) = delete;
	PlayLevelBase& operator=(PlayLevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _PrevLevel) override;

	void CreatePlayer();

	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class TestMap> Map = nullptr; // юс╫ц ╦й

	// TileMap
	std::shared_ptr<class TileMap> BGMap = nullptr;
	std::shared_ptr<class TileMap> BGAMap = nullptr;
	std::shared_ptr<class TileMap> FGMap = nullptr;
	std::shared_ptr<class TileMap> COLMap = nullptr;
	std::shared_ptr<class TileMap> MATMap = nullptr;

private:

};