#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

// All Level
#include "TitleLevel.h"
#include "Floor1.h"
#include "SludgeHeartRoom.h"
#include "YetiRoom.h"
#include "ContentsControlWindow.h"


ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineRenderTarget::IsDepth = false;
	// Load
	ContentsShaderLoad();
	GameEngineFont::Load("TSfont");

	// Create IMGUI
	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	// Clear Color Setting
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	GameEngineCore::MainWindow.CursorOff();

	// Map Texture Load
	GlobalLoad::LoadSpriteCut(16, 16, "Spectiles.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Underworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Overworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Overworld2.png", "Resource\\Texture\\Map\\");
	
	// UI Texture Load
	GlobalLoad::LoadSpriteSingle("BossNameBG.png", "Resource\\Texture\\UI\\");

	// Create Level
	GameEngineCore::CreateLevel<TitleLevel>("00.TitleLevel");
	GameEngineCore::CreateLevel<Floor1>("01.Floor1");
	GameEngineCore::CreateLevel<SludgeHeartRoom>("02.SludgeHeartRoom");
	GameEngineCore::CreateLevel<YetiRoom>("03.YetiRoom");

	GameEngineCore::ChangeLevel("00.TitleLevel");

	GameEngineInput::AddInputObject(this);

}

void ContentsCore::Update(float _Delta)
{
	// 임시 레벨 변경
	if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		GameEngineCore::ChangeLevel("00.TitleLevel");
	}
	if (true == GameEngineInput::IsDown(VK_F2, this))
	{
		GameEngineCore::ChangeLevel("01.Floor1");
	}
	if (true == GameEngineInput::IsDown(VK_F3, this))
	{
		GameEngineCore::ChangeLevel("02.SludgeHeartRoom");
	}
	if (true == GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineCore::ChangeLevel("03.YetiRoom");
	}

}

void ContentsCore::Release()
{

}

void ContentsCore::ContentsShaderLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineContentsShader");
	Dir.MoveChild("GameEngineContentsShader");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineShader::AutoCompile(File);
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("PlayerMaskEffect");
		Mat->SetVertexShader("PlayerMaskEffect_VS");
		Mat->SetPixelShader("PlayerMaskEffect_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ColossusBodyMask");
		Mat->SetVertexShader("ColossusBodyMask_VS");
		Mat->SetPixelShader("ColossusBodyMask_PS");
	}
}
