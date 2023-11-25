#pragma once

enum class HAND_STATE
{
	NONE,
	Sleep,
	Hide,
	Hover,
	Fall,
	Land,
	Hit,
	Death,
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


public:
	static inline bool ModeSwitchIsAble()
	{
		return ModeSwitchIsAbleValue;
	}

	static bool AttackModeIsSwitch;

private:
	static bool ModeSwitchIsAbleValue;

public:
	void Init(HAND_DIR _Dir);
	void ChangeState(HAND_STATE _State);

	void SetBodyActor(ColossusBody* _Body)
	{
		Body = _Body;
	}

private:
	class ColossusBody* Body = nullptr;


private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
	
	void AllCollisionOn()
	{
		Collision->On();
		AttackCollision->On();
	}

	void AllCollisionOff()
	{
		Collision->Off();
		AttackCollision->Off();
	}

	void SetHideCollision()
	{
		Collision->Transform.SetLocalScale({ 80.0f, 32.0f });
		Collision->Transform.SetLocalPosition({ 0.0f, 0.0f });
		Collision->On();
		AttackCollision->Off();
	}

	void SetLandCollision()
	{
		Collision->Transform.SetLocalScale({ 64.0f, 32.0f });
		Collision->Transform.SetLocalPosition({ 0.0f, 0.0f });
		AllCollisionOn();
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
	void HitStart();
	void DeathStart();

	void SleepUpdate(float _Delta);
	void HideUpdate(float _Delta);
	void HoverUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void LandUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);

private:
	float MaxHeight = 230.0f;
	float MinHeignt = 30.0f;
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

	float4 LeftRangeCenterValue = { -200.0f, -150.0f };
	float4 RightRangeCenterValue = { 200.0f, -150.0f };

	void MoveToPlayer(float _Delta, const float4& _StartPos);

private:
	float HoverCoolTime = 1.0f;
	float HoverTimer = 0.0f;

	float LandCoolTime = 0.75f;
	float LandTimer = 0.0f;

	static const float4 HidePos;

private:
	void ChangeAnimaion(std::string_view _AnimationMane);

private:
	void HoverRotationUpdate(float _Delta);
	void FallRotationUpdate(float _Delta);
	void HoverMaxRotationValueUpdate();

	float HoverMaxRotation = 15.0f;
	float HoverRotation = 0.0f;

	float FallMaxRotation = 0.0f;

	float4 CurRotation = float4::ZERO;


	float HoverRotationSpeed = 5.0f;
	float FallRotationSpeed = 10.0f;
private:
    // Physical
	float Speed = 3.0f;
	float Radian = GameEngineMath::PI;
	float MovingHeight = 20.0f;

	void Levitaion(float _Delta);
};