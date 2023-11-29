#pragma once

class SpreadParticle : public GameEngineActor
{
public:
	// Constructor Destructor
	SpreadParticle();
	~SpreadParticle();

	// Delete Function
	SpreadParticle(const SpreadParticle& _Other) = delete;
	SpreadParticle(SpreadParticle&& _Other) noexcept = delete;
	SpreadParticle& operator=(const SpreadParticle& _Other) = delete;
	SpreadParticle& operator=(SpreadParticle&& _Other) noexcept = delete;

	void SetRenderer(std::string_view SpriteName, int _Index, float _StartScale, const float4& _BasisVec, float _StartAlpha = 0.0f, float _DeathTime = 1.0f)
	{
		Renderer->SetSprite(SpriteName, _Index);
		Renderer->SetImageScale({ _StartScale, _StartScale });
		Alpha = _StartAlpha;
		Renderer->GetColorData().MulColor.A = Alpha;
		DeathTime = _DeathTime;
		BasisVec = _BasisVec;
	}

	void SetSpeed(float _Min, float _Max)
	{
		Speed = Inst.RandomFloat(_Min, _Max);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	GameEngineRandom Inst;
	int RandomSeedCount = 0;

private:
	float4 Scale = float4::ZERO;
	float Alpha = 0.0f;
	float4 BasisVec = float4::ZERO;
	float Speed = 0.0f;

private:
	float DeathTime = 1.0f;
	float UpdateRatio = 1.0f;
};