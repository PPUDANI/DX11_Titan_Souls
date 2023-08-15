#pragma once

class Titan_Souls
{
public:
	// Constructor Destructor
	Titan_Souls();
	~Titan_Souls();

	// Delete Function
	Titan_Souls(const Titan_Souls& _Other) = delete;
	Titan_Souls(Titan_Souls&& _Other) noexcept = delete;
	Titan_Souls& operator=(const Titan_Souls& _Other) = delete;
	Titan_Souls& operator=(Titan_Souls&& _Other) noexcept = delete;

protected:

private:

};