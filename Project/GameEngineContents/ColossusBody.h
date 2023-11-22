#pragma once

class ColossusBody : public GameEngineActor
{
public:
	// Constructor Destructor
	ColossusBody();
	~ColossusBody();

	// Delete Function
	ColossusBody(const ColossusBody& _Other) = delete;
	ColossusBody(ColossusBody&& _Other) noexcept = delete;
	ColossusBody& operator=(const ColossusBody& _Other) = delete;
	ColossusBody& operator=(ColossusBody&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr; 
	std::shared_ptr<GameEngineSpriteRenderer> MaskRenderer = nullptr;

	std::shared_ptr<GameEngineCollision> Collision = nullptr;

};