#include "PreCompile.h"
#include "ContentsControlWindow.h"

void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	Tabs.push_back(std::make_shared<PositionTab>("PositionTab"));
	CurTab = Tabs[1];
}

void PositionTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::list<std::shared_ptr<GameEngineObject>> PlayerActorList = _Level->GetObjectGroup(UPDATE_ORDER::Player);

	if (true == PlayerActorList.empty())
	{
		return;
	}

	std::shared_ptr<GameEngineObject> PlayerActor = PlayerActorList.front();

	std::string PlayerPos = PlayerActor.get()->Transform.GetWorldPosition().ToString();

	std::list<std::shared_ptr<GameEngineObject>> ArrowActorList = _Level->GetObjectGroup(UPDATE_ORDER::Arrow);
	std::shared_ptr<GameEngineObject> ArrowActor = ArrowActorList.front();
	std::string ArrowrPos = ArrowActor.get()->Transform.GetWorldPosition().ToString();

	ImGui::Text("\nPlayer Position");
	ImGui::Button(PlayerPos.c_str());

	ImGui::Text("\nArrow Position");
	ImGui::Button(ArrowrPos.c_str());

	ImGui::Text("\n");
	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
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
