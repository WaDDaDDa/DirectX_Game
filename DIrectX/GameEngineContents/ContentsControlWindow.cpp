#include "PreCompile.h"
#include "ContentsControlWindow.h"


void MapEditorTab::Start()
{
	GameEngineCore::ChangeLevel("MapEditor");
}

void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{

	if (ImGui::Button("Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Data");


		OPENFILENAMEA OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "GameData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetSaveFileNameA(&OFN) != 0) {
			// sprintf_s(filePathName, "%s 파일을 열겠습니까?", OFN.lpstrFile);

			SavePath = OFN.lpstrFile;
		}
	}

	InputPath.resize(256);

	std::string Labal = "저장경로";
	Labal = GameEngineString::AnsiToUTF8(Labal);
	ImGui::InputText(Labal.c_str(), &InputPath[0], InputPath.size());

	if (ImGui::Button("Def Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Data");

		std::string PathName = Dir.GetFileName();

		SavePath = PathName + InputPath + ".GameData";
	}

	if ("" != SavePath)
	{
		// File을 가지고 저장
		SavePath = "";
	}

	// 일반적으로 그냥 클래스를 저장할수는 없다.
	// 포인터는 저장의 의미가 없다.

}

void TestTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	if (ImGui::Button(MousePos.c_str()))
	{

	}
	std::string GameSpeed = "GameSpeed : ";
	GameSpeed += std::to_string(GameEngineCore::MainTime.GetTimeScale(0));
	if (ImGui::Button(GameSpeed.c_str()))
	{
		
	}

	if (ImGui::Button("Speed++ "))
	{
		Speed += 1.0f;
		GameEngineCore::MainTime.SetAllTimeScale(Speed);
	}

	if (ImGui::Button("Speed-- "))
	{
		Speed -= 1.0f;
		GameEngineCore::MainTime.SetAllTimeScale(Speed);
	}

	if (ImGui::Button("Normal Speed"))
	{
		Speed = 1.0f;
		GameEngineCore::MainTime.SetAllTimeScale(Speed);
	}

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	if (ImGui::Button("Sound++ "))
	{
		Sound += 0.1f;

		if (Sound >= 1.0f)
		{
			Sound = 1.0f;
		}

		GameEngineSound::SetGlobalVolume(Sound);
	}

	if (ImGui::Button("Sound-- "))
	{
		Sound -= 0.1f;

		if (Sound <= 0.0f)
		{
			Sound = 0.0f;
		}

		GameEngineSound::SetGlobalVolume(Sound);
	}
	

	//std::list<std::shared_ptr<GameEngineObject>> ObjectLists = _Level->GetObjectGroupInt(0);

	//std::vector<std::shared_ptr<GameEngineObject>> Objects;

	//for (std::shared_ptr<GameEngineObject> Ptr : ObjectLists)
	//{
	//	Objects.push_back(Ptr);
	//}


	//if (Objects.size())
	//{
	//	std::vector<std::string> Names;

	//	for (std::shared_ptr<GameEngineObject> Ptr : Objects)
	//	{
	//		Names.push_back(Ptr->GetName());
	//	}

	//	//Names.push_back("aaaa");
	//	//Names.push_back("bbbb");

	//	std::vector<const char*> CNames;

	//	for (size_t i = 0; i < Names.size(); i++)
	//	{
	//		CNames.push_back(Names[i].c_str());
	//	}

	//	if (ImGui::ListBox("ObjectList", &Select, &CNames[0], static_cast<int>(Names.size())))
	//	{
	//		SelectObject = Objects[Select];
	//	}

	//	if (nullptr != SelectObject)
	//	{
	//		if (ImGui::Button("Select Object Off"))
	//		{
	//			SelectObject->Off();
	//		}

	//	}
	//}
}


void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	CurTab = Tabs[0];
	Tabs.push_back(std::make_shared<TestTab>("Debug"));

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
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
			CurTab->Start();
		}
		ImGui::SameLine();
	}

	if (ImGui::Button("Off"))
	{
		Off();
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}
}
