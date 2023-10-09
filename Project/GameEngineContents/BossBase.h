#pragma once

class BossBase : GameEngineActor
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

protected:
	void Start() override;
	void Update(float _Delta) override;

	// Renderer
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;

	// Collision
	std::shared_ptr<class GameEngineCollision> WeakPoint = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;

private:

};