#pragma once

class Icicle : public GameEngineActor
{
public:
	// Constructor Destructor
	Icicle();
	~Icicle();

	// Delete Function
	Icicle(const Icicle& _Other) = delete;
	Icicle(Icicle&& _Other) noexcept = delete;
	Icicle& operator=(const Icicle& _Other) = delete;
	Icicle& operator=(Icicle&& _Other) noexcept = delete;

protected:

private:

};