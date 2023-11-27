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
		CloseDoorValue = false;
	}

	void CloseDoor()
	{
		if (true == OpenEnd)
		{
			CloseDoorValue = true;
			OpenDoorValue = false;
		}
		return;
	}

	inline bool OpenIsEnd()
	{
		return OpenEnd;
	}

	inline void SetPlayer(class Player* _PlayerPtr)
	{
		PlayerActor = _PlayerPtr;
	}

	inline void FocusOn()
	{
		FocusValue = true;
	}

	inline void FocusOff()
	{
		FocusValue = false;
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

	class Player* PlayerActor = nullptr;

private:

	float Speed = 20.0f;
	float MaxOpenDistance = 88.0f;
	float MovedDistance = 0.0f;

	float LightingTime = 2.0f;
	float LightingTimer = 0.0f;

	bool CloseDoorValue = false;

	bool OpenEnd = false;
	bool OpenDoorValue = false;

private:
	bool FocusValue = false;
	float CameraPosLerpForce = 0.0f;

	void FocusUpdate(float _Delta);
};