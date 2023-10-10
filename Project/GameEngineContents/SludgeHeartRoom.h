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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<class Heart> HeartActor = nullptr;
};