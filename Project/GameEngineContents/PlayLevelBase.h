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
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _PrevLevel) override;


	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class Arrow> ArrowActor = nullptr;

	std::shared_ptr<class FadeIn> FadeInActor = nullptr;
	std::shared_ptr<class FadeOut> FadeOutActor = nullptr;

	// TileMap
	std::shared_ptr<class TileMap> TileMapActor;

	virtual void SpawnPlayer(GameEngineLevel* _PrevLevel) {}
	virtual void SpawnBoss() {}

	void CreatePlayerElement();
	void CursorDirRotation();
	void ArrowDirRotation();
	
private:
	
};