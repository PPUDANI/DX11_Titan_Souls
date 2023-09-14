#pragma once

enum class VIEW_MODE
{
	Main,
	Collision,
	Material,
};

class PlayLevelBase: public GameEngineLevel
{
public:
	// Constructor Destructor
	PlayLevelBase();
	~PlayLevelBase();

	// Delete Function
	PlayLevelBase(const PlayLevelBase& _Other) = delete;
	PlayLevelBase(PlayLevelBase&& _Other) noexcept = delete;
	PlayLevelBase& operator=(const PlayLevelBase& _Other) = delete;
	PlayLevelBase& operator=(PlayLevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _PrevLevel) override;

	std::shared_ptr<class Player> PlayerActor = nullptr;
	std::shared_ptr<class TestMap> Map = nullptr; // юс╫ц ╦й

	// TileMap
	//std::shared_ptr<class SubTileMap> BGMap = nullptr;
	//std::shared_ptr<class SubTileMap> BGAMap = nullptr;
	//std::shared_ptr<class SubTileMap> FGMap = nullptr;
	//std::shared_ptr<class SubTileMap> COLMap = nullptr;
	//std::shared_ptr<class SubTileMap> MATMap = nullptr;
	std::shared_ptr<class TileMap> MapActor;
	VIEW_MODE CurViewMode = VIEW_MODE::Main;

	void SetTileView(VIEW_MODE _Mode)
	{
		CurViewMode = _Mode;
	}
private:
	
};