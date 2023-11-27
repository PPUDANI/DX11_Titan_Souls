#pragma once

class ScreenOverlay : public GameEngineActor
{
public:
	// Constructor Destructor
	ScreenOverlay();
	~ScreenOverlay();

	// Delete Function
	ScreenOverlay(const ScreenOverlay& _Other) = delete;
	ScreenOverlay(ScreenOverlay&& _Other) noexcept = delete;
	ScreenOverlay& operator=(const ScreenOverlay& _Other) = delete;
	ScreenOverlay& operator=(ScreenOverlay&& _Other) noexcept = delete;

	void SetColor(const float4& _Color)
	{
		FadeRenderer->GetColorData().PlusColor = _Color;
	}

	void SetAlpha(float _Alpha)
	{
		FadeRenderer->GetColorData().MulColor.A = _Alpha;
	}

	void FadeOutOn(float _MaxAlpha, float _Time)
	{
		MaxFadeAlpha = _MaxAlpha;
		FadeOnValue = true;
		FadeTime = _Time;
		FadeRatio = 0.0f;
	}

	void FadeInOn(float _MaxAlpha, float _Time)
	{
		MaxFadeAlpha = _MaxAlpha;
		FadeOnValue = true;
		FadeTime = -_Time;
		FadeRatio = 0.0f;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
	bool FadeOnValue = false;
	float MaxFadeAlpha = 0.0f;
	float FadeRatio = 0.0f;
	float FadeTime = 0.0f;
};