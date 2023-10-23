#pragma once

enum class JUMPBOSS_STATE
{
	Default,
	InSludge,
	Idle,
	Jump,
	Fall,
	Landing,
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
	virtual void DeathStart(){}

	virtual void InSludgeUpdate(float _Delta){}
	virtual void IdleUpdate(float _Delta){}
	virtual void JumpUpdate(float _Delta){}
	virtual void FallUpdate(float _Delta){}
	virtual void LandingUpdate(float _Delta){}
	virtual void DeathUpdate(float _Delta){}

protected:
	// Gravity
	void Gravity(float _Delta);
	float GravityValue = 0.0f;
	float GravityForce = 0.0f;
	float4 GravityDir = float4::UP;

protected:
	// Physics
	float MoveSpeed = 0.0f;
	float4 RenderPosBase = { 0.0f, 0.0f };
	float4 JumpStartPos = float4::ZERO;
	void MoveToPlayer(float _Delta);

	// State
	JUMPBOSS_STATE CurState = JUMPBOSS_STATE::Default;
	float JumpCooldown = 0.0f;

protected:
	virtual void RendererSetting() {}

private:

};