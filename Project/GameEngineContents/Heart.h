#pragma once

class Heart : public JumpBoss
{
public:
	// Constructor Destructor
	Heart();
	~Heart();

	// Delete Function
	Heart(const Heart& _Other) = delete;
	Heart(Heart&& _Other) noexcept = delete;
	Heart& operator=(const Heart& _Other) = delete;
	Heart& operator=(Heart&& _Other) noexcept = delete;

	inline void SetOwnerSludge(class Sludge* _SludgePtr)
	{
		OwnerSludge = _SludgePtr;
	}

	inline bool IsFirstHit()
	{
		return FirstHitValue;
	}

	inline void SetFirstHit(bool _Value)
	{
		FirstHitValue = _Value;
	}

private:
	// Virtual function
	void Start() override;
	void Update(float _Delta) override;

	// State
	void InSludgeStart() override;
	void IdleStart() override;
	void JumpStart() override;
	void FallStart() override;
	void LandingStart() override;
	void OutOfSludgeStart() override;
	void DeathStart() override;

	void InSludgeUpdate(float _Delta) override;
	void IdleUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;
	void LandingUpdate(float _Delta) override;
	void OutOfSludgeUpdate(float _Delta) override;
	void DeathUpdate(float _Delta) override;

private:
	class Sludge* OwnerSludge = nullptr;

	bool FirstHitValue = false;

	static SoundRandomPlayer LandPlayer;
	static bool SoundIsLoaded;
	void SoundLoad();

};