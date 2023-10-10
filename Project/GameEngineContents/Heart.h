#pragma once

enum class HEART_STATE
{
	InSludge,
	Idle,
	Jump,
	Fall,
	Landing,
};

class Heart : public GameEngineActor
{
public:
	// Constructor Destructor
	Heart();
	~Heart();

	// Delete Function
	Heart(const Heart& _Other) = delete;
	Heart(Heart&& _Other) noexcept = delete;
	Heart& operator=(const Heart& _Other) = delete;
	Heart& operator=(Heart&& _Other) noexcept = delete;

	void ChangeState(HEART_STATE _State);
protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void InSludgeStart();
	void IdleStart();
	void JumpStart();
	void FallStart();
	void LandingStart();

	void InSludgeUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void FallUpdate(float _Delta);

	void LandingUpdate(float _Delta);


	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

private:
	// State
	HEART_STATE CurState;
	float JumpCooldown = 0.0f;
private:
	
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 1000.0f;
	float4 GravityDir = float4::UP;
	float StartYPos = 0.0f;

};