#pragma once

class LevelBase : public GameEngineLevel
{
public:
	// Constructor Destructor
	LevelBase();
	~LevelBase();

	// Delete Function
	LevelBase(const LevelBase& _Other) = delete;
	LevelBase(LevelBase&& _Other) noexcept = delete;
	LevelBase& operator=(const LevelBase& _Other) = delete;
	LevelBase& operator=(LevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<class MouseCursor> CursorActor = nullptr;
	float4 CursorAngle = float4::ZERO;

public:

	void SetGlobalVolume(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.0f;
		}
		else if (2.0f < _Value)
		{
			_Value =2.0f;
		}
		GameEngineSound::SetGlobalVolume(_Value);
		SetAllVolume();
	}

	void SetBackgroundVolume(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.0f;
		}
		else if (2.0f < _Value)
		{
			_Value = 2.0f;
		}
		BackgroundVolume = _Value;
		SetBackgroundVolume();
	}

	void SetBackground2Volume(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.0f;
		}
		else if (2.0f < _Value)
		{
			_Value = 2.0f;
		}
		Background2Volume = _Value;
		SetBackground2Volume();
	}

	void SetAmbienceVolume(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.0f;
		}
		else if (2.0f < _Value)
		{
			_Value = 2.0f;
		}
		AmbienceVolume = _Value;
		SetAmbienceVolume();
	}

	void SetEffectVolume(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.0f;
		}
		else if (2.0f < _Value)
		{
			_Value = 2.0f;
		}
		EffectVolume = _Value;
		SetEffectVolume();
	}

	void SetBackgroundVolume()
	{
		BackgroundPlayer.SetVolume(BackgroundVolume);
	}

	void SetBackground2Volume()
	{
		BackgroundPlayer2.SetVolume(Background2Volume);
	}

	void SetAmbienceVolume()
	{
		AmbiencePlayer.SetVolume(AmbienceVolume);
	}

	void SetEffectVolume()
	{
		EffectPlayer.SetVolume(EffectVolume);
	}

	void SetAllVolume()
	{
		SetBackgroundVolume();
		SetBackground2Volume();
		SetAmbienceVolume();
		SetEffectVolume();
	}

	static inline float GetBackgroundVolume()
	{
		return BackgroundVolume;
	}
	static inline float GetBackground2Volume()
	{
		return Background2Volume;
	}

	static inline float GetAmbienceVolume()
	{
		return AmbienceVolume;
	}

	static inline float GetEffectVolume()
	{
		return EffectVolume;
	}

protected:

	void BackgroundPlay(std::string_view _SoundName, int _Loop = 0)
	{
		BackgroundPlayer = GameEngineSound::SoundPlay(_SoundName, _Loop);
		BackgroundPlayer.SetVolume(BackgroundVolume);
	}

	void Background2Play(std::string_view _SoundName, int _Loop = 0)
	{
		BackgroundPlayer2 = GameEngineSound::SoundPlay(_SoundName, _Loop);
		BackgroundPlayer2.SetVolume(Background2Volume);
	}

	void AmbiencePlay(std::string_view _SoundName, int _Loop = 0)
	{
		AmbiencePlayer = GameEngineSound::SoundPlay(_SoundName, _Loop);
		AmbiencePlayer.SetVolume(AmbienceVolume);
	}

	void EffectPlay(std::string_view _SoundName, int _Loop = 0)
	{
		EffectPlayer = GameEngineSound::SoundPlay(_SoundName, _Loop);
		EffectPlayer.SetVolume(EffectVolume);
	}

	inline void BackgroundStop()
	{
		BackgroundPlayer.Stop();
	}
	inline void Background2Stop()
	{
		BackgroundPlayer2.Stop();
	}
	inline void AmbienceStop()
	{
		AmbiencePlayer.Stop();
	}
	inline void EffectStop()
	{
		EffectPlayer.Stop();
	}


	void BackFadeInVolume(float _Delta)
	{
		BackFadeVolumeRatio += _Delta;
		if (1.0f < BackFadeVolumeRatio)
		{
			BackFadeVolumeRatio = 1.0f;
			BackFadeInVolumeValue = false;
		}

		BackgroundPlayer.SetVolume(BackgroundVolume * BackFadeVolumeRatio);
		BackgroundPlayer2.SetVolume(BackgroundVolume * BackFadeVolumeRatio);
	}

	void BackFadeOutVolume(float _Delta)
	{
		BackFadeVolumeRatio -= _Delta;
		if (0.0f > BackFadeVolumeRatio)
		{
			BackFadeVolumeRatio = 0.0f;
			BackFadeOutVolumeValue = false;
		}

		BackgroundPlayer.SetVolume(BackgroundVolume * BackFadeVolumeRatio);
		BackgroundPlayer2.SetVolume(BackgroundVolume * BackFadeVolumeRatio);
	}

	void AmbienceFadeInVolume(float _Delta)
	{
		AmbienceFadeVolumeRatio += _Delta;
		if (1.0f < AmbienceFadeVolumeRatio)
		{
			AmbienceFadeVolumeRatio = 1.0f;
			AmbienceFadeInVolumeValue = false;
		}

		AmbiencePlayer.SetVolume(AmbienceVolume * AmbienceFadeVolumeRatio);
	}

	void AmbienceFadeOutVolume(float _Delta)
	{
		AmbienceFadeVolumeRatio -= _Delta;
		if (0.0f > AmbienceFadeVolumeRatio)
		{
			AmbienceFadeVolumeRatio = 0.0f;
			AmbienceFadeOutVolumeValue = false;
		}

		AmbiencePlayer.SetVolume(AmbienceVolume * AmbienceFadeVolumeRatio);
	}

	void EffectFadeInVolume(float _Delta)
	{
		EffectVolume += _Delta;
		if (1.0f < EffectVolume)
		{
			EffectVolume = 1.0f;
			EffectFadeInVolumeValue = false;
		}

		EffectPlayer.SetVolume(EffectVolume);
	}

	void EffectFadeOutVolume(float _Delta)
	{
		EffectVolume -= _Delta;
		if (0.0f > EffectVolume)
		{
			EffectVolume = 0.0f;
			EffectFadeOutVolumeValue = false;
		}

		EffectPlayer.SetVolume(EffectVolume);
	}

	void BackFadeInVolumeOn()
	{
		BackFadeVolumeRatio = 0.0f;
		BackFadeInVolumeValue = true;
		BackFadeOutVolumeValue = false;
	}

	void BackFadeOutVolumeOn()
	{
		BackFadeVolumeRatio = 1.0f;
		BackFadeInVolumeValue = false;
		BackFadeOutVolumeValue = true;
	}

	void AmbienceFadeInVolumeOn()
	{
		AmbienceFadeVolumeRatio = 0.0f;
		AmbienceFadeInVolumeValue = true;
		AmbienceFadeOutVolumeValue = false;
	}

	void AmbienceFadeOutVolumeOn()
	{
		AmbienceFadeVolumeRatio = 1.0f;
		AmbienceFadeInVolumeValue = false;
		AmbienceFadeOutVolumeValue = true;
	}

	void EffectFadeInVolumeOn()
	{
		EffectVolume = 0.0f;
		EffectFadeInVolumeValue = true;
		EffectFadeOutVolumeValue = false;
	}

	void EffectFadeOutVolumeOn()
	{
		EffectVolume = 1.0f;
		EffectFadeInVolumeValue = false;
		EffectFadeOutVolumeValue = true;
	}

private:
	GameEngineSoundPlayer BackgroundPlayer;
	GameEngineSoundPlayer BackgroundPlayer2;
	GameEngineSoundPlayer AmbiencePlayer;
	GameEngineSoundPlayer EffectPlayer;

	static float BackgroundVolume;
	static float Background2Volume;
	static float AmbienceVolume;
	static float EffectVolume;

private:
	bool BackFadeInVolumeValue = true;
	bool BackFadeOutVolumeValue = false;

	bool AmbienceFadeInVolumeValue = true;
	bool AmbienceFadeOutVolumeValue = false;

	bool EffectFadeInVolumeValue = true;
	bool EffectFadeOutVolumeValue = false;

	float BackFadeVolumeRatio = 0.0f;
	float AmbienceFadeVolumeRatio = 0.0f;

public:
	float GetDelta() const
	{
		return DeltaTime;
	}
private:
	float DeltaTime = 0.0f;
};