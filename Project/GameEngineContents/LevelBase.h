#pragma once

class LevelBase : public GameEngineLevel
{
public:
	// Constructor Destructor
	LevelBase();
	~LevelBase();

	// Delete Function
	LevelBase(const LevelBase& _Other) = delete;
	LevelBase(LevelBase&& _Other) noexcept = delete;
	LevelBase& operator=(const LevelBase& _Other) = delete;
	LevelBase& operator=(LevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class MouseCursor> Cursor = nullptr;

};