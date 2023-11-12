#pragma once

enum class SLUDGE_STATE
{
	Increase,
	Decrease
};

class Sludge : public JumpBoss
{
public:
	// Constructor Destructor
	Sludge();
	~Sludge();

	// Delete Function
	Sludge(const Sludge& _Other) = delete;
	Sludge(Sludge&& _Other) noexcept = delete;
	Sludge& operator=(const Sludge& _Other) = delete;
	Sludge& operator=(Sludge&& _Other) noexcept = delete;

	inline void SetHeart(class Heart* _HeartPtr)
	{
		HeartActor = _HeartPtr;
	}

	void DividedSludgeInit(int _DividedCount);

private:
	class Heart* HeartActor = nullptr;
private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

	float4 RenderScale = { 256.0f, 256.0f, 1.0f };
	float4 ShadowRenderScale = { 128.0f, 128.0f , 1.0f };

	float MaxScale = 0.0f;
	float MinScale = 0.0f;
	float ExpandDefalutSpeed = 192.0f;

	float LerpRange = 0.0f;

	float4 HeartPos = float4::ZERO;

private:
	void RendererSetting();
	void SetByDivided();
private:
	// State
	void IdleStart() override;
	void JumpStart() override;
	void FallStart() override;
	void LandingStart() override;

	void DivisionStart() override;

	void IdleUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;
	void LandingUpdate(float _Delta) override;
	void DivisionUpdate(float _Delta) override;

	bool IsDivision = false;
	bool DivisionEnd = false;
	int DividedCount = 0;
	float DecreaseSize = 0.25f;
	float IncreaseMoveSpeed = 30.0f;
	float IncreaseGravityForce = 200.0f;

	float4 DefaultRenderPosBase = { 0.0f, -64.0f, 1.0f };
	float4 DefaultCollisionSizeBase = { 200.0f, 100.0f, 1.0f };
	float4 DefaultDetectionRangeSize = { 800.0f, 500.0f, 1.0f };

	float DefaultMoveSpeed = 250.0f;
	float DefaultGravityForce = 1200.0f;

	bool MaxDivision = false;
	SLUDGE_STATE ExpandDir = SLUDGE_STATE::Decrease;
	EventParameter CollisionParam;

private:
	// Physics
	void DecreaseY(float _Speed);
	void IncreaseY(float _Speed);

	bool ReadyToJump = false;
	float JumpChargeTime = 0.0f;
private:
	float ScreenShakingTime = 0.0f;
	float ScreenShakingTimer = 0.0f;
	float ShakingPerFrame = 0.0f;
	bool ShakingEnd = false;
	float ShakingLerpValue = 0.0f;
};