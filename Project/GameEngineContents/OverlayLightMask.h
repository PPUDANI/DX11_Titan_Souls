#pragma once

class OverlayLightMask : public Effect
{
public:
	// Constructor Destructor
	OverlayLightMask();
	~OverlayLightMask();

	// Delete Function
	OverlayLightMask(const OverlayLightMask& _Other) = delete;
	OverlayLightMask(OverlayLightMask&& _Other) noexcept = delete;
	OverlayLightMask& operator=(const OverlayLightMask& _Other) = delete;
	OverlayLightMask& operator=(OverlayLightMask&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};