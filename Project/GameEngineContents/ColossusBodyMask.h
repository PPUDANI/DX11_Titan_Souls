#pragma once

class ColossusBodyMask : public Effect
{
public:
	// Constructor Destructor
	ColossusBodyMask();
	~ColossusBodyMask();

	// Delete Function
	ColossusBodyMask(const ColossusBodyMask& _Other) = delete;
	ColossusBodyMask(ColossusBodyMask&& _Other) noexcept = delete;
	ColossusBodyMask& operator=(const ColossusBodyMask& _Other) = delete;
	ColossusBodyMask& operator=(ColossusBodyMask&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};