#pragma once

class WeaknessActor : public BossBase
{
public:
	// Constructor Destructor
	WeaknessActor();
	~WeaknessActor();

	// Delete Function
	WeaknessActor(const WeaknessActor& _Other) = delete;
	WeaknessActor(WeaknessActor&& _Other) noexcept = delete;
	WeaknessActor& operator=(const WeaknessActor& _Other) = delete;
	WeaknessActor& operator=(WeaknessActor&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};