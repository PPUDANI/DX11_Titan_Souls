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
		BackgroundPlayer2.SetVolume(BackgroundVolume);
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
		SetAmbienceVolume();
		SetEffectVolume();
	}

	static inline float GetBackgroundVolume()
	{
		return BackgroundVolume;
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
		BackgroundPlayer2.SetVolume(BackgroundVolume);
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
		FadeVolumeRatio += _Delta;
		if (1.0f < FadeVolumeRatio)
		{
			FadeVolumeRatio = 1.0f;
			FadeInVolume = false;
		}

		BackgroundPlayer.SetVolume(BackgroundVolume * FadeVolumeRatio);
		BackgroundPlayer2.SetVolume(BackgroundVolume * FadeVolumeRatio);
		AmbiencePlayer.SetVolume(AmbienceVolume * FadeVolumeRatio);
	}

	void BackFadeOutVolume(float _Delta)
	{
		FadeVolumeRatio -= _Delta;
		if (0.0f > FadeVolumeRatio)
		{
			FadeVolumeRatio = 0.0f;
			FadeOutVolume = false;
		}

		BackgroundPlayer.SetVolume(BackgroundVolume * FadeVolumeRatio);
		BackgroundPlayer2.SetVolume(BackgroundVolume * FadeVolumeRatio);
		AmbiencePlayer.SetVolume(AmbienceVolume * FadeVolumeRatio);
	}

	void FadeInVolumeIsOn()
	{
		FadeInVolume = true;
		FadeOutVolume = false;
	}

	void FadeOutVolumeIsOn()
	{
		FadeInVolume = false;
		FadeOutVolume = true;
	}

private:
	GameEngineSoundPlayer BackgroundPlayer;
	GameEngineSoundPlayer BackgroundPlayer2;
	GameEngineSoundPlayer AmbiencePlayer;
	GameEngineSoundPlayer EffectPlayer;

	static float BackgroundVolume;
	static float AmbienceVolume;
	static float EffectVolume;

private:
	bool FadeInVolume = true;
	bool FadeOutVolume = false;

	float FadeVolumeRatio = 0.0f;
};