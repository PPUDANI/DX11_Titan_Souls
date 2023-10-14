#pragma once

enum HEART_STATE
{
	InSludge,
	Idle,
	Jump,
	Fall,
	Landing,
	Death,
};

class Heart : public BossBase
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

private:
	// Virtual function
	void Start() override;
	void Update(float _Delta) override;

private:
	// State
	void InSludgeStart();
	void IdleStart();
	void JumpStart();
	void FallStart();
	void LandingStart();
	void DeathStart();

	void InSludgeUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void DeathUpdate(float _Delta);
private:
	// State
	HEART_STATE CurState;
	float JumpCooldown = 0.0f;

private:
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 1200.0f;
	float4 GravityDir = float4::UP;

private:
	float MoveSpeed = 150.0f;
	float4 RenderPosBase = { 0.0f, 10.0f };
	float4 JumpStartPos = float4::ZERO;

	void MoveToPlayer(float _Delta);

};