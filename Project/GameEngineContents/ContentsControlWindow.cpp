#include "PreCompile.h"
#include "ContentsControlWindow.h"
#include "ContentsCore.h"
#include "Floor1.h"

void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	Tabs.push_back(std::make_shared<Information>("Information"));
	Tabs.push_back(std::make_shared<SoundSetting>("SoundSetting"));
	Tabs.push_back(std::make_shared<ViewMode>("ViewMode"));
	CurTab = Tabs[1];
}

void Information::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::IsWindowFocused(4))
	{
		ContentsCore::CursorOn();
	}

	ImGui::SeparatorText("Position");
	std::list<std::shared_ptr<GameEngineObject>> PlayerActorList = _Level->GetObjectGroup(UPDATE_ORDER::Player);

	if (true != PlayerActorList.empty())
	{
		std::shared_ptr<GameEngineObject> PlayerActor = PlayerActorList.front();
		std::string PlayerPos = PlayerActor.get()->Transform.GetWorldPosition().ToString();

		ImGui::Text("\nPlayer Position");
		ImGui::Button(PlayerPos.c_str());
	}

	std::list<std::shared_ptr<GameEngineObject>> ArrowActorList = _Level->GetObjectGroup(UPDATE_ORDER::Arrow);

	if (true != ArrowActorList.empty())
	{
		std::shared_ptr<GameEngineObject> ArrowActor = ArrowActorList.front();
		std::string ArrorPos = ArrowActor.get()->Transform.GetWorldPosition().ToString();

		ImGui::Text("\nArrow Position");
		ImGui::Button(ArrorPos.c_str());
	}

	std::shared_ptr<GameEngineCamera> CameraObject = _Level->GetMainCamera();

	if (nullptr != CameraObject)
	{
		std::string CameraPos = _Level->GetMainCamera()->Transform.GetLocalPosition().ToString();
		ImGui::Text("\nCamera Position");
		ImGui::Button(CameraPos.c_str());
	}

	// Frame Per Second
	if (FPSUpdateTime < FPSUpdateTimer)
	{
		FPSUpdateTimer -= FPSUpdateTime;
		FramePerSecond = 1.0f / _DeltaTime;
	}
	else
	{
		FPSUpdateTimer += _DeltaTime;
	}
	std::string FPSStr = "\nFPS : ";
	FPSStr += std::to_string(static_cast<int>(FramePerSecond));
	ImGui::Text(FPSStr.c_str());

	ImGui::SeparatorText("Controller");

	static bool CollisionDebug = false;
	if (true == ImGui::Checkbox("Collision Debug", &CollisionDebug))
	{
		if (true == CollisionDebug &&
			false == GameEngineLevel::IsDebug)
		{
			GameEngineLevel::IsDebug = CollisionDebug;
		}
		else if (false == CollisionDebug &&
			true == GameEngineLevel::IsDebug)
		{
			GameEngineLevel::IsDebug = CollisionDebug;
		}
	}
	
	ImGui::Text("\n");
	Floor1* FloorLevel = dynamic_cast<Floor1*>(_Level);
	if (nullptr != FloorLevel)
	{
		if (ImGui::Button("Create Weakness"))
		{
			FloorLevel->CreateWeaknessActor();
		}

		if (ImGui::Button("Death Weakness"))
		{
			FloorLevel->DeathWeaknessActor();
		}
	}
}

void ViewMode::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::IsWindowFocused(4))
	{
		ContentsCore::CursorOn();
	}
	std::list<std::shared_ptr<GameEngineObject>> TileMapActorList = _Level->GetObjectGroup(UPDATE_ORDER::TileMap);

	if (true != TileMapActorList.empty())
	{
		std::shared_ptr<GameEngineObject> TileMapObject = TileMapActorList.front();
		TileMap* TileMapActor = dynamic_cast<TileMap*>(TileMapObject.get());

		ImGui::SeparatorText("TileMap View Mode");
		if (ImGui::Button("DEFAULT_MODE"))
		{
			TileMapActor->SetViewMode(VIEW_MODE::DEFAULT_MODE);
		}
		if (ImGui::Button("COLLISION_MODE"))
		{
			TileMapActor->SetViewMode(VIEW_MODE::COLLISION_MODE);
		}
		if (ImGui::Button("MATERIAL_MODE"))
		{
			TileMapActor->SetViewMode(VIEW_MODE::MATERIAL_MODE);
		}
		if (ImGui::Button("FG_MODE"))
		{
			TileMapActor->SetViewMode(VIEW_MODE::FG_MODE);
		}
	}
}

void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::IsWindowFocused(4))
	{
		ContentsCore::CursorOn();
	}
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}
}


void ContentsControlWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::IsWindowFocused(4))
	{
		ContentsCore::CursorOn();
	}
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
			CurTab->Start();
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}
}

void SoundSetting::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::IsWindowFocused(4))
	{
		ContentsCore::CursorOn();
	}
	ImGui::SeparatorText("Sound Volume Setting");
	static float BackgroundVolume = 1.0f;
	if (ImGui::SliderFloat("BackgroundVolume", &BackgroundVolume, 0.0f, 2.0f))
	{
		dynamic_cast<LevelBase*>(_Level)->SetBackgroundVolume(BackgroundVolume * 0.5f);
	}
	static float AmbienceVolume = 1.0f;
	if (ImGui::SliderFloat("AmbienceVolume", &AmbienceVolume, 0.0f, 2.0f))
	{
		dynamic_cast<LevelBase*>(_Level)->SetAmbienceVolume(AmbienceVolume);
	}
	static float EffectVolume = 1.0f;
	if (ImGui::SliderFloat("EffectVolume", &EffectVolume, 0.0f, 2.0f))
	{
		dynamic_cast<LevelBase*>(_Level)->SetEffectVolume(EffectVolume);
	}
}
