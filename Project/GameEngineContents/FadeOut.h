#pragma once

class FadeOut : public GameEngineActor
{
public:
	// Constructor Destructor
	FadeOut();
	~FadeOut();

	// Delete Function
	FadeOut(const FadeOut& _Other) = delete;
	FadeOut(FadeOut&& _Other) noexcept = delete;
	FadeOut& operator=(const FadeOut& _Other) = delete;
	FadeOut& operator=(FadeOut&& _Other) noexcept = delete;

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