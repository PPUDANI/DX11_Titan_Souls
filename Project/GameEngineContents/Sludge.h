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

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

	float4 RenderBasePos = { 0.0f, -64.0f };
	float4 RenderScale = { 256.0f , 256.0f, 1.0f };

	float MaxScale = 352.0f;
	float ExpandDefalutSpeed = 192.0f;

	SLUDGE_STATE ExpandDir = SLUDGE_STATE::Decrease;

private:
	// State
	void IdleStart() override;
	void JumpStart() override;
	void FallStart() override;
	void LandingStart() override;
	void DeathStart() override;

	void IdleUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;
	void LandingUpdate(float _Delta) override;
	void DeathUpdate(float _Delta) override;

private:
	// Physics
	void DecreaseY(float _Speed);
	void IncreaseY(float _Speed);

	bool ReadyToJump = false;
};