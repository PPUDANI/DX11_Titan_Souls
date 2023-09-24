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