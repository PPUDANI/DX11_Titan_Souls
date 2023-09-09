#pragma once

enum class PLAYER_STATE
{
	Idle,
	Walk,
	Run,
	Roll,
	Aim,
	Shot,
	Death,
};

enum class PLAYER_DIRECTION
{
	Right,
	Up,
	Left,
	Down,
	RightDown,
	LeftDown,
	LeftUp,
	RightUp,
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
	void RollStart();
	void AimStart();
	void ShotStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void RollUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void ShotUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void SetAnimation(std::string_view _AnimName );
	void ChangeState(PLAYER_STATE _State);

	float4 MoveToDir(float _Speed);

	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	PLAYER_STATE CurState = PLAYER_STATE::Idle;
	PLAYER_DIRECTION CurDir = PLAYER_DIRECTION::Down;

	// 물리 변수
	const float DefaultSpeed = 150.0f;
	const float RollSpeed = 600.0f;

	// 구르기 재사용 대기시간
	void RollCoolDownUpdate(float _Delta)
	{
		if (RollCoolDown <= RollCoolDownTimer)
		{
			RollCoolDownTimer = 0.0f;
			IsRollOnCooldown = false;
		}
		else
		{
			RollCoolDownTimer += _Delta;
		}
	}
	bool IsRollOnCooldown = false;
	float RollCoolDown = 0.6f;
	float RollCoolDownTimer = 0.0f;
};