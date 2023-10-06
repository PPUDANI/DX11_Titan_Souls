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

	inline void OwnerPlayerSetting(std::shared_ptr<class Player> _Player)
	{
		OwnerPlayer = _Player;
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


private:
	// Owner Player
	std::shared_ptr<class Player> OwnerPlayer = nullptr;

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

private:
	// Physics Valuable
	float4 ArrowAngleDeg = float4::ZERO;
	float4 FiyingDirection = float4::ZERO;
	float PullingForce = 0.0f;
	float MaxPullingForce = 6.0f;
	float PullingForceIncreaseSpeed = 8.0f;

	float DefaultSpeed = 800.0f;

private:
};