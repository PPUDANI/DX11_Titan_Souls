#pragma once

class FadeScreenOverlay : public GameEngineActor
{
public:
	// Constructor Destructor
	FadeScreenOverlay();
	~FadeScreenOverlay();

	// Delete Function
	FadeScreenOverlay(const FadeScreenOverlay& _Other) = delete;
	FadeScreenOverlay(FadeScreenOverlay&& _Other) noexcept = delete;
	FadeScreenOverlay& operator=(const FadeScreenOverlay& _Other) = delete;
	FadeScreenOverlay& operator=(FadeScreenOverlay&& _Other) noexcept = delete;

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
		FadeOutOnValue = true;
		FadeInOnValue = false;

		MaxFadeAlpha = _MaxAlpha;
		FadeOutTime = _Time;
	}

	void FadeInOn(float _Time)
	{
		if (true == FadeInOnValue)
		{
			return;
		}

		FadeInOnValue = true;
		FadeOutOnValue = false;
		FadeRatio = 1.0f;
		FadeInTime = _Time;
	}

	inline bool FadeOutIsEnd() const
	{
		return !FadeOutOnValue;
	}

	inline bool FadeInIsEnd() const
	{
		return !FadeInOnValue;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
	bool FadeOutOnValue = false;

	float FadeOutTime = 0.0f;

	bool FadeInOnValue = false;
	float FadeInTime = 0.0f;

	float FadeRatio = 0.0f;
	float MaxFadeAlpha = 0.0f;
};