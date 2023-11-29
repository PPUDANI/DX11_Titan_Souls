#pragma once

class ClearLight2 : public GameEngineActor
{
public:
	// Constructor Destructor
	ClearLight2();
	~ClearLight2();

	// Delete Function
	ClearLight2(const ClearLight2& _Other) = delete;
	ClearLight2(ClearLight2&& _Other) noexcept = delete;
	ClearLight2& operator=(const ClearLight2& _Other) = delete;
	ClearLight2& operator=(ClearLight2&& _Other) noexcept = delete;

	void LightOn()
	{
		Renderer->On();
	}

	void EffectOn()
	{
		Renderer->RenderBaseInfoValue.Target3 = 1;
	}

	void EffectOff()
	{
		Renderer->RenderBaseInfoValue.Target3 = 0;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

private:
	float LightAlphaRatio = 1.0f;

	bool LightOnValue = false;
};