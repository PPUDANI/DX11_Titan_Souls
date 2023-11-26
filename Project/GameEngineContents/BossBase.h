#pragma once

class BossBase : public GameEngineActor
{
public:
	// Constructor Destructor
	BossBase();
	~BossBase();

	// Delete Function
	BossBase(const BossBase& _Other) = delete;
	BossBase(BossBase&& _Other) noexcept = delete;
	BossBase& operator=(const BossBase& _Other) = delete;
	BossBase& operator=(BossBase&& _Other) noexcept = delete;

	inline void SetEnymePlayer(Player* _PlayerPtr)
	{
		EnymePlayer = _PlayerPtr;
	}

	inline void SetEnymeArrow(Arrow* _ArrowPtr)
	{
		EnymeArrow = _ArrowPtr;
	}

	inline void TileMapSetting(TileMap* _CurMap)
	{
		CurMap = _CurMap;
	}

	inline void WeaknessHitByArrow()
	{
		IsWeaknessHitByArrow = true;
	}

	inline void BodyHitByArrow()
	{
		IsBodyHitByArrow = true;
	}

protected:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

protected:
	// Component
	std::shared_ptr<GameEngineSpriteRenderer> BodyRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

	void ShadowVariableByHeightUpdate(const float4& _JumpStartPos);
	void ShadowAlphaByHeightUpdate(const float4& _JumpStartPos);
	
	float4 ShadowStandardPos = float4::ZERO;
	float4 ShadowStandardScale = float4::ZERO;
	float ShadowStandardAlpha = 0.0f;
	float ShadowScaleConstant = 0.0f;
	float ShadowAlphaConstant = 0.0f;

	class Player* EnymePlayer = nullptr;
	class Arrow* EnymeArrow = nullptr;
	class TileMap* CurMap = nullptr;

	// State
	bool IsWeaknessHitByArrow = false;
	bool IsBodyHitByArrow = false;
protected:
	void SetMoveDir(const float4& _CheckPos);
	void SetMoveDir(const float4& _CheckPos, const float4& _EndPos);
	float4 SetMoveDirReturn(const float4& _CheckPos);
	void SetDirToDeg(float _Degree);
	// Move
	float4 MoveDirBasis = float4::ZERO;
	float4 MoveAngle = float4::ZERO;
	bool RandomMoveValue = false;

protected:
	CameraShakingObject CSObj;

	float CameraPosLerpForce = 0.0f;

protected:
	void EffectSoundStop()
	{
		EffectPlayer.Stop();
	}

	void EffectSoundPlay(std::string_view _SoundName)
	{
		EffectPlayer = GameEngineSound::SoundPlay(_SoundName);
		EffectPlayer.SetVolume(LevelBase::GetEffectVolume());
	}

	GameEngineSoundPlayer EffectPlayer;

	static bool SoundIsLoded;
};