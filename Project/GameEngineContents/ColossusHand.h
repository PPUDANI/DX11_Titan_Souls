#pragma once

class ColossusHand
{
public:
	// Constructor Destructor
	ColossusHand();
	~ColossusHand();

	// Delete Function
	ColossusHand(const ColossusHand& _Other) = delete;
	ColossusHand(ColossusHand&& _Other) noexcept = delete;
	ColossusHand& operator=(const ColossusHand& _Other) = delete;
	ColossusHand& operator=(ColossusHand&& _Other) noexcept = delete;

protected:

private:

};