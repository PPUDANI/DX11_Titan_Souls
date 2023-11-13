#pragma once

enum class YETI_STATE
{
	Sleep,
	Idle,
	Throwing,
	ReadyToRoll,
	Rolling,
	Landing,
	Blocked,
	Hit,
	Death,
};

enum class YETI_DIRECTION
{
	Right,
	RightUp,
	Up,
	LeftUp,
	Left,
	LeftDown,
	Down,
	RightDown,
};

class Yeti : public BossBase
{
public:
	// Constructor Destructor
	Yeti();
	~Yeti();

	// Delete Function
	Yeti(const Yeti& _Other) = delete;
	Yeti(Yeti&& _Other) noexcept = delete;
	Yeti& operator=(const Yeti& _Other) = delete;
	Yeti& operator=(Yeti&& _Other) noexcept = delete;

	void ChangeState(YETI_STATE _State);

	void WakeUpYeti();
	
	inline bool YetiIsWakeUp() const
	{
		return YetiIsWakeUpValue;
	}

	inline void YetiIsWakeUpReset()
	{
		YetiIsWakeUpValue = false;
	}

	inline YETI_STATE GetCurState() const
	{
		return CurState;
	}

protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	// State
	bool YetiIsWakeUpValue = false;
	YETI_STATE CurState = YETI_STATE::Sleep;
	YETI_STATE NextStateBuffer = YETI_STATE::Sleep;


	void SleepStart();
	void IdleStart();
	void ThrowingStart();
	void ReadyToRollStart();
	void RollingStart();
	void LandingStart();
	void BlockedStart();
	void HitStart();
	void DeathStart();

	void SleepUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void ThrowingUpdate(float _Delta);
	void ReadyToRollUpdate(float _Delta);
	void RollingUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void BlockedUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);

private:
	YETI_DIRECTION CurDir = YETI_DIRECTION::Down;
	void SetDirection(YETI_DIRECTION _Dir);
	void DirectionUpdate();
	void DirReflection();

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer = nullptr;
	float4 RendererStandardPos = { 0.0f, -20.0f };

	void CreateYetiAnimation();
	void SetAnimByDir(std::string_view _AnimName, int _Frame = 0, bool _Force = false);

private:
	std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollision2 = nullptr;
	std::shared_ptr<class GameEngineCollision> RollingCollision = nullptr;

	EventParameter Param;

	void SetColScaleByDir();

	inline void BodyCollisionOff()
	{
		Collision->Off();
		BodyCollision->Off();
		BodyCollision2->Off();
	}

	inline void BodyCollisionOn()
	{
		Collision->On();
		BodyCollision->On();
		BodyCollision2->On();
	}

	float4 BodyColStandardPos = { 0.0f, 50.0f };
	float4 WeeknessColStandardPos = { 0.0f, 0.0f };
	float4 RollingColStandardPos = { 0.0f, 0.0f };

	bool TileColCheck(float4& _MovePos);
	void AdjustLeftPosByTileCol(float4& _MovePos);
	void AdjustRightPosByTileCol(float4& _MovePos);
	void AdjustUpPosByTileCol(float4& _MovePos);
	void AdjustDownPosByTileCol(float4& _MovePos);

	float4 LeftPos = {40.0f, 0.0f};
	float4 RightPos = {-40.0f, 0.0f};
	float4 UpPos = {0.0f, 20.0f};
	float4 DownPos = {0.0f, -20.0f};

private:
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 1200.0f;
	float4 GravityDir = float4::UP;

	float RollingSpeed = 1200.0f;
	float DecreaseByBlocked = 0.15f;
	float4 JumpStartPos = float4::ZERO;

private:
	float IdleDelay = 0.5f;
	float IdleTimer = 0.0f;

	float ThrowingDelay = 0.1f;
	float ThrowingTimer = 0.0f;
	bool IsThrowing = false;

	unsigned int ThrowMaxCount = 4;
	unsigned int ThrowCount = 0;
	
	float LandingDelay = 0.5f;
	float LandingTimer = 0.0f;

	void ThrowSnowball();

private:
	void ShakingScreenInit();
};