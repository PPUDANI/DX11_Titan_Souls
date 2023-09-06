#pragma once

class GolIathRoom : public GameEngineLevel
{
public:
	// Constructor Destructor
	GolIathRoom();
	~GolIathRoom();

	// Delete Function
	GolIathRoom(const GolIathRoom& _Other) = delete;
	GolIathRoom(GolIathRoom&& _Other) noexcept = delete;
	GolIathRoom& operator=(const GolIathRoom& _Other) = delete;
	GolIathRoom& operator=(GolIathRoom&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};