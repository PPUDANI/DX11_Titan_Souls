#pragma once

class Heart : GameEngineActor
{
public:
	// Constructor Destructor
	Heart();
	~Heart();

	// Delete Function
	Heart(const Heart& _Other) = delete;
	Heart(Heart&& _Other) noexcept = delete;
	Heart& operator=(const Heart& _Other) = delete;
	Heart& operator=(Heart&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};