#pragma once

class UpParticle : public GameEngineActor
{
public:
	// Constructor Destructor
	UpParticle();
	~UpParticle();

	// Delete Function
	UpParticle(const UpParticle& _Other) = delete;
	UpParticle(UpParticle&& _Other) noexcept = delete;
	UpParticle& operator=(const UpParticle& _Other) = delete;
	UpParticle& operator=(UpParticle&& _Other) noexcept = delete;

	void SetRenderer(std::string_view SpriteName, float _StartScale, float _StartAlpha = 0.0f)
	{
		Renderer->SetSprite(SpriteName);
		Scale = { _StartScale , _StartScale };
		Alpha = _StartAlpha;
		Renderer->GetColorData().MulColor.A = Alpha;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

	GameEngineRandom Inst;
	int RandomSeedCount = 0;

private:
	float Speed = 0.0f;
	float4 Scale = float4::ZERO;
	float Alpha = 0.0f;

private:
	float DeathTimer = 1.0f;
};