#pragma once

class ActorBase : public GameEngineActor
{
public:
	// Constructor Destructor
	ActorBase();
	~ActorBase();

	// Delete Function
	ActorBase(const ActorBase& _Other) = delete;
	ActorBase(ActorBase&& _Other) noexcept = delete;
	ActorBase& operator=(const ActorBase& _Other) = delete;
	ActorBase& operator=(ActorBase&& _Other) noexcept = delete;

protected:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;
	void EffectSoundStop()
	{
		EffectPlayer.Stop();
	}

	void EffectSoundPlay(std::string_view _SoundName)
	{
		EffectPlayer = GameEngineSound::SoundPlay(_SoundName);
		EffectPlayer.SetVolume(LevelBase::GetEffectVolume());
	}

	GameEngineSoundPlayer EffectPlayer;
private:
};