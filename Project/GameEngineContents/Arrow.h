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
		OwnerPlayer = _Player;
	}

	// TileMap Setting
	void TileMapSetting(std::shared_ptr<TileMap> _Map)
	{
		CurMap = _Map;
	}

	inline void SetArrowAngleDeg(float4& _Angle)
	{
		ArrowAngleDeg = _Angle;
	}

	inline void AddArrowAngleDeg(float4 _Angle)
	{
		ArrowAngleDeg += _Angle;
	}

	inline void SetRenderOrder(RENDERING_ORDER _Order)
	{
		if (static_cast<int>(_Order) != Renderer->GetOrder())
		{
			Renderer->SetRenderOrder(_Order);
		}
	}

	void DebugingModeSwitch()
	{
		DebugingMode = !DebugingMode;
	}

private:
	// External Element
	std::shared_ptr<class Player> OwnerPlayer = nullptr;
	std::shared_ptr<TileMap> CurMap;

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
	TILE_COLLISION_TYPE ColType = TILE_COLLISION_TYPE::EMPTY;

	bool NextColCkeck(float4 _MovePos);

private:
	// Debug Mode
	bool DebugingMode = false;
	void DebugRender();

private:
	// Physics Valuable
	float4 ArrowAngleDeg = float4::ZERO;
	float4 FlyingDirectionBasis = float4::ZERO;
	float PullingForce = 0.0f;
	float MaxPullingForce = 6.0f;
	float PullingForceIncreaseSpeed = 10.0f;
	float DefaultSpeed = 600.0f;

	float ZoomValue = 0.0f;
	float ZoomRatio = 0.0f;
	float CameraMoveScale = 1.0f;
	float CameraMovePos = 1.0f;
private:
};