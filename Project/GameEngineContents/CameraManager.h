#pragma once

class CameraManager
{
public:
	// Constructor Destructor
	CameraManager();
	~CameraManager();

	// Delete Function
	CameraManager(const CameraManager& _Other) = delete;
	CameraManager(CameraManager&& _Other) noexcept = delete;
	CameraManager& operator=(const CameraManager& _Other) = delete;
	CameraManager& operator=(CameraManager&& _Other) noexcept = delete;

	static float4 AddCameraPosFromArrow;
	static float4 AddCameraPosFromPlayer;
	static float4 AddCameraPosFromBoss;

	static float AddCameraZoomFromArrow;
	static float AddCameraZoomFromPlayer;
	static float AddCameraZoomFromBoss;

	static float4 GetCameraPos()
	{
		float4 CameraPos = AddCameraPosFromArrow + AddCameraPosFromPlayer + AddCameraPosFromBoss;

		CameraPos.Z = -100.0f;
		CameraPos.W = 1.0f;
		return CameraPos;
	}

	static float GetCameraZoom()
	{
		float ZoomValue = AddCameraZoomFromPlayer + AddCameraZoomFromArrow + AddCameraZoomFromBoss;
		if (0.1f > ZoomValue)
		{
			ZoomValue = 1.0f;
		}
		else if (1.0f <  ZoomValue)
		{
			ZoomValue = 1.0f;
		}
		return ZoomValue;
	}

protected:

private:

};