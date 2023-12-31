#pragma once

class SludgeHeartRoom : public PlayLevelBase
{
public:
	// Constructor Destructor
	SludgeHeartRoom();
	~SludgeHeartRoom();

	// Delete Function
	SludgeHeartRoom(const SludgeHeartRoom& _Other) = delete;
	SludgeHeartRoom(SludgeHeartRoom&& _Other) noexcept = delete;
	SludgeHeartRoom& operator=(const SludgeHeartRoom& _Other) = delete;
	SludgeHeartRoom& operator=(SludgeHeartRoom&& _Other) noexcept = delete;

	void SpawnDividedSludge(int _DividedCount, float4 _SpawnPos);

protected:

private:
	// Inheritance function
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	// Inheritance function
	void SpawnBoss() override;
	void SpawnPlayer(GameEngineLevel* _PrevLevel) override;
	void SpawnTriggerBox() override;

	void ReleaseBoss();
	void ReleaseSludges();
	void PutTheHeartInSludge();
	void OutputBossName();
	void ReleaseTriggerBox() override; 

private:
	// Boss Eliment
	std::list<std::shared_ptr<class Sludge>> Sludges;
	std::shared_ptr<class Sludge> SludgeActor = nullptr;
	std::shared_ptr<class Heart> HeartActor = nullptr;

	void BossStateUpdate();

	bool BossDeathPrecessingIsEnd = false;
	bool BossFirstHitPrecessingIsEnd = false;
	void BossDeathProcessing();

private:
	// TriggerBox
	std::shared_ptr<class TriggerBox> EnterTheFloor1 = nullptr;
	void Floor1TriggerFunc();

	// Overlay
	std::shared_ptr<class ScreenOverlay> ScreenOverlayActor = nullptr;

private:
	void SoundLoad() override;

private:
	bool StartProcessingIsEnd = false;
	void StartProcessing();
}; 