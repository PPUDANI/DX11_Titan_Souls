#pragma once

enum class PLAYER_STATE
{
	Idle,
	Walk,
	Run,
	Stop,
	Roll,
	Aim,
	Shot,
	Death,
};

enum class PLAYER_DIRECTION
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

class Player : public GameEngineActor
{
public:
	// Constructor Destructor
	Player();
	~Player();

	// Delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline PLAYER_STATE GetState() const
	{
		return CurState;
	}

	inline PLAYER_DIRECTION GetDir() const
	{
		return CurDir;
	}

protected:


private:
	void Start() override;
	void Update(float _Delta) override;

	void IdleStart();
	void WalkStart();
	void RunStart();
	void StopStart();
	void RollStart();
	void AimStart();
	void ShotStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void RollUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void ShotUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void SetAnimation(std::string_view _AnimName, int _Frame = 0, bool _Force = false);
	void ChangeState(PLAYER_STATE _State);
	void SetDir(PLAYER_DIRECTION _Dir, float _Delta);

	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	// 상태 변수
	PLAYER_STATE CurState = PLAYER_STATE::Idle;

	// 방향 변수
	PLAYER_DIRECTION CurDir = PLAYER_DIRECTION::Down;
	float4 PlayerDirDeg = float4::ZERO;
	float ChangeDirCoolTime = 0.05f;
	float ChangeDirCoolDownTimer = 0.0f;

	// 물리 변수
	const float DefaultSpeed = 200.0f;
	const float RunForce = 1.5f;
	const float RollForce = 3.0f;
	const float StopForce = 0.1f;

	// 구르기 재사용 대기시간
	bool RollCooldownOn = false;
	float RollCoolDown = 0.5f;
	float RollCoolDownTimer = 0.5;

	inline void Roll()
	{
		if (false == RollCooldownOn)
		{
			ChangeState(PLAYER_STATE::Roll);
		}
	}

	void RollCoolDownUpdate(float _Delta)
	{
		if (RollCoolDown <= RollCoolDownTimer)
		{
			RollCoolDownTimer = 0.0f;
			RollCooldownOn = false;
		}
		else
		{
			RollCoolDownTimer += _Delta;
		}
	}
};
