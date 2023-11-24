#include "PreCompile.h"
#include "TitleLevel.h"

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"
#include "BanPickManager.h"

// UI
#include "StadiumBoard.h"

// GameUnit
#include "Knight.h"
#include "Swordman.h"
#include "Monk.h"
#include "Ninja.h"
#include "Archer.h"
#include "Pyromancer.h"
#include "Pythoness.h"
#include "Priest.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"
#include "Title_UI.h"


TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	//GameEngineRenderTarget::IsDepth = false;

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		if (nullptr == GameEngineSound::FindSound("StreetLove.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("StreetLove.WAV"));
		}
	}

	GameEngineInput::AddInputObject(this);

}

void TitleLevel::Update(float _Delta)
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("StreetLove.WAV");
	BGMPlayer.SetLoop(100);

	RandSeed = reinterpret_cast<long long>(this);
	RandSeed += Rand.RandomInt(0, 1000);
	Rand.SetSeed(RandSeed);

	std::shared_ptr<BattleField> BF = CreateActor<BattleField>();

	BlueUnitSetting();
	RedUnitSetting();

	// 팀설정
	for (size_t i = 0; i < BlueTeam.size(); i++)
	{
		BlueTeam[static_cast<int>(i)]->EnemyUnitSetting(RedTeam);
		BlueTeam[static_cast<int>(i)]->TeamUnitSetting(BlueTeam);
		BlueTeam[static_cast<int>(i)]->TeamSet(TeamType::Blue);
		BlueTeam[static_cast<int>(i)]->IsTitle = true;
	}

	for (size_t i = 0; i < RedTeam.size(); i++)
	{
		RedTeam[static_cast<int>(i)]->EnemyUnitSetting(BlueTeam);
		RedTeam[static_cast<int>(i)]->TeamUnitSetting(RedTeam);
		RedTeam[static_cast<int>(i)]->TeamSet(TeamType::Red);
		RedTeam[static_cast<int>(i)]->IsTitle = true;
	}

	CreateActor<Title_UI>();

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	//for (size_t i = 0; i < BlueTeam.size(); i++)
	//{
	//	BlueTeam[static_cast<int>(i)]->Death();

	//}

	//for (size_t i = 0; i < RedTeam.size(); i++)
	//{
	//	RedTeam[static_cast<int>(i)]->Death();

	//}

	BlueTeam.clear();
	RedTeam.clear();
	UseUnitName.clear();
	BGMPlayer.Stop();

}

void TitleLevel::BlueUnitSetting()
{
	std::string UnitName = CrateUnitName();

	BlueTeam.push_back(CrateUnit(UnitName)->GetPointer());
	UseUnitName.push_back(UnitName);

	for (size_t i = 0; i < 3; i++)
	{
		std::string CheckName = "";
		bool Check = false;

		while (UnitName != CheckName)
		{
			UnitName = CrateUnitName();
			// 이름 을 꺼내.
			for (size_t i = 0; i < UseUnitName.size(); i++)
			{
				// 확인했더니 있어. 다시 이름을꺼내.
				// 확인했더니 없어. 아래로 내려.
				if (i == UseUnitName.size() - 1)
				{
					CheckName = UnitName;
				}

				if (UnitName == UseUnitName[static_cast<int>(i)])
				{
					CheckName = "";
					break;
				}
			}

		}

		UseUnitName.push_back(UnitName);
		BlueTeam.push_back(CrateUnit(UnitName)->GetPointer());
	}
}

void TitleLevel::RedUnitSetting()
{
	std::string UnitName = CrateUnitName();

	for (size_t i = 0; i < 4; i++)
	{
		std::string CheckName = "";
		bool Check = false;

		while (UnitName != CheckName)
		{
			UnitName = CrateUnitName();
			// 이름 을 꺼내.
			for (size_t i = 0; i < UseUnitName.size(); i++)
			{
				// 확인했더니 있어. 다시 이름을꺼내.
				// 확인했더니 없어. 아래로 내려.
				if (i == UseUnitName.size() - 1)
				{
					CheckName = UnitName;
				}

				if (UnitName == UseUnitName[static_cast<int>(i)])
				{
					CheckName = "";
					break;
				}
			}

		}

		UseUnitName.push_back(UnitName);
		RedTeam.push_back(CrateUnit(UnitName)->GetPointer());
	}
}

std::string TitleLevel::CrateUnitName()
{
	RandSeed++;
	Rand.SetSeed(RandSeed);
	int Num = Rand.RandomInt(1, 8);

	if (1 == Num)
	{
		return "Archer";
	}
	if (2 == Num)
	{
		return "Knight";
	}
	if (3 == Num)
	{
		return  "Monk";
	}
	if (4 == Num)
	{
		return  "Pyromancer";
	}
	if (5 == Num)
	{
		return "Pythoness"; 
	}
	if (6 == Num)
	{
		return "Swordman";
	}
	if (7 == Num)
	{
		return "Priest";
	}
	if (8 == Num)
	{
		return "Ninja";
	}

	return "";
}

std::shared_ptr<GameUnit> TitleLevel::CrateUnit(std::string_view _Name)
{
	std::string Name = _Name.data();

	if ("Archer" == Name)
	{
		return CreateActor<Archer>();
	}
	if ("Knight" == Name)
	{
		return CreateActor<Knight>();
	}
	if ("Monk" == Name)
	{
		return CreateActor<Monk>();
	}
	if ("Pyromancer" == Name)
	{
		return CreateActor<Pyromancer>();
	}
	if ("Pythoness" == Name)
	{
		return CreateActor<Pythoness>();
	}
	if ("Swordman" == Name)
	{
		return CreateActor<Swordman>();
	}
	if ("Priest" == Name)
	{
		return CreateActor<Priest>();
	}
	if ("Ninja" == Name)
	{
		return CreateActor<Ninja>();
	}

	return nullptr;
}