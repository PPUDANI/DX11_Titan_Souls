#pragma once

class EnterPlace : public GameEngineActor
{
public:
	// Constructor Destructor
	EnterPlace();
	~EnterPlace();

	// Delete Function
	EnterPlace(const EnterPlace& _Other) = delete;
	EnterPlace(EnterPlace&& _Other) noexcept = delete;
	EnterPlace& operator=(const EnterPlace& _Other) = delete;
	EnterPlace& operator=(EnterPlace&& _Other) noexcept = delete;

	void SetPlaceScale(const float4& _Sclae)
	{
		PlaceCol->Transform.SetLocalScale(_Sclae);
	}
protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> PlaceCol = nullptr;

};