#pragma once

enum class HAND_STATE
{
	NONE,
	Sleep,
	Hide,
	Hover,
	Fall,
	Land,
};

enum class HAND_DIR
{
	NONE,
	Left,
	Right
};

class Hand : public BossBase
{
public:
	// Constructor Destructor
	Hand();
	~Hand();

	// Delete Function
	Hand(const Hand& _Other) = delete;
	Hand(Hand&& _Other) noexcept = delete;
	Hand& operator=(const Hand& _Other) = delete;
	Hand& operator=(Hand&& _Other) noexcept = delete;

	void Init(HAND_DIR _Dir);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

private:
	HAND_STATE CurState = HAND_STATE::NONE;
	HAND_DIR CurDir = HAND_DIR::NONE;

	void ChangeState(HAND_STATE _State);
	void SleepStart();
	void HideStart();
	void HoverStart();
	void FallStart();
	void LandStart();

	void SleepUpdate(float _Delta);
	void HideUpdate(float _Delta);
	void HoverUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void LandUpdate(float _Delta);
};