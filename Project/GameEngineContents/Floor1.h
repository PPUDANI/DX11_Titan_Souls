#pragma once

enum class ATTACKHAND_DIR
{
	NONE,
	Left,
	Right
};

class Floor1 : public PlayLevelBase
{
public:
	// Constructor Destructor
	Floor1();
	~Floor1();

	// Delete Function
	Floor1(const Floor1& _Other) = delete;
	Floor1(Floor1&& _Other) noexcept = delete;
	Floor1& operator=(const Floor1& _Other) = delete;
	Floor1& operator=(Floor1&& _Other) noexcept = delete;

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
private:
	// TriggerBox
	std::shared_ptr<class TriggerBox> EnterTheSludgeRoom = nullptr;
	void StaySludgeRoomTriggerFunc();

	std::shared_ptr<class TriggerBox> EnterTheYetiRoom = nullptr;
	void StayYetiRoomTriggerFunc();

	std::shared_ptr<class TriggerBox> EnterTheColossusRoom = nullptr;
	void EnterColossusRoomTriggerFunc();

	std::shared_ptr<class TriggerBox> GameEndPlace = nullptr;
	void OpenDoorFunc();

	std::shared_ptr<class EndingDoor> EndingDoorActor = nullptr;

	// OverlayActor
	std::shared_ptr<class OverlayActor> SludgeRoomEntranceOverlayActor = nullptr;
	std::shared_ptr<class OverlayActor> YetiRoomEntranceOverlayActor = nullptr;

	std::shared_ptr<class ClearLight> SludgeClearLight = nullptr;
	std::shared_ptr<class ClearLight> YetiClearLight = nullptr;
	std::shared_ptr<class ClearLight> ColossusClearLight = nullptr;

private:
	std::shared_ptr<class ColossusBody> BossBodyActor = nullptr;

	std::shared_ptr<class Hand> LeftHandActor = nullptr;
	std::shared_ptr<class Hand> RightHandActor = nullptr;

	std::shared_ptr<class TriggerBox> LeftHandPlayerDetectionRange = nullptr;
	std::shared_ptr<class TriggerBox> RightHandPlayerDetectionRange = nullptr;

	void EnterLeftDetectionRange();
	void EnterRightDetectionRange();

	void SwitchToAttackModeLeftHand();
	void SwitchToAttackModeRightHand();

	ATTACKHAND_DIR AttackDir = ATTACKHAND_DIR::NONE;

private:
	void SoundLoad() override;

	bool StartProcessingIsEnd = false;
	void StartProcessing();

	bool BossPageIsFight = false;
	void BossPageProcessing();

	void OutputBossName();
	void BossStateUpdate();

	bool ShowtingProcessingIsEnd = false;
	bool BossHitProcessingIsEnd = false;
	void BossHitProcessing();

	void BossDeathProcessing();
	void BossDeathCheck();
	bool AllBossClear = false;
};