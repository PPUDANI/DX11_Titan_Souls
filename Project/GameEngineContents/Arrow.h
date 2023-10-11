#pragma once

enum class ARROW_STATE
{
	Hold,
	Aim,
	Flying,
	Fallen,
	Returning,
	PickUp,
};

class Arrow : public ActorBase
{
public:
	// Constructor Destructor
	Arrow();
	~Arrow();

	// Delete Function
	Arrow(const Arrow& _Other) = delete;
	Arrow(Arrow&& _Other) noexcept = delete;
	Arrow& operator=(const Arrow& _Other) = delete;
	Arrow& operator=(Arrow&& _Other) noexcept = delete;

	void ChangeState(ARROW_STATE _State);

	inline ARROW_STATE GetCurState() const
	{
		return CurState;
	}

	// Player Setting
	inline void OwnerPlayerSetting(std::shared_ptr<class Player> _Player)
	{
		OwnerPlayer = _Player.get();
	}

	// TileMap Setting
	void TileMapSetting(std::shared_ptr<TileMap> _Map)
	{
		CurMap = _Map.get();
		TileEndPos = CurMap->GetTileSize();
	}

	inline void SetArrowAngleDeg(float4& _Angle)
	{
		ArrowAngleDeg = _Angle;
	}

	inline void AddArrowAngleDeg(float4 _Angle)
	{
		ArrowAngleDeg += _Angle;
	}

	void DebugingModeSwitch()
	{
		DebugingMode = !DebugingMode;
	}

private:
	// External Element
	class Player* OwnerPlayer = nullptr;
	class TileMap* CurMap = nullptr;

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta);

	//FSM Functions
	void HoldStart();
	void AimStart();
	void FlyingStart();
	void FallenStart();
	void ReturningStart();
	void PickUpStart();

	void HoldUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void FlyingUpdate(float _Delta);
	void FallenUpdate(float _Delta);
	void ReturningUpdate(float _Delta);
	void PickUpUpdate(float _Delta);

	// State Variable
	ARROW_STATE CurState;
	bool AbleReturning = true;

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

	// Collision
	float4 ArrowheadPosBasis = { 12.0f, 12.0f };
	float4 ArrowheadCheckPos = float4::ZERO;
	TILE_COLLISION_TYPE TileColType = TILE_COLLISION_TYPE::EMPTY;

	void MoveAndColCheck(float4& _MovePos);
	bool ArrowColCheckByState(float4& _MovePos);
	void AdjustPosByCol();
private:
	// Debug Mode
	bool DebugingMode = false;
	void DirSpecularReflection();
	void DebugRender();

private:
	// Physics Valuable
	float4 ArrowAngleDeg = float4::ZERO;
	float4 FlyingDirectionBasis = float4::ZERO;
	float4 CameraMoveDirectionBasis = float4::ZERO;

	float PullingForce = 0.0f;
	float MaxPullingForce = 1.0f;
	float PullingForceIncreaseSpeed = 10.0f;
	float DefaultSpeed = 3000.0f;
	float ZoomRatio = 1.0f;

	float CameraMoveScale = 1.0f;
	float CameraMovePos = 1.0f;

	float4 WindowScale;

	bool IsBlocked = false;
	float FiyTimer = 0.0f;
public:
	//CurMap EndPos
	float4 TileEndPos = float4::ZERO;
};