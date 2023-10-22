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

	inline void SetEnymePlayer(Player* _PlayerPtr)
	{
		EnymePlayer = _PlayerPtr;
	}

	inline void SetEnymeArrow(Arrow* _ArrowPtr)
	{
		EnymeArrow = _ArrowPtr;
	}

	inline void HitArrow()
	{
		IsHitArrow = true;
	}

	inline bool IsWeaknessActor()
	{
		return WeaknessActorValue;
	}

protected:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

protected:
	// Component
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

	class Player* EnymePlayer = nullptr;
	class Arrow* EnymeArrow = nullptr;

	// State
	bool IsHitArrow = false;
	bool WeaknessActorValue = false;

protected:
	void SetMoveDir(float4& _CheckPos);
	// Move
	float4 MoveDirBasis = float4::ZERO;

private:

};