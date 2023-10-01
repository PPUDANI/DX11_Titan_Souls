#pragma once

enum class ARROW_STATE
{
	Hold,
	Zoom,
	Flying,
	Drop,
	PickUp,
};

class Arrow : public GameEngineActor
{
public:
	// Constructor Destructor
	Arrow();
	~Arrow();

	// Delete Function
	Arrow(const Arrow& _Other) = delete;
	Arrow(Arrow&& _Other) noexcept = delete;
	Arrow& operator=(const Arrow& _Other) = delete;
	Arrow& operator=(Arrow&& _Other) noexcept = delete;

	void ChangeState(ARROW_STATE _State);

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta);

private:
	// Components
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;

private:
	//FSM Functions
	ARROW_STATE CurState = ARROW_STATE::Hold;

	void HoldStart();
	void ZoomStart();
	void FlyingStart();
	void DropStart();
	void PickUpStart();

	void HoldUpdate(float _Delta);
	void ZoomUpdate(float _Delta);
	void FlyingUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void PickUpUpdate(float _Delta);
};