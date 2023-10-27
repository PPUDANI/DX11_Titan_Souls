#pragma once

class Fade : public GameEngineActor
{
public:
	// Constructor Destructor
	Fade();
	~Fade();

	// Delete Function
	Fade(const Fade& _Other) = delete;
	Fade(Fade&& _Other) noexcept = delete;
	Fade& operator=(const Fade& _Other) = delete;
	Fade& operator=(Fade&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;
};