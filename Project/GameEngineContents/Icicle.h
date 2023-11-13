#pragma once

class Icicle : public GameEngineActor
{
public:
	// Constructor Destructor
	Icicle();
	~Icicle();

	// Delete Function
	Icicle(const Icicle& _Other) = delete;
	Icicle(Icicle&& _Other) noexcept = delete;
	Icicle& operator=(const Icicle& _Other) = delete;
	Icicle& operator=(Icicle&& _Other) noexcept = delete;

	void Init(const float4& _StartPos);
protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

private:
	float4 TargetPoint = float4::ZERO;
	float4 StandardHeight = { 0.0f, 300.0f };

	float GravityForce = 1000.0f;
	float GravityValue = 0.0f;

};