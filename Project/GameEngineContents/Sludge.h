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

private:
	class Heart* HeartActor = nullptr;
private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> PressMarkRenderer = nullptr;
	float4 RenderScale = { 256.0f , 256.0f, 1.0f };
	float4 ShadowRenderScale = { 128.0f, 128.0f , 1.0f };
	float MaxScale = 0.0f;
	float MinScale = 0.0f;
	float ExpandDefalutSpeed = 192.0f;
	
	float LerpRange = 0.0f;

	float4 HeartPos = float4::ZERO;

private:
	void RendererSetting() override;

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

	bool IsDivision = false;
	float DividedCount = 0.0f;
	float SizeReduction = 0.33f;
	float SludgeDividedSize = 0.0f;
	SLUDGE_STATE ExpandDir = SLUDGE_STATE::Decrease;
	EventParameter Param;
private:
	// Physics
	void DecreaseY(float _Speed);
	void IncreaseY(float _Speed);

	bool ReadyToJump = false;
};