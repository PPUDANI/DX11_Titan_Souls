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

protected:

private:
	
};

class DepthValue
{
public:
	static const float4 BGMap;
	static const float4 BGAMap;
	static const float4 WALLMap;
	static const float4 COLMap;
	static const float4 MATMap;
	static const float4 Shadow;
	static const float4 TempValue;
	static const float4 FGMap;
	static const float4 UI;
};