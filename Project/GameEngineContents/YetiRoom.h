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

	void SpawnSnowBall(const float4& _StartPos, const float4& _Angle, RENDERING_ORDER _Order);
	void SpawnIcicle(const float4& _FirstStartPos, const float4& _Angle);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void SpawnPlayer(GameEngineLevel* _PrevLevel) override;
	void SpawnBoss() override;
	void SpawnTriggerBox() override;
	void ReleaseTriggerBox() override;


	void ReleaseBoss();
	void ReleaseSnowball();
	void ReleaseIcicle();
	void OutputBossName();
	void ReleaseBossName();

private:
	// Yeti
	std::shared_ptr<class Yeti> YetiActor = nullptr;
	std::shared_ptr<class Snowball> SnowballActor = nullptr;
	std::shared_ptr<class Icicle> IcicleActor = nullptr;


private:
	std::shared_ptr<class TriggerBox> EnterTheFloor1 = nullptr;
	void Floor1TriggerFunc();

	// Overlay
	// std::shared_ptr<class ScreenOverlay> ScreenOverlayActor = nullptr;

	// Fade
	std::shared_ptr<class FadeIn> FadeInByKillBoss = nullptr;

private:
	void BossStateUpdate();

	void BossDeathProcessing();
	void BossWakeUpProcessing();

	bool BossDeathPrecessingIsEnd = false;
	bool WakeUpProcessingIsEnd = false;

private:
	void SoundLoad() override;

private:
	bool StartProcessingIsEnd = false;
	void StartProcessing();

public:
	void CreateSnowParticle(const float4& _Pos, float _Dir, float _Range, int _Num);

	std::shared_ptr<class GravityParticle> GravityParticleActor = nullptr;
	void CreateIcicleParticle(const float4& _Pos, int _Num);

	std::shared_ptr<class SpreadParticle> SpreadParticleActor = nullptr;
	void CreateSpreadSnowParticle(const float4& _Pos, float _LiveTime, float MinSpeed, float MaxSpeed, int _Num);
};