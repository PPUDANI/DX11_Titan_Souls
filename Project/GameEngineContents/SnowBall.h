#pragma once

class SnowBall : public GameEngineActor
{
public:
	// Constructor Destructor
	SnowBall();
	~SnowBall();

	// Delete Function
	SnowBall(const SnowBall& _Other) = delete;
	SnowBall(SnowBall&& _Other) noexcept = delete;
	SnowBall& operator=(const SnowBall& _Other) = delete;
	SnowBall& operator=(SnowBall&& _Other) noexcept = delete;

protected:

private:

};