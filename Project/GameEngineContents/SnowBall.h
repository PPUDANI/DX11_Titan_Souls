#pragma once
#include "YetiRoom.h"
class Snowball : public ActorBase
{
public:
	// Constructor Destructor
	Snowball();
	~Snowball();

	// Delete Function
	Snowball(const Snowball& _Other) = delete;
	Snowball(Snowball&& _Other) noexcept = delete;
	Snowball& operator=(const Snowball& _Other) = delete;
	Snowball& operator=(Snowball&& _Other) noexcept = delete;

	void TileMapSetting(TileMap* _TileMapPtr)
	{
		CurMap = _TileMapPtr;
	}

	void PlayerSetting(Player* _PlayerPtr)
	{
		EnymePlayer = _PlayerPtr;
	}

	void Init(const float4& _StartPos, const float4& _Angle, RENDERING_ORDER _Order)
	{
		Transform.SetLocalPosition(_StartPos);
		AngleToPlayer = _Angle;
		Renderer->SetRenderOrder(_Order);
	}

protected:

private:
	// Inheritance
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	std::shared_ptr<GameEngineCollision> Collision = nullptr;

	bool SoundIsPlay = false;
private:
	TileMap* CurMap = nullptr;
	Player* EnymePlayer = nullptr;
	bool TileColCheck();


	float4 StartPos = float4::ZERO;
	float4 AngleToPlayer = float4::ZERO;
	
	float SnowballSpeed = 1500.0f;

	static SoundRandomPlayer ThrowPlayer;

	static bool SoundIsLoaded;
	void SoundLoad();

private:
	float RollingSnowCoolTime = 1.0f / 60.0f;
	float RollingSnowCoolTimer = 0.0f;

	void SnowParticle()
	{
		dynamic_cast<YetiRoom*>(GetLevel())->CreateSnowParticle(Transform.GetLocalPosition(), AngleToPlayer.Z, 20.0f);
	}
};