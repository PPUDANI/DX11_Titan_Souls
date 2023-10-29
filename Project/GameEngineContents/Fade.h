#pragma once

enum class FadeMode
{
	Off,
	FadeOut,
	FadeIn,
};

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

	inline void SetFadeMode(FadeMode _Mode)
	{
		Mode = _Mode;
	}

	inline void SetWhiteColor()
	{
		FadeRenderer->GetColorData().PlusColor = { 1.0f, 1.0f, 1.0f };
	}

	inline void SetBlackColor()
	{
		FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };
	}

	// 1Sec = 1.0f
	inline void SetFadeSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

	inline void SetMaxFade(float _Max)
	{
		MaxFade = _Max;
	}
protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
	FadeMode Mode = FadeMode::FadeOut;
	float FadeSpeed = 0.0f;
	float MaxFade = 0.0f;
};