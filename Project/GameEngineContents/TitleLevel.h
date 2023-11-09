#pragma once
enum class TITLE_STATE
{
	GAMEPAD,
	ACIDNERVE,
	DEVOLVER,
	MAIN_TITLE,
	GAME_START,
};

enum class SELECT_MENU
{
	START,
	OPTION,
	EXIT,
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
	TITLE_STATE CurState = TITLE_STATE::GAMEPAD;
	void ChangeState(TITLE_STATE _State);

	void GamePadStart();
	void AcidnerveStart();
	void DevolverStart();
	void MainTitleStart();
	void GameStartStart();

	void GamePadUpdate(float _Delta);
	void AcidnerveUpdate(float _Delta);
	void DevolverUpdate(float _Delta);
	void MainTitleUpdate(float _Delta);
	void GameStartUpdate(float _Delta);

private:
	// TileMap Actor
	std::shared_ptr<class TileMap> TileMapActor;

	// Overlay Actor
	std::shared_ptr<class OverlayActor> ScreenOverlayActor = nullptr;

	// Fade Actor
	std::shared_ptr<class FadeIn> FadeInActor = nullptr;
	std::shared_ptr<class FadeOut> FadeOutActor = nullptr;

	// 
	//  Actor
	std::shared_ptr<class FadeImage> GamePadImage = nullptr;
	std::shared_ptr<class FadeImage> AcidnerveImage = nullptr;
	std::shared_ptr<class FadeImage> DevolverImage = nullptr;

	// Image Actor
	std::shared_ptr<class ImageActor> TitleLogo = nullptr;

	void MainTitleActorOff();
private:
	// Text Actor
	std::shared_ptr<class SelectText> StartText = nullptr;
	std::shared_ptr<class SelectText> OptionText = nullptr;
	std::shared_ptr<class SelectText> ExitText = nullptr;

	SELECT_MENU CurSelectMenu = SELECT_MENU::START;
	SELECT_MENU PrevSelectMenu = SELECT_MENU::START;

	float4 SelectedColor = float4::WHITE;
	float4 UnSelectedColor = { 0.4f, 0.4f, 0.4f, 1.0f };

	void SetSelectAction();
};