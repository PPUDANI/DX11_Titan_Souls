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

class ColCheckInfo
{
public:
	bool LeftCheck = false;
	bool RightCheck = false;
	bool UpCheck = false;
	bool DownCheck = false;

	COLLISION_TYPE LeftColType = COLLISION_TYPE::EMPTY;
	COLLISION_TYPE RightColType = COLLISION_TYPE::EMPTY;
	COLLISION_TYPE UpColType = COLLISION_TYPE::EMPTY;
	COLLISION_TYPE DownColType = COLLISION_TYPE::EMPTY;
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
	
	// Debuging Mode
	void DebugRender();
	void DebugingModeSwitch()
	{
		DebugingMode = !DebugingMode;
	}
	bool DebugingMode = false;

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
	// Collision Check Pos
	float4 LocalLeftPos = { -7.0f, -8.0f };
	float4 LocalLeftPos2 = { -7.0f, -13.0f };

	float4 LocalRightPos = { 7.0f, -8.0f };
	float4 LocalRightPos2 = { 7.0f, -13.0f };

	float4 LocalUpPos = { -3.0f, -5.0f };
	float4 LocalUpPos2 = { 3.0f, -5.0f };

	float4 LocalDownPos = { -3.0f, -16.0f };
	float4 LocalDownPos2 = { 3.0f, -16.0f };

	// Tile Check
	float4 TileLeftPos = { -8.0f, -11.0f };
	float4 TileRightPos = { 8.0f, -11.0f };
	float4 TileUpPos = { 0.0f, -4.0f };
	float4 TileDownPos = { 0.0f, -17.0f };

	ColCheckInfo ColInfo;
	ColCheckInfo ColTileInfo;

	void BodyColCheck();
	void TriangleColCheck();
	bool CurDirColCheck();
	void DirSpecularReflection();

	// Nomaliaztion
	void TileColCheck();
	void AdjustPosByCol();
private:
	// State Variables
	PLAYER_STATE CurState = PLAYER_STATE::Idle;

private:
	// Physics Variables
	const float DefaultSpeed = 160.0f;
	const float DebugModeForce = 10.0f;
	const float RunForce = 1.5f;
	const float RollForce = 2.6f;

	// Move Functions
	bool MoveCheckInIdle();
	bool MoveCheck();

	inline float4 MovePosInt(float4 _Pos)
	{
		int X = _Pos.iX();
		int Y = _Pos.iY();

		return { static_cast<float>(X), static_cast<float>(Y) };
	}

	// Deceleration
	float DecelerationValue = 0.0f; // 1.0f보다 클 수 없음.

	void Deceleration(float _Speed)
	{
		DecelerationValue -= DecelerationValue * _Speed;
		if (0.05f > DecelerationValue)
		{
			DecelerationValue = 0.0f;
		}
	}

private:
	// Direction Variables
	PLAYER_DIRECTION CurDir = PLAYER_DIRECTION::Down;
	float4 PlayerDirDeg = float4::ZERO;
	bool IsChangeDirOnCooldown = false;
	const float ChangeDirCoolTime = 0.05f;
	float ChangeDirCooldownTimer = 0.0f;

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
		if (ChangeDirCoolTime <= ChangeDirCooldownTimer)
		{
			ChangeDirCooldownTimer = 0.0f;
			IsChangeDirOnCooldown = false;
		}
		else
		{
			ChangeDirCooldownTimer += _Delta;
		}
	}

private:
	// Roll Variables
	bool IsRollingBlocked = false;

	// Roll CoolDown Variables
	bool IsRollOnCooldown = false;
	const float RollCooldown = 0.5f;
	float RollCooldownTimer = 0.0f;

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
		if (RollCooldown <= RollCooldownTimer)
		{
			RollCooldownTimer = 0.0f;
			IsRollOnCooldown = false;
		}
		else
		{
			RollCooldownTimer += _Delta;
		}
	}

private:
	bool IsRunning = false;
	const float KeepRunCoolTime = 0.1f;
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
