#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class Tab
{
public:
	std::string Name;
	int Index;

	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class Information : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	Information(std::string_view _Name)
		: Tab(_Name)
	{
	}
private:
	float FPSUpdateTime = 0.5f;
	float FPSUpdateTimer = 0.0f;
	float FramePerSecond = 0.0f;
};

class ViewMode : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	ViewMode(std::string_view _Name)
		: Tab(_Name)
	{
	}
private:
	float FPSUpdateTime = 0.5f;
	float FPSUpdateTimer = 0.0f;
	float FramePerSecond = 0.0f;
};

class SoundSetting : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	SoundSetting(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

class LevelChangeTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	LevelChangeTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

// Ό³Έν :
class ContentsControlWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;

};

