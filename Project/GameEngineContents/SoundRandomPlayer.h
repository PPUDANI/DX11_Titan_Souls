#pragma once

class SoundRandomPlayer
{
public:
	// Constructor Destructor
	SoundRandomPlayer(std::vector<std::string_view> _SoundList) : SoundList(_SoundList)
	{

	};
	~SoundRandomPlayer();

	// Delete Function
	SoundRandomPlayer(const SoundRandomPlayer& _Other) = delete;
	SoundRandomPlayer(SoundRandomPlayer&& _Other) noexcept = delete;
	SoundRandomPlayer& operator=(const SoundRandomPlayer& _Other) = delete;
	SoundRandomPlayer& operator=(SoundRandomPlayer&& _Other) noexcept = delete;

	void InputSoundList(std::vector<std::string_view> _SoundList);

	void RandomPlay(float AddSoundVolume= 0.0f, int _Loop = 0);

	inline void Stop()
	{
		SoundPlayer.Stop();
	}

protected:

private:
	std::vector<std::string_view> SoundList;
	GameEngineSoundPlayer SoundPlayer;
	GameEngineRandom Inst;
	int RandomCount = 0;
};