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

	void SetSprite(std::string_view SpriteName)
	{

	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

private:
	GameEngineRandom Inst;
	int RandomSeedCount = 0;
};