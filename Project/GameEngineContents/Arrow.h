#pragma once

enum class ARROW_STATE
{
	Hold,
	Flying,
	Drop,
};

class Arrow : GameEngineActor
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

	static std::shared_ptr<Arrow> MainArrow;

	static void ShotArrow(float);

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
	void FlyingStart();
	void DropStart();

	void HoldUpdate(float _Delta);
	void FlyingUpdate(float _Delta);
	void DropUpdate(float _Delta);
};