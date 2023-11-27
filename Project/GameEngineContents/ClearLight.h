#pragma once

class ClearLight : public GameEngineActor
{
public:
	// Constructor Destructor
	ClearLight();
	~ClearLight();

	// Delete Function
	ClearLight(const ClearLight& _Other) = delete;
	ClearLight(ClearLight&& _Other) noexcept = delete;
	ClearLight& operator=(const ClearLight& _Other) = delete;
	ClearLight& operator=(ClearLight&& _Other) noexcept = delete;

	void LightOn()
	{
		LightRenderer->On();
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer = nullptr;
};