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

private:
	// Inheritance function
	void SpawnBoss() override;
	void SpawnPlayer() override;

private:
	// Boss Eliment
	std::list<std::shared_ptr<class Sludge>> Sludges;
	std::shared_ptr<class Sludge> SludgeActor = nullptr;
	std::shared_ptr<class Heart> HeartActor = nullptr;

	bool BossIsDeath = false;
};