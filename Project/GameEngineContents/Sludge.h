#pragma once

class Sludge : public BossBase
{
public:
	// Constructor Destructor
	Sludge();
	~Sludge();

	// Delete Function
	Sludge(const Sludge& _Other) = delete;
	Sludge(Sludge&& _Other) noexcept = delete;
	Sludge& operator=(const Sludge& _Other) = delete;
	Sludge& operator=(Sludge&& _Other) noexcept = delete;

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

	float MinYScale = 160.0f;
	float MaxYScale = 320.0f;
	float4 Scale = { 256.0f , 256.0f, 1.0f};
	float WaveSpeed = 400.0f;
	bool ReverseSclae = false;
};