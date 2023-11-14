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

	// TileMap
	std::shared_ptr<class TileMap> TileMapActor;

	// Player
	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class Arrow> ArrowActor = nullptr;

	// Fade
	std::shared_ptr<class FadeIn> FadeInActor = nullptr;
	std::shared_ptr<class FadeOut> FadeOutActor = nullptr;
	std::shared_ptr<class FadeIn> BossDeathEffect = nullptr;

	// AncientScript
	std::shared_ptr<class AncientScript> BossNameScript = nullptr;
	std::shared_ptr<class AncientScript> BossDescriptionScript = nullptr;
	std::shared_ptr<class FadeImage> BossNameBack = nullptr;


	virtual void SpawnPlayer(GameEngineLevel* _PrevLevel) {}
	virtual void SpawnBoss() {}

	void CreatePlayerElement();
	void CursorDirRotation();
	void ArrowDirRotation();
	
private:

	// PostEffect
	std::shared_ptr<class PlayerMaskEffect> PlayerEffect;
};