#pragma once

enum class BODY_STATE
{
	NONE,
	Sleep,
	WakeUp,
	Shouting,
	Idle,
	Hit,
	Death,
};

class ColossusBody : public BossBase
{
	friend class Hand;
public:
	// Constructor Destructor
	ColossusBody();
	~ColossusBody();

	// Delete Function
	ColossusBody(const ColossusBody& _Other) = delete;
	ColossusBody(ColossusBody&& _Other) noexcept = delete;
	ColossusBody& operator=(const ColossusBody& _Other) = delete;
	ColossusBody& operator=(ColossusBody&& _Other) noexcept = delete;

	void ChangeState(BODY_STATE _State);

	BODY_STATE GetCurState() const
	{
		return CurState;
	}

	void SetLeftHand(class Hand* _Hand)
	{
		LeftHand = _Hand;
	}

	void SetRightHand(class Hand* _Hand)
	{
		RightHand = _Hand;
	}
	
private:
	void Start() override;
	void Update(float _Delta) override;

private:
	class Hand* LeftHand = nullptr;
	class Hand* RightHand = nullptr;

private:
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr; 
	std::shared_ptr<GameEngineSpriteRenderer> BodyLightRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HeadRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RightShoulderRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LeftShoulderRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	std::shared_ptr<GameEngineCollision> AttackRange = nullptr;

private:
	BODY_STATE CurState = BODY_STATE::NONE;

	void SleepStart();
	void WakeUpStart();
	void ShoutingStart();
	void IdleStart();
	void HitStart();
	void DeathStart();

	void SleepUpdate(float _Delta);
	void WakeUpUpdate(float _Delta);
	void ShoutingUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);

private:
	float CameraMoveRatio = 0.0f;
	float ZoomRatio = 1.0f;

private:
	// Physical
	float Speed = 2.0f;
	float Radian = GameEngineMath::PI / 2.0f;
	float MovingHeight = 10.0f;

	void Levitaion(float _Delta);

private:
	void SoundLoad();
};