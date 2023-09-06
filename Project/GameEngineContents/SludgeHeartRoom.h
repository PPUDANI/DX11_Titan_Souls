#pragma once

class SludgeHeartRoom : public GameEngineLevel
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
};