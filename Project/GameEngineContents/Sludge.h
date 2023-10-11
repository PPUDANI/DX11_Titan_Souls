#pragma once

class Sludge : public ActorBase
{
public:
	// Constructor Destructor
	Sludge();
	~Sludge();

	// Delete Function
	Sludge(const Sludge& _Other) = delete;
	Sludge(Sludge&& _Other) noexcept = delete;
	Sludge& operator=(const Sludge& _Other) = delete;
	Sludge& operator=(Sludge&& _Other) noexcept = delete;

protected:

private:

};