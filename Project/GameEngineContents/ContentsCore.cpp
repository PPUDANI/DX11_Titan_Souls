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
#include "EndingLevel.h"
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
	CursorOff();

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
	GameEngineCore::CreateLevel<EndingLevel>("04.Ending");

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
	if (true == GameEngineInput::IsDown(VK_F5, this))
	{
		GameEngineCore::ChangeLevel("04.Ending");
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
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("OverlayLightMask");
		Mat->SetVertexShader("OverlayLightMask_VS");
		Mat->SetPixelShader("OverlayLightMask_PS");
	}
}

void ContentsCore::CursorOff()
{
	CURSORINFO CursorInfo;
	CursorInfo.cbSize = sizeof(CURSORINFO);

	GetCursorInfo(&CursorInfo);

	if (0 == CursorInfo.flags)
	{
		return;
	}

	ShowCursor(FALSE);
}

void ContentsCore::CursorOn()
{
	CURSORINFO CursorInfo;
	CursorInfo.cbSize = sizeof(CURSORINFO);

	GetCursorInfo(&CursorInfo);

	if (1 == CursorInfo.flags)
	{
		return;
	}
	ShowCursor(TRUE);
}
