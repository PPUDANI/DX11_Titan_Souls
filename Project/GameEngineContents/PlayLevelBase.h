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

	bool PlayerIsDeath()
	{
		return PlayerIsDeathValue;
	}

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
	virtual void SpawnTriggerBox() {}
	virtual void ReleaseTriggerBox() {}

	void CreatePlayerElement();
	void CursorDirRotation();
	void ArrowDirRotation();
	
	void EnterRoomTriggerFunc();
	void ExitRoomTriggerFunc();

	virtual void SoundLoad() {};

	void ReleaseBossName();


	void PlayerDeathProcessing(float _Delta);
	bool PlayerIsDeathValue = false;
	float DeathProcessingStartTime = 2.0f;
	float DeathProcessingStartTimer = 0.0f;

protected:
	bool BossIsDeath = false;
	static bool SludgeIsDeath;
	static bool YetiIsDeath;
	static bool ColossusIsDeath;

	bool SoundIsLoaded = false;
	
protected:
	// PostEffect
	std::shared_ptr<class PlayerMaskEffect> PlayerEffect = nullptr;

public:
	// Particle
	void CreateDust(const float4& _Pos, float _Dir);
	std::shared_ptr<class UpParticle> UpParticleActor = nullptr;
	GameEngineRandom Inst;
	int RandomSeedCount = 0;

	void ReleaseParticle();
};