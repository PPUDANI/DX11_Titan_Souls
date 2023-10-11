#pragma once

class Debris : public ActorBase
{
public:
	// Constructor Destructor
	Debris();
	~Debris();

	// Delete Function
	Debris(const Debris& _Other) = delete;
	Debris(Debris&& _Other) noexcept = delete;
	Debris& operator=(const Debris& _Other) = delete;
	Debris& operator=(Debris&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};