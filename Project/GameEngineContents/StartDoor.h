#pragma once

class StartDoor : public GameEngineActor
{
public:
	// Constructor Destructor
	StartDoor();
	~StartDoor();

	// Delete Function
	StartDoor(const StartDoor& _Other) = delete;
	StartDoor(StartDoor&& _Other) noexcept = delete;
	StartDoor& operator=(const StartDoor& _Other) = delete;
	StartDoor& operator=(StartDoor&& _Other) noexcept = delete;

	void SetTileMap(TileMap* _Map)
	{
		CurMap = _Map;
		CollisionOn();
	}

	void OpenDoor()
	{
		OpenDoorValue = true;
		LightRenderer->On();

		Renderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
		LightRenderer->SetRenderOrder(RENDERING_ORDER::Y_SORT_ENTITY_FRONT);
		CollisionOff();
	}

	inline bool IsOpening() const
	{
		return OpenDoorValue;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LightRenderer = nullptr;

	TileMap* CurMap = nullptr;
	void CollisionOn();
	void CollisionOff();

private:
	bool OpenDoorValue = false;
	float Timer = 0.0f;
	float OpenTime = 2.0f;

private:
	float LightTimer = 0.0f;
	float LightTime = 0.5f;

private:
	GameEngineRandom Inst;
	int RandomSeedCount = 0;
};