#pragma once
#include <cmath>
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
	static float4 AddCameraPosFromActor;
	static float4 AddCameraPosFromShaking;

	static float AddCameraZoomFromArrow;
	static float AddCameraZoomFromPlayer;
	static float AddCameraZoomFromBoss;

	static float4 GetCameraPos(const float4& _TileEndPos)
	{
		float4 CameraPos = float4::ZERO;

 		if (true == CalCameraPosFromArrow)
		{
			CameraPos += AddCameraPosFromArrow;
		}

		if (true == CalCameraPosFromPlayer)
		{
			CameraPos += AddCameraPosFromPlayer;
		}

		if (true == CalCameraPosFromBoss)
		{
			CameraPos += AddCameraPosFromBoss;
		}

		if (true == CalCameraPosFromActor)
		{
			CameraPos += AddCameraPosFromActor;
		}

		if (TurmSize > CameraPos.X - GlobalValue::WindowScale.hX())
		{
			CameraPos.X = GlobalValue::WindowScale.hX() + TurmSize;
		}
		if (_TileEndPos.X - TurmSize < CameraPos.X + GlobalValue::WindowScale.hX())
		{
			CameraPos.X = _TileEndPos.X - TurmSize - GlobalValue::WindowScale.hX();
		}

		if (-TurmSize < CameraPos.Y + GlobalValue::WindowScale.hY())
		{
			CameraPos.Y = -GlobalValue::WindowScale.hY() - TurmSize;
		}
		if (_TileEndPos.Y + TurmSize > CameraPos.Y - GlobalValue::WindowScale.hY())
		{
			CameraPos.Y = _TileEndPos.Y + TurmSize + GlobalValue::WindowScale.hY();
		}

		CameraPos += AddCameraPosFromShaking;
		CameraPos.Z = -100.0f;


		return CameraPos;
	}

	static float GetCameraZoom()
	{
		float ZoomValue = AddCameraZoomFromPlayer * AddCameraZoomFromBoss;

		if (true == CalCameraZoomFromArrow)
		{
			ZoomValue *= AddCameraZoomFromArrow;
		}

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

	static void CameraValueReset()
	{
		AddCameraPosFromArrow = float4::ZERO;
		AddCameraPosFromPlayer = float4::ZERO;
		AddCameraPosFromBoss = float4::ZERO;
		AddCameraPosFromShaking = float4::ZERO;
		AddCameraZoomFromArrow = 1.0f;
		AddCameraZoomFromPlayer = 1.0f;
		AddCameraZoomFromBoss = 1.0f;
	}
	
	// Pos
	static void CalCameraPosFromArrowOn()
	{
		CalCameraPosFromArrow = true;
	}

	static void CalCameraPosFromArrowOff()
	{
		CalCameraPosFromArrow = false;
	}

	static void CalCameraPosFromPlayerOn()
	{
		CalCameraPosFromPlayer = true;
	}

	static void CalCameraPosFromPlayerOff()
	{
		CalCameraPosFromPlayer = false;
	}

	static void CalCameraPosFromBossOn()
	{
		CalCameraPosFromBoss = true;
	}

	static void CalCameraPosFromBossOff()
	{
		CalCameraPosFromBoss = false;
	}

	// Zoom
	static void CalCameraZoomFromArrowOn()
	{
		CalCameraZoomFromArrow = true;
	}

	static void CalCameraZoomFromArrowOff()
	{
		CalCameraZoomFromArrow = false;
	}

protected:

private:
	static float TurmSize;

	static bool CalCameraPosFromArrow;
	static bool CalCameraPosFromPlayer;
	static bool CalCameraPosFromBoss;
	static bool CalCameraPosFromActor;

	static bool CalCameraZoomFromArrow;
	static bool CalCameraZoomFromPlayer;
	static bool CalCameraZoomFromBoss;
	static bool CalCameraZoomFromActor;
};