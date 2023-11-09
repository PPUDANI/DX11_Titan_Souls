#pragma once

enum class YETI_STATE
{
	Sleep,
	Idle,
	Throwing,
	ReadyToRoll,
	Rolling,
	Landing,
	Blocked,
	Hit,
	Death,
};

enum class YETI_DIRECTION
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

class Yeti : public BossBase
{
public:
	// Constructor Destructor
	Yeti();
	~Yeti();

	// Delete Function
	Yeti(const Yeti& _Other) = delete;
	Yeti(Yeti&& _Other) noexcept = delete;
	Yeti& operator=(const Yeti& _Other) = delete;
	Yeti& operator=(Yeti&& _Other) noexcept = delete;

protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	// State
	YETI_STATE CurState;
	void ChangeState(YETI_STATE _State);

	void SleepStart();
	void IdleStart();
	void ThrowingStart();
	void ReadyToRollStart();
	void RollingStart();
	void LandingStart();
	void BlockedStart();
	void HitStart();
	void DeathStart();

	void SleepUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void ThrowingUpdate(float _Delta);
	void ReadyToRollUpdate(float _Delta);
	void RollingUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void BlockedUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);
private:
	YETI_DIRECTION CurDir;

	void SetDirection(YETI_DIRECTION _Dir);
	void DirectionUpdate();
private:
	std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderer = nullptr;
	void CreateYetiAnimation();
	void SetAnimByDir(std::string_view _AnimName, int _Frame = 0, bool _Force = false);
};