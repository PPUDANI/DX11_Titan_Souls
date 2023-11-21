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

	TriggerFunction EnterTriggerFunc = nullptr;
	TriggerFunction StayTriggerFunc = nullptr;
	TriggerFunction ExitTriggerFunc = nullptr;

	inline void SetPlaceScale(const float4& _Sclae)
	{
		PlaceCol->Transform.SetLocalScale(_Sclae);
	}

	inline void SetEnterTriggerFunc(TriggerFunction _Func)
	{
		EnterTriggerFunc = _Func;
	}

	inline void SetStayTriggerFunc(TriggerFunction _Func)
	{
		StayTriggerFunc = _Func;
	}

	inline void SetExitTriggerFunc(TriggerFunction _Func)
	{
		ExitTriggerFunc = _Func;
	}

protected:

private:
	// Inheritance Functions
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> PlaceCol = nullptr;
	EventParameter Param;
};