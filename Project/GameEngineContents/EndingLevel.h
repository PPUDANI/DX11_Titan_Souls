#pragma once

class EndingLevel : public LevelBase
{
public:
	// Constructor Destructor
	EndingLevel();
	~EndingLevel();

	// Delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<FadeImage> TitanSoulsRogo = nullptr;

	std::shared_ptr<AncientScript> EndingText = nullptr;
};