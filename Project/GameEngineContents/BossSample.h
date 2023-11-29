#pragma once

class BossSample : public BossBase
{
public:
	// Constructor Destructor
	BossSample();
	~BossSample();

	// Delete Function
	BossSample(const BossSample& _Other) = delete;
	BossSample(BossSample&& _Other) noexcept = delete;
	BossSample& operator=(const BossSample& _Other) = delete;
	BossSample& operator=(BossSample&& _Other) noexcept = delete;

protected:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> Collision2 = nullptr;
};