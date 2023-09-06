#pragma once

class GollathRoom : public GameEngineLevel
{
public:
	// Constructor Destructor
	GollathRoom();
	~GollathRoom();

	// Delete Function
	GollathRoom(const GollathRoom& _Other) = delete;
	GollathRoom(GollathRoom&& _Other) noexcept = delete;
	GollathRoom& operator=(const GollathRoom& _Other) = delete;
	GollathRoom& operator=(GollathRoom&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};