#pragma once

class GlobalCalculator
{
public:
	static void CalDepthValue(float _CameraYPos, float _ActorYPos, float4& _DepthBuffer)
	{
		_CameraYPos -= GlobalValue::WindowScale.hY();

		float ActorPosInCamera = _ActorYPos - _CameraYPos;

		_DepthBuffer.Z += (ActorPosInCamera / GlobalValue::WindowScale.Y) + 1.0f;
	}
};