#pragma once
enum class BALL_STATE
{
	Idle,
	Hit,
	Death,
};

class CrystalBall : public BossBase
{
public:
	// Constructor Destructor
	CrystalBall();
	~CrystalBall();

	// Delete Function
	CrystalBall(const CrystalBall& _Other) = delete;
	CrystalBall(CrystalBall&& _Other) noexcept = delete;
	CrystalBall& operator=(const CrystalBall& _Other) = delete;
	CrystalBall& operator=(CrystalBall&& _Other) noexcept = delete;

	inline bool IsHitArrow() const
	{
		return HitArrow;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;


	void ChangeState(BALL_STATE _State);
	void IdleStart();
	void HitStart();
	void DeathStart();
	void IdleUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	BALL_STATE CurState = BALL_STATE::Idle;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer = nullptr;

private:

	float4 LightDefaultScale = { 32.0f, 32.0f};
	float LightScaleRatio = 1.0f;
	float LightAlphaRatio = 1.0f;
	float AddAlphaDir = 1.0f;

	bool HitArrow = false;
};