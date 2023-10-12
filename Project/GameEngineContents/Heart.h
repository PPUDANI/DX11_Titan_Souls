#pragma once

enum class HEART_STATE
{
	InSludge,
	Idle,
	Jump,
	Fall,
	Landing,
};

class Heart : public ActorBase
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

	void SetMoveDirBasis(float4& _MoveAngle)
	{
		HeartMoveDirBasis = _MoveAngle;
	}

private:
	// Virtual function
	void Start() override;
	void Update(float _Delta) override;

	// Component
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;


private:
	// State
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

private:
	// State
	HEART_STATE CurState;
	float JumpCooldown = 0.0f;

private:
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 900.0f;
	float4 GravityDir = float4::UP;
	float JumpStartYPos = 0.0f;
private:
	// Move
	float4 HeartMoveDirBasis = float4::ZERO;
	float MoveSpeed = 100.0f;
	
	void MoveToPlayer(float _Delta);

	float4 RenderPos = float4::ZERO;
};