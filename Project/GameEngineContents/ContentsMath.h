#pragma once

class ContentsMath
{
public:
	// 0으로 수렴하는 감속 연산 함수입니다.
	// _DecelValue : 감속하는 대상입니다.
	// _DecelSpeedPerSec : 초당 감속 속도입니다. "DeltaTime"을 꼭 곱해주세요.
	//     (0.1f 라면 1초 후 90%, 1.0f 라면 1초 후 0% 로 감속됩니다.) 
	static void Deceleration(float& _DecelValue, float _DecelSpeedPerSec)
	{
		_DecelValue -= _DecelValue * _DecelSpeedPerSec;
		if (0.005f > _DecelValue)
		{
			_DecelValue = 0.0f;
		}
	}

	// _AccelValue : 가속하는 대상입니다.
    // _AccelSpeedPerSec : 초당 가속 속도입니다. "DeltaTime"을 꼭 곱해주세요.
	//     (0.1f라면 초당 10%, 1.0f라면 초당 100% 증가합니다.)
	// _Max : 최대 속도입니다.
	static void Acceleration(float& _AccelValue, float _AccelSpeedPerSec, float _Max)
	{
		_AccelValue += _AccelSpeedPerSec;
		if (_Max < _AccelValue)
		{
			_AccelValue = _Max;
		}
	}


};