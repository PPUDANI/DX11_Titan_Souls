#pragma once

class OverlayActor : public GameEngineActor
{
public:
	// Constructor Destructor
	OverlayActor();
	~OverlayActor();

	// Delete Function
	OverlayActor(const OverlayActor& _Other) = delete;
	OverlayActor(OverlayActor&& _Other) noexcept = delete;
	OverlayActor& operator=(const OverlayActor& _Other) = delete;
	OverlayActor& operator=(OverlayActor&& _Other) noexcept = delete;

	void SetScale(const float4& _Scale)
	{
		FadeRenderer->SetImageScale(_Scale);
	}

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