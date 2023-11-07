#pragma once

class AncientScript : public GameEngineActor
{
public:
	// Constructor Destructor
	AncientScript();
	~AncientScript();

	// Delete Function
	AncientScript(const AncientScript& _Other) = delete;
	AncientScript(AncientScript&& _Other) noexcept = delete;
	AncientScript& operator=(const AncientScript& _Other) = delete;
	AncientScript& operator=(AncientScript&& _Other) noexcept = delete;

	void Init(std::string_view _Text);

private:
	void Start() override;
	void Update(float _Delta) override;

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renderers;
};