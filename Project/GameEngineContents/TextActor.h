#pragma once

class TextActor : public GameEngineActor
{
public:
	// Constructor Destructor
	TextActor();
	~TextActor();

	// Delete Function
	TextActor(const TextActor& _Other) = delete;
	TextActor(TextActor&& _Other) noexcept = delete;
	TextActor& operator=(const TextActor& _Other) = delete;
	TextActor& operator=(TextActor&& _Other) noexcept = delete;

	void Init(std::string_view _Text);
protected:
	void Start() override;
	void Update(float _Delta) override;

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renderers;
private:

};