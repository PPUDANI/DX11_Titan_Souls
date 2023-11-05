#pragma once
enum class TITLE_STATE
{
	START,
	GAMEPAD,
	ACIDNERVE,
	DEVOLVER,
	MAIN_TITLE
};

class TitleLevel : public GameEngineLevel
{
public:
	// Constructor Destructor
	TitleLevel();
	~TitleLevel();

	// Delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	TITLE_STATE CurState;
	void ChangeState(TITLE_STATE _State);

	void GamePadStart();
	void AcidnerveStart();
	void DevolverStart();
	void MainTitleStart();

	void GamePadUpdate(float _Delta);
	void AcidnerveUpdate(float _Delta);
	void DevolverUpdate(float _Delta);
	void MainTitleUpdate(float _Delta);
private:


	// TileMap Actor
	std::shared_ptr<class TileMap> TileMapActor;

	// Overlay Actor
	std::shared_ptr<class ScreenOverlay> ScreenOverlayActor = nullptr;

	// Fade Actor
	std::shared_ptr<class FadeIn> FadeInActor = nullptr;
	std::shared_ptr<class FadeOut> FadeOutActor = nullptr;

	// FadeImage Actor
	std::shared_ptr<class FadeImage> GamePadImage = nullptr;
	std::shared_ptr<class FadeImage> AcidnerveImage = nullptr;
	std::shared_ptr<class FadeImage> DevolverImage = nullptr;
};