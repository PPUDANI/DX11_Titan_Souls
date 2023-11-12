#pragma once

class Snowball : public GameEngineActor
{
public:
	// Constructor Destructor
	Snowball();
	~Snowball();

	// Delete Function
	Snowball(const Snowball& _Other) = delete;
	Snowball(Snowball&& _Other) noexcept = delete;
	Snowball& operator=(const Snowball& _Other) = delete;
	Snowball& operator=(Snowball&& _Other) noexcept = delete;

protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;
};