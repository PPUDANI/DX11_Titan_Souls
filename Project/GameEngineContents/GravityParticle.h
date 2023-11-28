#pragma once

class GravityParticle : public GameEngineActor
{
public:
	// Constructor Destructor
	GravityParticle();
	~GravityParticle();

	// Delete Function
	GravityParticle(const GravityParticle& _Other) = delete;
	GravityParticle(GravityParticle&& _Other) noexcept = delete;
	GravityParticle& operator=(const GravityParticle& _Other) = delete;
	GravityParticle& operator=(GravityParticle&& _Other) noexcept = delete;

	void SetRenderer(std::string_view SpriteName, int _Index, float _Scale = 0.0f, float _StartAlpha = 1.0f, float _DeathTime = 1.0f)
	{
		Renderer->SetSprite(SpriteName, _Index);
		Renderer->SetImageScale({ _Scale , _Scale });

		Alpha = _StartAlpha;
		Renderer->GetColorData().MulColor.A = Alpha;
		DeathTime = _DeathTime;
	}

	void GravityInit(float _GravityValue, float _GravityForce)
	{
		GravityValue = _GravityValue;
		GravityForce = _GravityForce;
	}	 

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

private:
	float Alpha = 1.0f;

private:
	float GravityValue = 0.0f;
	float GravityForce = 0.0f;
	float4 GravityDir = float4::UP;

	float RandomXSpeed = 0.0f;
	float RandomYSpeed = 0.0f;

private:
	float DeathTime = 0.0f;
	float UpdateRatio = 1.0f;

private:
	GameEngineRandom Inst;
	int RandomSeedCount = 0;
};