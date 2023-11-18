#pragma once

class SoundRandomPlayer
{
public:
	// Constructor Destructor
	SoundRandomPlayer();
	~SoundRandomPlayer();

	// Delete Function
	SoundRandomPlayer(const SoundRandomPlayer& _Other) = delete;
	SoundRandomPlayer(SoundRandomPlayer&& _Other) noexcept = delete;
	SoundRandomPlayer& operator=(const SoundRandomPlayer& _Other) = delete;
	SoundRandomPlayer& operator=(SoundRandomPlayer&& _Other) noexcept = delete;

	void InputSoundList(GameEngineSoundPlayer& _SoundPlayer, std::vector<std::string_view> _SoundList)
	{
		SoundList = _SoundList;
		SoundPlayer = _SoundPlayer;
	}

	void RandomPlay();
protected:

private:
	std::vector<std::string_view> SoundList;
	GameEngineSoundPlayer SoundPlayer;
	GameEngineRandom Inst;
	int RandomCount = 0;
};