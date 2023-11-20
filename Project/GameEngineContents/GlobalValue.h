#pragma once

class GlobalValue
{
public:
	// Delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static const float4 WindowScale;
	static const float4 StandardTextureScale;

	// SoundList

	// Player
	static std::vector<std::string_view> PlayerStoneStepList;
	static std::vector<std::string_view> PlayerGrassStepList;

	// Yeti
	static std::vector<std::string_view> YetiRollList;
	static std::vector<std::string_view> YetiBlockedList;
	static std::vector<std::string_view> YetiLandList;
	static std::vector<std::string_view> SnowballThrowList;
	static std::vector<std::string_view> SnowballImpactList;
	static std::vector<std::string_view> IcicleLandList;
	static std::vector<std::string_view> IcicleSmashList;

protected:

private:
	
};