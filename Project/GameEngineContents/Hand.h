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
	friend class ColossusBody;
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
	void ChangeState(HAND_STATE _State);

	static inline bool ModeSwitchIsAble()
	{
		return ModeSwitchIsAbleValue;
	}

	static bool AttackModeIsSwitch;

private:
	static bool ModeSwitchIsAbleValue;

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
	
	void CollisionOn()
	{
		Collision->On();
		AttackCollision->On();
	}

	void CollisionOff()
	{
		Collision->Off();
		AttackCollision->Off();
	}

private:
	HAND_STATE CurState = HAND_STATE::NONE;
	HAND_STATE PrevState = HAND_STATE::NONE;
	HAND_DIR CurDir = HAND_DIR::NONE;


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

private:
	float MaxHeight = 180.0f;
	float MinHeignt = 10.0f;
	float CurHeignt = 0.0f;

private:
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 0.0f;
	float4 GravityDir = float4::UP;

private:
	float MoveRatio = 0.0f;
	float MoveSpeed = 0.0f;
	float4 FloorCheckPos = float4::ZERO;

	void MoveToPlayer(float _Delta, const float4& _StartPos);

private:
	float HoverCoolTime = 1.0f;
	float HoverTimer = 0.0f;

private:
	float LandCoolTime = 0.75f;
	float LandTimer = 0.0f;

private:
	static const float4 HidePos;
	//float4 MaxHoverRotation = { 0.0f, 0.0f, 20.0f };
	//float4 MinHoverRotation = { 0.0f, 0.0f, 0.0f };
	//float4 CurHoverRotation = { 0.0f, 0.0f, 0.0f };
};