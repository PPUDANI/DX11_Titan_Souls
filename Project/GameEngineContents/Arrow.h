#pragma once

enum class ARROW_STATE
{
	Default,
	Hold,
	Aim,
	Flying,
	Fallen,
	Returning,
	PickUp,
	Pinned,
};

class Arrow : public GameEngineActor
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
	}

	inline void SetArrowAngleDeg(const float4& _Angle)
	{
		ArrowAngleDeg = _Angle;
	}

	inline float4 GetArrowAngleDeg() const
	{
		return ArrowAngleDeg;
	}

	inline void AddArrowAngleDeg(float4 _Angle)
	{
		ArrowAngleDeg += _Angle;
	}

	void DecreasePullingForce(float _Delta)
	{
		PullingForce = std::lerp(PullingForce, 0.0f, _Delta);
	}

	bool HitSpeedCheck() const
	{
		return StandartPullingForceByHit < PullingForce;
	}

	void SetOrderToYSort()
	{
		Renderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY);
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
	void PinnedStart();

	void HoldUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void FlyingUpdate(float _Delta);
	void FallenUpdate(float _Delta);
	void ReturningUpdate(float _Delta);
	void PickUpUpdate(float _Delta);
	void PinnedUpdate(float _Delta);

	// State Variable
	ARROW_STATE CurState = ARROW_STATE::Default;
	bool AbleReturning = true;

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;
	std::shared_ptr<GameEngineCollision> PickUpCollision = nullptr;
	// Collision
	float ArrowheadPosBasis = 12.0f;
	float4 ArrowheadCheckPos = float4::ZERO;
	TILE_COLLISION_TYPE TileColType = TILE_COLLISION_TYPE::EMPTY;

	void MoveAndColCheck(const float4& _MovePos);
	bool ArrowColCheckByState(const float4& _MovePos);
	void AdjustPosByTileCol();
	void AdjustPosByCol();
	void WeaknessCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup, float4 _MovePos);
	void BossBodyCollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup, float4 _MovePos);

private:
	// Debug Mode
	void DirSpecularReflection();
	void DebugRender();

private:
	// Physics Valuable
	float4 ArrowAngleDeg = float4::ZERO;
	float4 FlyingDirectionBasis = float4::ZERO;
	float4 CameraMoveDirectionBasis = float4::ZERO;

	float PullingForce = 0.0f;
	float DefaultSpeed = 4500.0f;
	float ZoomRatio = 1.0f;

	float CameraMoveScale = 1.0f;
	float CameraMovePos = 1.0f;

	float4 WindowScale;

	bool IsBlocked = false;
	float FiyTimer = 0.0f;

	// Pinned Valuable
	float DirRangeValue = 8.0f;
	float AddRange = 0.0f;
	float PinnedRotationDir = 0.0f;
	float PinnedRotationSpeed = 500.0f;
	bool RotationReverse = false;

	float StandartPullingForceByHit = 0.5f;

	float PullOutDuration = 2.0f;
	float PullOutTimer = 0.0f;

public:
	//CurMap EndPos
	float4 TileEndPos = float4::ZERO;
};