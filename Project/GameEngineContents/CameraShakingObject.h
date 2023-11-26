#pragma once

class CameraShakingObject
{
public:
	// Constructor Destructor
	CameraShakingObject();
	~CameraShakingObject();

	// Delete Function
	CameraShakingObject(const CameraShakingObject& _Other) = delete;
	CameraShakingObject(CameraShakingObject&& _Other) noexcept = delete;
	CameraShakingObject& operator=(const CameraShakingObject& _Other) = delete;
	CameraShakingObject& operator=(CameraShakingObject&& _Other) noexcept = delete;

	void ShakingScreen(float _Delta);

	void Init(float _ScreenShakingTime, float _ShakingPerFrame, float _ShakingLerpMax);

	void Reset()
	{
		FrameTimer = 0.0f;
		ScreenShakingTimer = 0.0f;
		ShakingEnd = false;
		ShakingLerpValue = ShakingLerpMax;
	}

	void SetLerpMax(float _ShakingLerpMax)
	{
		ShakingLerpMax = _ShakingLerpMax;
		ShakingLerpValue = ShakingLerpMax;
	}

protected:

private:


	GameEngineRandom Inst;

	float ShakingFrame = 1.0f / 60.0f;
	float FrameTimer = 0.0f;
	int ShakingSeedCount = 0;


	float ScreenShakingTimer = 0.0f;
	bool ShakingEnd = false;

	float ScreenShakingTime = 0.0f;
	float ShakingPerFrame = 0.0f;
	float ShakingLerpMax = 0.0f;
	float ShakingLerpValue = 0.0f;
};