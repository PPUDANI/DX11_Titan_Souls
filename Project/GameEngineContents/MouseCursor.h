#pragma once

class MouseCursor : public GameEngineActor
{
public:
	// Constructor Destructor
	MouseCursor();
	~MouseCursor();

	// Delete Function
	MouseCursor(const MouseCursor& _Other) = delete;
	MouseCursor(MouseCursor&& _Other) noexcept = delete;
	MouseCursor& operator=(const MouseCursor& _Other) = delete;
	MouseCursor& operator=(MouseCursor&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
};