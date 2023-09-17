#pragma once

enum class PLAYER_STATE
{
	Idle,
	Move,
	Stop,
	Roll,
	Blocked,
	Aim,
	Shot,
	Death,
	StandUp,
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
	
	// Debug Mode
	bool DebugMode = false;

	// TileMap
	std::shared_ptr<TileMap> CurMap;
	void SetTileMap(std::shared_ptr<TileMap> _Map)
	{
		CurMap = _Map;
	}

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;
public:
	// FMS Functions
	void ChangeState(PLAYER_STATE _State);

private:
	// State Start Functions
	void IdleStart();
	void MoveStart();
	void StopStart();
	void RollStart();
	void BlockedStart();
	void AimStart();
	void ShotStart();
	void DeathStart();
	void StandUpStart();

	// State Update Functions
	void IdleUpdate(float _Delta);
	void MoveUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void RollUpdate(float _Delta);
	void BlockedUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void ShotUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void StandUpUpadte(float _Delta);

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BowRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ArrowInBagRenderer = nullptr;

	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	// Load Texture & Create Animation Functions
	void CreatePlayerbodyAnimation();
	void CreateBowAnimation();
	void CreateArrowInBagAnimation();

	// Change Amimation By Direction Functions
	void SetAnimByDir(std::string_view _AnimName, int _Frame = 0, bool _Force = false);

private:
	// Tile Check Pos
	float4 LocalRightPos = { 11.0f, 0.0f };
	float4 LocalRightUpPos = { 11.0f, 1.0f };
	float4 LocalUpPos = { 0.0f, 1.0f };
	float4 LocalLeftUpPos = { -11.0f, 1.0f };
	float4 LocalLeftPos = { -11.0f, 0.0f };
	float4 LocalLeftDownPos = { -11.0f, -1.0f };
	float4 LocalDownPos = { 0.0f, -1.0f };
	float4 LocalRightDownPos = { 11.0f, -1.0f };

	bool TileColCheck();
	void PosNormalization(float4 _Pos);
private:
	// State Variables
	PLAYER_STATE CurState = PLAYER_STATE::Idle;
	PLAYER_STATE PrevState = PLAYER_STATE::Idle;

private:
	// Physics Variables
	const float DefaultSpeed = 160.0f;
	const float DebugModeForce = 10.0f;
	const float RunForce = 1.5f;
	const float RollForce = 2.5f;

	// Move Functions
	bool MoveCheck();

	// Deceleration
	float DecelerationRatio = 0.0f; // 1.0f보다 클 수 없음.

	void Deceleration(float _Speed)
	{
		DecelerationRatio -= DecelerationRatio * _Speed;
		if (0.05f > DecelerationRatio)
		{
			DecelerationRatio = 0.0f;
		}
	}

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
	float RollCoolDownTimer = 0.0f;

	inline bool RollCollDownCheck()
	{
		if (false == IsRollOnCooldown)
		{
			ChangeState(PLAYER_STATE::Roll);
			return true;
		}
		else
		{
			return false;
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

private:
	bool IsRunning = false;
	float KeepRunCoolTime = 0.1f;
	float KeepRunCoolDownTimer = 0.0f;

	void KeepRunCoolDownUpdate(float _Delta)
	{
		if (KeepRunCoolTime <= KeepRunCoolDownTimer)
		{
			KeepRunCoolDownTimer = 0.0f;
			IsRunning = false;
		}
		else
		{
			KeepRunCoolDownTimer += _Delta;
		}
	}
};
