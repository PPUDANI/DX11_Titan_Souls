#pragma once

class EventPlace : public GameEngineActor
{
public:
	// Constructor Destructor
	EventPlace();
	~EventPlace();

	// Delete Function
	EventPlace(const EventPlace& _Other) = delete;
	EventPlace(EventPlace&& _Other) noexcept = delete;
	EventPlace& operator=(const EventPlace& _Other) = delete;
	EventPlace& operator=(EventPlace&& _Other) noexcept = delete;

	inline void SetPlaceScale(const float4& _Sclae)
	{
		PlaceCol->Transform.SetLocalScale(_Sclae);
	}

	inline bool EnterCheck() const
	{
		return PlayerEnterCheck;
	}

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> PlaceCol = nullptr;
	EventParameter Param;
	bool PlayerEnterCheck = false;
};