#pragma once

enum class FadeMode
{
	FadeIn,
	FadeOut,
	Off,
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
		FadeResetByMode();
	}

	inline void SetWhiteColor()
	{
		FadeRenderer->GetColorData().PlusColor = { 1.0f, 1.0f, 1.0f };
	}

	inline void SetBlackColor()
	{
		FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };
	}

	inline void SetColor(const float4& _Color)
	{
		FadeRenderer->GetColorData().PlusColor += _Color;
	}

	// 1Sec = 1.0f
	inline void SetFadeSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

	inline void SetTargetValue(float _TargetValue)
	{
		TargetValue = _TargetValue;
	}

	inline void SetDefaultValue(float _DefaultValue)
	{
		DefaultValue = _DefaultValue;
	}

	inline bool FadeIsEnd() const
	{
		return FadeEnd;
	}

	void FadeResetByMode()
	{
		FadeEnd = false;
		switch (Mode)
		{
		case FadeMode::FadeIn:
			
			if (0.0f > DefaultValue)
			{
				FadeRenderer->GetColorData().MulColor.A = 1.0f;
			}
			else
			{
				FadeRenderer->GetColorData().MulColor.A = DefaultValue;
			}

			if (0.0f > TargetValue)
			{
				TargetValue = 0.0f;
			}
			break;

		case FadeMode::FadeOut:
			if (0.0f > DefaultValue)
			{
				FadeRenderer->GetColorData().MulColor.A = 0.0f;
			}
			else
			{
				FadeRenderer->GetColorData().MulColor.A = DefaultValue;
			}

			if (0.0f > TargetValue)
			{
				TargetValue = 1.0f;
			}
			break;

		case FadeMode::Off:
			break;
		default:
			break;
		}
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
	FadeMode Mode = FadeMode::FadeOut;
	float FadeSpeed = 0.0f;
	float TargetValue = -1.0f;
	float DefaultValue = -1.0f;
	bool FadeEnd = false;
};