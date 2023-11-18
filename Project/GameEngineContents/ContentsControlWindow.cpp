#include "PreCompile.h"
#include "ContentsControlWindow.h"

void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	Tabs.push_back(std::make_shared<ObjectPosition>("PositionTab"));
	Tabs.push_back(std::make_shared<Setting>("Setting"));
	CurTab = Tabs[1];
}

void ObjectPosition::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
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
}


void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
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

void Setting::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("\nSound Volume Setting");
	static float BackgroundVolume = 1.0f;
	if (ImGui::SliderFloat("BackgroundVolume", &BackgroundVolume, 0.0f, 2.0f))
	{
		dynamic_cast<LevelBase*>(_Level)->SetBackgroundVolume(BackgroundVolume);
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

	ImGui::Text("\n");
	static bool CollisionDebug = false;
	ImGui::Checkbox("Collision Debug", &CollisionDebug);
	if (true == CollisionDebug)
	{
		GameEngineLevel::IsDebug = true;
	}
	else
	{
		GameEngineLevel::IsDebug = false;
	}

	std::list<std::shared_ptr<GameEngineObject>> TileMapActorList = _Level->GetObjectGroup(UPDATE_ORDER::Map);

	if (true != TileMapActorList.empty())
	{
		std::shared_ptr<GameEngineObject> TileMapActor = TileMapActorList.front();
	}
}
