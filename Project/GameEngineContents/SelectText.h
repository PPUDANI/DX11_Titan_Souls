#pragma once

class SelectText : public TextActor
{
public:
	// Constructor Destructor
	SelectText();
	~SelectText();

	// Delete Function
	SelectText(const SelectText& _Other) = delete;
	SelectText(SelectText&& _Other) noexcept = delete;
	SelectText& operator=(const SelectText& _Other) = delete;
	SelectText& operator=(SelectText&& _Other) noexcept = delete;

	void Init(std::string_view _Text, const float4& _SelectedColor, const float4& _UnSelectedColor, float _FontScale);

	inline void SelectOff()
	{
		SideRenderer->Off();
		TextActor::SetColor(UnSelectedColor);
	}

	inline void SelectOn()
	{
		SideRenderer->On();
		TextActor::SetColor(SelectedColor);
	}

private:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SideRenderer = nullptr;

	float4 SelectedColor = float4::ZERO;
	float4 UnSelectedColor = float4::ZERO;
};