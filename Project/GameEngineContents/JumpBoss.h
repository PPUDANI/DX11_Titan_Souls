#pragma once

enum class JUMPBOSS_STATE
{
	Default,
	InSludge,
	Idle,
	Jump,
	Fall,
	Landing,
	Division,
	Death,
};

class JumpBoss : public BossBase
{
public:
	// Constructor Destructor
	JumpBoss();
	~JumpBoss();

	// Delete Function
	JumpBoss(const JumpBoss& _Other) = delete;
	JumpBoss(JumpBoss&& _Other) noexcept = delete;
	JumpBoss& operator=(const JumpBoss& _Other) = delete;
	JumpBoss& operator=(JumpBoss&& _Other) noexcept = delete;

	void ChangeState(JUMPBOSS_STATE _State);

	inline JUMPBOSS_STATE GetCurState() const
	{
		return CurState;
	}

protected:
	void Start() override;
	void Update(float _Delta);

protected:
	// State
	virtual void InSludgeStart() {}
	virtual void IdleStart(){}
	virtual void JumpStart(){}
	virtual void FallStart(){}
	virtual void LandingStart(){}
	virtual void DivisionStart() {}
	virtual void DeathStart(){}

	virtual void InSludgeUpdate(float _Delta){}
	virtual void IdleUpdate(float _Delta){}
	virtual void JumpUpdate(float _Delta){}
	virtual void FallUpdate(float _Delta){}
	virtual void LandingUpdate(float _Delta){}
	virtual void DivisionUpdate(float _Delta) {}
	virtual void DeathUpdate(float _Delta){}

protected:
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 0.0f;
	float4 GravityDir = float4::UP;

protected:
	// Physics
	float4 ColPosInterval;

	float MoveSpeed = 0.0f;
	float4 RenderPosBase = { 0.0f, 0.0f };
	float4 JumpStartPos = float4::ZERO;

	float4 LeftPos = float4::ZERO;
	float4 RightPos = float4::ZERO;
	float4 UpPos = float4::ZERO;
	float4 DownPos = float4::ZERO;

	void PosUpdate();

	void MoveToPlayer(float _Delta);
	void TileColCheck(float4& _MovePos);
	// State
	JUMPBOSS_STATE CurState = JUMPBOSS_STATE::Default;
	float JumpCooldown = 0.0f;

protected:
	virtual void RendererSetting() {}

protected:
	std::shared_ptr<GameEngineCollision> PlayerDetectionRange = nullptr;
	bool FindPlayer = false;

	void SetMoveDirRandom(float4& _CheckPos, float _RandomRange);
	void AddMoveDirByArrow(float _AddPos);

private:
	void AdjustLeftPosByTileCol(float4& _MovePos);
	void AdjustRightPosByTileCol(float4& _MovePos);
	void AdjustUpPosByTileCol(float4& _MovePos);
	void AdjustDownPosByTileCol(float4& _MovePos);
};