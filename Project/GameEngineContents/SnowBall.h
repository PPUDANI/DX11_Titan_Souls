#pragma once

class Snowball : public GameEngineActor
{
public:
	// Constructor Destructor
	Snowball();
	~Snowball();

	// Delete Function
	Snowball(const Snowball& _Other) = delete;
	Snowball(Snowball&& _Other) noexcept = delete;
	Snowball& operator=(const Snowball& _Other) = delete;
	Snowball& operator=(Snowball&& _Other) noexcept = delete;

	void Init(const float4& _StartPos, const float4& _Angle)
	{
		Transform.SetLocalPosition(_StartPos);
		AngleToPlayer = _Angle;
	}

protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

private:
	float4 StartPos = float4::ZERO;
	float4 AngleToPlayer = float4::ZERO;
	
	float SnowballSpeed = 1500.0f;
};