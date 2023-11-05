#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineBlend.h>

// All Level
#include "TitleLevel.h"
#include "Floor1.h"
#include "SludgeHeartRoom.h"
#include "YetiRoom.h"
#include "KnightElhananRoom.h"
#include "Jam.h"
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

	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; // src팩터
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("OverRay", Desc);
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureOver");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
		Mat->SetBlendState("OverRay");
	}

	// Clear Color Setting
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	GameEngineCore::MainWindow.CursorOff();

	// Map Texture Load
	GlobalLoad::LoadSpriteCut(16, 16, "Spectiles.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Jam.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Underworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Overworld.png", "Resource\\Texture\\Map\\");
	GlobalLoad::LoadSpriteCut(64, 64, "Overworld2.png", "Resource\\Texture\\Map\\");

	// Create Level
	GameEngineCore::CreateLevel<TitleLevel>("00.TitleLevel");
	GameEngineCore::CreateLevel<Floor1>("01.Floor1");
	GameEngineCore::CreateLevel<SludgeHeartRoom>("02.SludgeHeartRoom");
	GameEngineCore::CreateLevel<YetiRoom>("03.YetiRoom");
	GameEngineCore::CreateLevel<KnightElhananRoom>("04.KnightElhananRoom");
	GameEngineCore::CreateLevel<Jam>("05.Jam");
	// Create IMGUI
	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");

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
		GameEngineCore::ChangeLevel("04.KnightElhananRoom");
	}
	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineCore::ChangeLevel("05.Jam");
	}
}

void ContentsCore::Release()
{

}