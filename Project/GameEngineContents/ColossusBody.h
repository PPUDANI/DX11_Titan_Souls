#pragma once

enum class BODY_STATE
{
	NONE,
	Sleep,
	WkaeUp,
	Idle,
	Hit,
	Death,
};

class ColossusBody : public GameEngineActor
{
public:
	// Constructor Destructor
	ColossusBody();
	~ColossusBody();

	// Delete Function
	ColossusBody(const ColossusBody& _Other) = delete;
	ColossusBody(ColossusBody&& _Other) noexcept = delete;
	ColossusBody& operator=(const ColossusBody& _Other) = delete;
	ColossusBody& operator=(ColossusBody&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr; 
	std::shared_ptr<GameEngineSpriteRenderer> HeadRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RightShoulderRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LeftShoulderRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;
private:
	BODY_STATE CurState = BODY_STATE::NONE;

	void SleepStart();
	void WkaeUpStart();
	void IdleStart();
	void HitStart();
	void DeathStart();

	void SleepUpdate(float _Delta);
	void WkaeUpUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);
};