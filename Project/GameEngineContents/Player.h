#pragma once

enum class PLAYER_STATE
{
	Idle,
	Move,
	Stop,
	Rolling,
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
	void RollingStart();
	void BlockedStart();
	void AimStart();
	void ShotStart();
	void DeathStart();
	void StandUpStart();

	// State Update Functions
	void IdleUpdate(float _Delta);
	void MoveUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void RollingUpdate(float _Delta);
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
	const float4 LocalLeftPos = { -9.0f, -8.0f };
	const float4 LocalLeftPos2 = { -9.0f, -14.0f };
	const float4 LocalRightPos = { 9.0f, -8.0f };
	const float4 LocalRightPos2 = { 9.0f, -14.0f };
	const float4 LocalUpPos = { -3.0f, -3.0f };
	const float4 LocalUpPos2 = { 3.0f, -3.0f };
	const float4 LocalDownPos = { -3.0f, -19.0f };
	const float4 LocalDownPos2 = { 3.0f, -19.0f };

	// Tile Check
	const float4 TileLeftPos = { -12.0f, -11.0f };
	const float4 TileRightPos = { 12.0f, -11.0f };
	const float4 TileUpPos = { 0.0f, 1.0f };
	const float4 TileDownPos = { 0.0f, -23.0f };

	ColCheckInfo BodyColInfo;
	ColCheckInfo TileColInfo;

	void BodyColCheck();
	bool CurDirColCheck();
	bool AnyDirColCheck();
	bool AllDirColCheck();

	// 모든 방향 충돌이 일어난 경우(충돌 타일에 낀 상태) 안전장치 함수
	void ResolveCollisionSticking();

	// Reflection
	void DirSpecularReflection();

	// Nomaliaztion
	void TileColCheck();
	void AdjustPosByCol();
private:
	// State Variables
	PLAYER_STATE CurState = PLAYER_STATE::Idle;
	bool IsBlocked = false;
private:
	// Physics Variables
	const float DefaultSpeed = 160.0f;
	const float DebugModeForce = 10.0f;
	const float RunForce = 1.5f;
	const float SpeedUpForce = 1.0f;
	const float RollingForce = 2.5f;

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
		if (0.01f > DecelerationValue)
		{
			DecelerationValue = 0.0f;
		}
	}

private:
	// Direction Variables
	PLAYER_DIRECTION CurDir = PLAYER_DIRECTION::Down;
	PLAYER_DIRECTION PrevDir = PLAYER_DIRECTION::Down;
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
	// Rolling Variables
	bool IsRollingingBlocked = false;

	// Rolling CoolDown Variables
	bool IsRollingOnCooldown = false;
	const float RollingCooldown = 0.5f;
	float RollingCooldownTimer = 0.0f;

	inline bool RollingCollDownCheck()
	{
		if (false == IsRollingOnCooldown)
		{
			ChangeState(PLAYER_STATE::Rolling);
			return true;
		}
		else
		{
			return false;
		}
	}

	void RollingCoolDownUpdate(float _Delta)
	{
		if (RollingCooldown <= RollingCooldownTimer)
		{
			RollingCooldownTimer = 0.0f;
			IsRollingOnCooldown = false;
		}
		else
		{
			RollingCooldownTimer += _Delta;
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
