#pragma once

class TextActor : public GameEngineActor
{
public:
	// Constructor Destructor
	TextActor();
	~TextActor();

	// Delete Function
	TextActor(const TextActor& _Other) = delete;
	TextActor(TextActor&& _Other) noexcept = delete;
	TextActor& operator=(const TextActor& _Other) = delete;
	TextActor& operator=(TextActor&& _Other) noexcept = delete;

	void Init(std::string_view _Text, const float4& _Color, float _FontScale);
	void SetColor(const float4& _Color);

protected:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> FontRenderer = nullptr;

	std::string Text = "";
	float4 Color = float4::ZERO;
	float FontScale = 0.0f;

};