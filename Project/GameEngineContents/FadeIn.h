#pragma once

class FadeIn : public GameEngineActor
{
public:
	// Constructor Destructor
	FadeIn();
	~FadeIn();

	// Delete Function
	FadeIn(const FadeIn& _Other) = delete;
	FadeIn(FadeIn&& _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn& _Other) = delete;
	FadeIn& operator=(FadeIn&& _Other) noexcept = delete;

	// _Second
	void Init(FadeColor _Color, float _Second = 1.0f)
	{
		switch (_Color)
		{
		case FadeColor::White:
			FadeRenderer->GetColorData().PlusColor = { 1.0f, 1.0f, 1.0f };
			break;
		case FadeColor::Black:
		default:
			break;
		}

		FadeSpeed = 1.0f / _Second;
	}

	inline bool FadeIsEnd() const
	{
		return FadeEnd;
	}

	inline void FadeResetByMode()
	{
		FadeEnd = false;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
	float FadeSpeed = 0.0f;
	bool FadeEnd = false;
};