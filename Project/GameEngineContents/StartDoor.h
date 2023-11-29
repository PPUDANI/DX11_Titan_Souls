#pragma once

class StartDoor : public GameEngineActor
{
public:
	// Constructor Destructor
	StartDoor();
	~StartDoor();

	// Delete Function
	StartDoor(const StartDoor& _Other) = delete;
	StartDoor(StartDoor&& _Other) noexcept = delete;
	StartDoor& operator=(const StartDoor& _Other) = delete;
	StartDoor& operator=(StartDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
};