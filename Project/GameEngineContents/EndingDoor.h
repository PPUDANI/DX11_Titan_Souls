#pragma once

class EndingDoor : public GameEngineActor
{
public:
	// Constructor Destructor
	EndingDoor();
	~EndingDoor();

	// Delete Function
	EndingDoor(const EndingDoor& _Other) = delete;
	EndingDoor(EndingDoor&& _Other) noexcept = delete;
	EndingDoor& operator=(const EndingDoor& _Other) = delete;
	EndingDoor& operator=(EndingDoor&& _Other) noexcept = delete;

	void OpenDoor()
	{
		OpenDoorValue = true;
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LeftDoor = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RightDoor = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> LeftDoorLight = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RightDoorLight = nullptr;

private:

	float OpenSpeed = 10.0f;
	float MaxOpenDistance = 176.0f;
	float MovedDistance = 0.0f;

	float LightingTime = 2.0f;
	float LightingTimer = 0.0f;


	bool OpenDoorValue = false;
};