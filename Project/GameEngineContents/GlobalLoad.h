#pragma once

class GlobalLoad
{
public:
	// Constructor Destructor
	GlobalLoad();
	~GlobalLoad();

	// Delete Function
	GlobalLoad(const GlobalLoad& _Other) = delete;
	GlobalLoad(GlobalLoad&& _Other) noexcept = delete;
	GlobalLoad& operator=(const GlobalLoad& _Other) = delete;
	GlobalLoad& operator=(GlobalLoad&& _Other) noexcept = delete;

	static void LoadPlayerTexture();
	static void LoadArrowInBagTexture();
	static void LoadBowTexture();
	static void LoadTestMapTexture();
	static void LoadUnderWorldTexture();
protected:

private:
	static bool IsLoadPlayerTexture;
	static bool IsLoadBowTexutre;
	static bool IsLoadArrowInBagTexture;
	static bool IsLoadTestMapTexture;
};