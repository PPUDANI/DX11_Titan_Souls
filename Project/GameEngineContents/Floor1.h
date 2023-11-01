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
private:
	std::shared_ptr<class TriggerBox> EnterTheSludgeRoom = nullptr;
	void EnterTheSludgeRoomUpdate();
};