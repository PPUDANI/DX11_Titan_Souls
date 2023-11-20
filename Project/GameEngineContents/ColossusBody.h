#pragma once

class ColossusBody
{
public:
	// Constructor Destructor
	ColossusBody();
	~ColossusBody();

	// Delete Function
	ColossusBody(const ColossusBody& _Other) = delete;
	ColossusBody(ColossusBody&& _Other) noexcept = delete;
	ColossusBody& operator=(const ColossusBody& _Other) = delete;
	ColossusBody& operator=(ColossusBody&& _Other) noexcept = delete;

protected:

private:

};