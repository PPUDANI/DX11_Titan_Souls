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
	static std::vector<std::string_view> PlayerSnowStepList;

	// Sludge
	static std::vector<std::string_view> SludgeDivision0List;
	static std::vector<std::string_view> SludgeDivision1List;
	static std::vector<std::string_view> SludgeDivision2List;
	static std::vector<std::string_view> SludgeDivision3List;
	static std::vector<std::string_view> SludgeSlice;
	static std::vector<std::string_view> HeartList;

	// Yeti
	static std::vector<std::string_view> YetiRollList;
	static std::vector<std::string_view> YetiBlockedList;
	static std::vector<std::string_view> YetiLandList;
	static std::vector<std::string_view> SnowballThrowList;
	static std::vector<std::string_view> SnowballImpactList;
	static std::vector<std::string_view> IcicleLandList;
	static std::vector<std::string_view> IcicleSmashList;

	// Colossus
	static std::vector<std::string_view> FistAttackList;

protected:

private:
	
};