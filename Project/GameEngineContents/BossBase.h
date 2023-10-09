#pragma once

class BossBase
{
public:
	// Constructor Destructor
	BossBase();
	~BossBase();

	// Delete Function
	BossBase(const BossBase& _Other) = delete;
	BossBase(BossBase&& _Other) noexcept = delete;
	BossBase& operator=(const BossBase& _Other) = delete;
	BossBase& operator=(BossBase&& _Other) noexcept = delete;

protected:

private:

};