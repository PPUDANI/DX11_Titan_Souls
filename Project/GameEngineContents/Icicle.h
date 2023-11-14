#pragma once

enum class ICICLE_STATE
{
	Falling,
	Stuck,
};

class Icicle : public GameEngineActor
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

	inline void PlayerSetting(Player* _PlayerPtr)
	{
		EnymePlayer = _PlayerPtr;
	}

private:
	Player* EnymePlayer = nullptr;

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
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> FallingCollision = nullptr;
	std::shared_ptr<GameEngineCollision> BlockedCollision = nullptr;


private:
	float4 TargetPos = float4::ZERO;
	float4 StandardHeight = float4::ZERO;

	float GravityForce = 1500.0f;
	float GravityValue = -500.0f;

	int RandomIndex = 0;
	int StuckAnimationIndex = 0;
};