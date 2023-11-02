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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> FadeRenderer = nullptr;

private:
};