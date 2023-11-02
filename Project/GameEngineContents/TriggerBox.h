#pragma once
#include <functional>

class TriggerBox : public GameEngineActor
{
public:
	// Constructor Destructor
	TriggerBox();
	~TriggerBox();

	// Delete Function
	TriggerBox(const TriggerBox& _Other) = delete;
	TriggerBox(TriggerBox&& _Other) noexcept = delete;
	TriggerBox& operator=(const TriggerBox& _Other) = delete;
	TriggerBox& operator=(TriggerBox&& _Other) noexcept = delete;

	using TriggerFunction = std::function<void()>;

	TriggerFunction TriggerFunc = nullptr;


	inline void SetPlaceScale(const float4& _Sclae)
	{
		PlaceCol->Transform.SetLocalScale(_Sclae);
	}

	inline void SetTriggerFunction(TriggerFunction _Func)
	{
		TriggerFunc = _Func;
	}

	inline void Stop()
	{
		ColCheck = false;
	}
protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> PlaceCol = nullptr;
	EventParameter Param;
	bool ColCheck = false;
};