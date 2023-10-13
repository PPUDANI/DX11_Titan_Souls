#pragma once

class BossBase : public GameEngineActor
{
public:
	// Constructor Destructor
	BossBase();
	~BossBase();

	// Delete Function
	BossBase(const BossBase& _Other) = delete;
	BossBase(BossBase&& _Other) noexcept = delete;
	BossBase& operator=(const BossBase& _Other) = delete;
	BossBase& operator=(BossBase&& _Other) noexcept = delete;

	void SetEnymePlayer(Player* _PlayerPtr)
	{
		EnymePlayer = _PlayerPtr;
	}

protected:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

protected:
	// Component
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

	class Player* EnymePlayer = nullptr;

protected:
	void SetMoveDir(float4& _CheckPos);
	// Move
	float4 MoveDirBasis = float4::ZERO;

private:

};