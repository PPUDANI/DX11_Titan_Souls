#pragma once

class Jam : public PlayLevelBase
{
public:
	// Constructor Destructor
	Jam();
	~Jam();

	// Delete Function
	Jam(const Jam& _Other) = delete;
	Jam(Jam&& _Other) noexcept = delete;
	Jam& operator=(const Jam& _Other) = delete;
	Jam& operator=(Jam&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void SpawnPlayer(GameEngineLevel* _PrevLevel) override;
};