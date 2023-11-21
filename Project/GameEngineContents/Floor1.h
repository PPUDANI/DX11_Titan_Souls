#pragma once

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

private:
	// TriggerBox
	std::shared_ptr<class TriggerBox> EnterTheSludgeRoom = nullptr;
	void SludgeRoomStayTriggerFunc();

	std::shared_ptr<class TriggerBox> EnterTheYetiRoom = nullptr;
	void YetiRoomStayTriggerFunc();

	// OverlayActor
	std::shared_ptr<class OverlayActor> SludgeRoomEntranceOverlayActor = nullptr;
	std::shared_ptr<class OverlayActor> YetiRoomEntranceOverlayActor = nullptr;

	// PostEffect
	std::shared_ptr<class PlayerMaskEffect> PlayerEffect = nullptr;

private:
	std::shared_ptr<class Hand> LeftHandActor = nullptr;
	std::shared_ptr<class Hand> RightHandActor = nullptr;

	std::shared_ptr<class TriggerBox> LeftHandPlayerDetectionRange = nullptr;
	std::shared_ptr<class TriggerBox> RightHandPlayerDetectionRange = nullptr;

	void EnterLeftDetectionRange();
	void EnterRightDetectionRange();

	void ExitLeftDetectionRange();
	void ExitRightDetectionRange();

	bool LeftIsDetected = false;
	bool RightIsDetected = false;

private:
	void SoundLoad() override;
};