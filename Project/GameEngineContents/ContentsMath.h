#pragma once

class ContentsMath
{
public:
	// _DecelValue : �����ϴ� ����Դϴ�.
	// _DecelSpeedPerSec : �ʴ� ���� �ӵ��Դϴ�. "DeltaTime"�� �� �����ּ���.
	//     (0.1f ��� 1�� �� 90%, 1.0f ��� 1�� �� 0% �� ���ӵ˴ϴ�.) 
	static void Deceleration(float& _DecelValue, float _DecelSpeedPerSec)
	{
		_DecelValue -= _DecelValue * _DecelSpeedPerSec;
		if (0.05f > _DecelValue)
		{
			_DecelValue = 0.0f;
		}
	}

	// _AccelValue : �����ϴ� ����Դϴ�.
    // _AccelSpeedPerSec : �ʴ� ���� �ӵ��Դϴ�. "DeltaTime"�� �� �����ּ���.
	//     (0.1f��� �ʴ� 10%, 1.0f��� �ʴ� 100% �����մϴ�.)
	// _MaxSpeed : �ִ� �ӵ��Դϴ�.
	static void Acceleration(float& _AccelValue, float _AccelSpeedPerSec, float _MaxSpeed)
	{
		_AccelValue += _AccelSpeedPerSec;
		if (_MaxSpeed < _AccelValue)
		{
			_AccelValue = _MaxSpeed;
		}
	}


};