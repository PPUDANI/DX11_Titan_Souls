#pragma once

class ActorBase : public GameEngineActor
{
public:
	// Constructor Destructor
	ActorBase();
	~ActorBase();

	// Delete Function
	ActorBase(const ActorBase& _Other) = delete;
	ActorBase(ActorBase&& _Other) noexcept = delete;
	ActorBase& operator=(const ActorBase& _Other) = delete;
	ActorBase& operator=(ActorBase&& _Other) noexcept = delete;

protected:

private:

};