#pragma once

class TitanSouls
{
public:
	// Constructor Destructor
	TitanSouls();
	~TitanSouls();

	// Delete Function
	TitanSouls(const TitanSouls& _Other) = delete;
	TitanSouls(TitanSouls&& _Other) noexcept = delete;
	TitanSouls& operator=(const TitanSouls& _Other) = delete;
	TitanSouls& operator=(TitanSouls&& _Other) noexcept = delete;

protected:

private:

};