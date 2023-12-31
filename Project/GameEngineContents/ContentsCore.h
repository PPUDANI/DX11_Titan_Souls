#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCore.h>

// ���� :
class ContentsCore : public GameEngineObject
{
public:
	static std::string GetWindowTitle()
	{
		return "[ PPUDANI ] Titan Souls";
	}

	static float4 GetStartWindowSize()
	{
		return GlobalValue::WindowScale;
	}

	static float4 GetStartWindowPos()
	{
		return { 50.0f, 50.0f };
	}

	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static void CursorOff();
	static void CursorOn();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	void ContentsShaderLoad();

	std::shared_ptr<class GameEngineCoreWindow> RenderTargetGUI = nullptr;
	std::shared_ptr<class ContentsControlWindow> SettingGUI = nullptr;
};

