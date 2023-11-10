#pragma once

class Snowball
{
public:
	// Constructor Destructor
	Snowball();
	~Snowball();

	// Delete Function
	Snowball(const Snowball& _Other) = delete;
	Snowball(Snowball&& _Other) noexcept = delete;
	Snowball& operator=(const Snowball& _Other) = delete;
	Snowball& operator=(Snowball&& _Other) noexcept = delete;

protected:

private:

};