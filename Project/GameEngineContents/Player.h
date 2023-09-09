#pragma once

enum class PlayerState
{
	Idle,
	Run,
	Roll,
	Aim,
	Shot,
	Death,
};

enum class PlayerDir
{
	Right,
	Up,
	Left,
	Down,
	RightDown,
	LeftDown,
	LeftUp,
	RightUp,
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

	inline PlayerState GetState() const
	{
		return CurState;
	}

	inline PlayerDir GetDir() const
	{
		return CurDir;
	}

protected:


private:
	void Start() override;
	void Update(float _Delta) override;

	void IdleStart();
	void RunStart();
	void RollStart();
	void AimStart();
	void ShotStart();
	void DeathStart();

	void IdleUpdate();
	void RunUpdate();
	void RollUpdate();
	void AimUpdate();
	void ShotUpdate();
	void DeathUpdate();

	void SetAnimation(std::string_view _AnimName );
	void ChangeState(PlayerState _State);

	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	PlayerState CurState = PlayerState::Idle;
	PlayerDir CurDir = PlayerDir::Down;
};