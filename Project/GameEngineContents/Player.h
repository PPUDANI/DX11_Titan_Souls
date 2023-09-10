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
	Spawn,
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

	// static Player
	static std::shared_ptr<Player> MainPlayer;

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
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	// FMS Functions
	void ChangeState(PLAYER_STATE _State);

	void IdleStart();
	void WalkStart();
	void RunStart();
	void StopStart();
	void RollStart();
	void AimStart();
	void ShotStart();
	void DeathStart();
	void SpawnStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void RollUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void ShotUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void SpawnUpadte(float _Delta);

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	// Change Amimation By Direction Functions
	void SetAnimByDir(std::string_view _AnimName, int _Frame = 0, bool _Force = false);
	
private:
	// State Variables
	PLAYER_STATE CurState = PLAYER_STATE::Idle;

private:
	// Physics Variables
	const float DefaultSpeed = 200.0f;
	const float RunForce = 1.5f;
	const float RollForce = 3.0f;
	const float StopForce = 0.1f;

private:
	// Direction Variables
	PLAYER_DIRECTION CurDir = PLAYER_DIRECTION::Down;
	float4 PlayerDirDeg = float4::ZERO;
	bool IsChangeDirOnCooldown = false;
	float ChangeDirCoolTime = 0.05f;
	float ChangeDirCoolDownTimer = 0.0f;

	// Direction Functions
	void SetDirection(PLAYER_DIRECTION _Dir);

	inline void ChangeDirCheck(PLAYER_DIRECTION _Dir)
	{
		if (false == IsChangeDirOnCooldown)
		{
			IsChangeDirOnCooldown = true;
			SetDirection(_Dir);
		}
	}

	void ChangeDirCoolDownUpdate(float _Delta)
	{
		if (ChangeDirCoolTime <= ChangeDirCoolDownTimer)
		{
			ChangeDirCoolDownTimer = 0.0f;
			IsChangeDirOnCooldown = false;
		}
		else
		{
			ChangeDirCoolDownTimer += _Delta;
		}
	}

private:
	// Roll CoolDown Variables
	bool IsRollOnCooldown = false;
	float RollCoolDown = 0.5f;
	float RollCoolDownTimer = 0.5;

	inline void RollCheck()
	{
		if (false == IsRollOnCooldown)
		{
			ChangeState(PLAYER_STATE::Roll);
		}
	}

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
};
