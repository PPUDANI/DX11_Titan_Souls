#pragma once

class PlayerMaskEffect : public Effect
{
public:
	// Constructor Destructor
	PlayerMaskEffect();
	~PlayerMaskEffect();

	// Delete Function
	PlayerMaskEffect(const PlayerMaskEffect& _Other) = delete;
	PlayerMaskEffect(PlayerMaskEffect&& _Other) noexcept = delete;
	PlayerMaskEffect& operator=(const PlayerMaskEffect& _Other) = delete;
	PlayerMaskEffect& operator=(PlayerMaskEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};