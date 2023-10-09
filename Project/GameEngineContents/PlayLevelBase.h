#pragma once

class PlayLevelBase: public LevelBase
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
	virtual void Start() override;
	virtual void Update(float _Delta) override;
	virtual void LevelStart(GameEngineLevel* _PrevLevel) override;
	virtual void LevelEnd(GameEngineLevel* _PrevLevel) override;


	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class Arrow> ArrowActor = nullptr;

	// TileMap
	std::shared_ptr<class TileMap> TileMapActor;

	void CreatePlayerElement();
	void SpawnPlayer();
	void CursorDirRotation();
	void ArrowDirRotation();

	float4 PlayerSpawnPos = float4::ZERO;
private:
	
};