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

	static float4 GetCameraPos(const float4& _TileEndPos)
	{
		float4 CameraPos = AddCameraPosFromArrow + AddCameraPosFromPlayer + AddCameraPosFromBoss;

		if (0.0f > CameraPos.X - GlobalValue::WindowScale.hX())
		{
			CameraPos.X = GlobalValue::WindowScale.hX();
		}
		if (_TileEndPos.X < CameraPos.X + GlobalValue::WindowScale.hX())
		{
			CameraPos.X = _TileEndPos.X - GlobalValue::WindowScale.hX();
		}
		if (0.0f < CameraPos.Y + GlobalValue::WindowScale.hY())
		{
			CameraPos.Y = -GlobalValue::WindowScale.hY();
		}
		if (_TileEndPos.Y > CameraPos.Y - GlobalValue::WindowScale.hY())
		{
			CameraPos.Y = _TileEndPos.Y + GlobalValue::WindowScale.hY();
		}

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