#pragma once

class YetiRoom : public PlayLevelBase
{
public:
	// Constructor Destructor
	YetiRoom();
	~YetiRoom();

	// Delete Function
	YetiRoom(const YetiRoom& _Other) = delete;
	YetiRoom(YetiRoom&& _Other) noexcept = delete;
	YetiRoom& operator=(const YetiRoom& _Other) = delete;
	YetiRoom& operator=(YetiRoom&& _Other) noexcept = delete;

	void SpawnSnowBall(const float4& _StartPos, const float4& _Angle);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void SpawnPlayer(GameEngineLevel* _PrevLevel) override;
	void SpawnBoss() override;


	void OutputBossName();
	void ReleaseBossName();

private:
	void ReleaseBossEliment();

	// Yeti
	std::shared_ptr<class Yeti> YetiActor = nullptr;
	std::shared_ptr<class Snowball> SnowballActor = nullptr;

private:
	std::shared_ptr<class TriggerBox> EnterTheFloor1 = nullptr;
	void Floor1TriggerFunc();

	// Overlay
	std::shared_ptr<class ScreenOverlay> ScreenOverlayActor = nullptr;

	// Fade
	std::shared_ptr<class FadeIn> FadeInByKillBoss = nullptr;

private:
	bool BossIsDeath = false;
	bool BossDeathPrecessingIsEnd = false;
	void BossDeathProcessing();
	void BossWakeUpProcessing();

	bool WakeUpProcessingIsEnd = false;
};