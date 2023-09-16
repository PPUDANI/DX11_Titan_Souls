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

	void CreatePlayerElement();

	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class Arrow> ArrowActor = nullptr;
	std::shared_ptr<class TestMap> Map = nullptr; // �ӽ� ��

	// TileMap
	std::shared_ptr<class TileMap> TileMapActor;
private:
	
};