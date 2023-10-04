#pragma once

enum class ARROW_STATE
{
	Hold,
	Aim,
	Flying,
	Drop,
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

	inline void OwnerPlayerSetting(std::shared_ptr<class Player> _Player)
	{
		ArrowOwnerPlayer = _Player;
	}

	inline void SetArrowDeg(float& _Deg)
	{
		ArrowDegree = _Deg;
	}

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta);

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

private:
	// Physics Valuable
	float ArrowDegree = 0.0f;
	float PullingForce = 0.0f;
	float MaxPullingForce = 4.0f;
	float PullingForceIncreaseSpeed = 6.0f;
private:
	//FSM Functions
	ARROW_STATE CurState;
	std::shared_ptr<class Player> ArrowOwnerPlayer = nullptr;

	void HoldStart();
	void AimStart();
	void FlyingStart();
	void DropStart();
	void PickUpStart();

	void HoldUpdate(float _Delta);
	void AimUpdate(float _Delta);
	void FlyingUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void PickUpUpdate(float _Delta);
};