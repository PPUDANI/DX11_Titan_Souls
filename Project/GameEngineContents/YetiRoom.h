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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void SpawnPlayer(GameEngineLevel* _PrevLevel) override;

private:
	std::shared_ptr<class TriggerBox> EnterTheFloor1 = nullptr;
	void Floor1TriggerFunc();

	// Overlay
	std::shared_ptr<class ScreenOverlay> ScreenOverlayActor = nullptr;

	// Fade
	std::shared_ptr<class FadeIn> FadeInByKillBoss = nullptr;

};