#pragma once

enum class ICICLE_STATE
{
	Falling,
	Stuck,
};

class Icicle : public BossBase
{
public:
	// Constructor Destructor
	Icicle();
	~Icicle();

	// Delete Function
	Icicle(const Icicle& _Other) = delete;
	Icicle(Icicle&& _Other) noexcept = delete;
	Icicle& operator=(const Icicle& _Other) = delete;
	Icicle& operator=(Icicle&& _Other) noexcept = delete;

	void Init(const float4& _TargetPos, const float4& _Height);

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	ICICLE_STATE CurState = ICICLE_STATE::Falling;
	void ChangeState(ICICLE_STATE _State);
	void FallingStart();
	void StuckStart();

	void FallingUpdate(float _Delta);
	void StuckUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineCollision> FallingCollision = nullptr;
	EventParameter BlockedColParam;

private:
	float4 TargetPos = float4::ZERO;
	float4 StandardHeight = float4::ZERO;

	float GravityForce = 2000.0f;
	float GravityValue = -1000.0f;

	int RandomIndex = 0;
	int StuckAnimationIndex = 0;
};