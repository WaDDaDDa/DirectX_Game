#include "PreCompile.h"
#include "BattleLevel.h"

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"
#include "BanPickManager.h"
#include "StadiumLevel.h"

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


BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Start()
{
	//GameEngineRenderTarget::IsDepth = false;

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		if (nullptr == GameEngineSound::FindSound("Loop_Electronic001.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("Loop_Electronic001.WAV"));
		}
	}

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	GameEngineInput::AddInputObject(this);
}

void BattleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1', this))
	{
		GameEngineLevel::DebugSwitch();
		//GameEngineCore::MainTime.SetAllTimeScale(5.0f);
		//SetAllTimeScale
	}
}

void BattleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	if ("Loop_Electronic001.WAV" != StadiumLevel::BGMPlayer.GetCurSoundName())
	{
		StadiumLevel::BGMPlayer.Stop();
		StadiumLevel::BGMPlayer = GameEngineSound::SoundPlay("Loop_Electronic001.WAV");
		StadiumLevel::BGMPlayer.SetLoop(100);
	}

	std::shared_ptr<BattleField> BF = CreateActor<BattleField>();

	UnitSetting();

	CreateActor<Bird>();

	CreateActor<StadiumBoard>()->Setting(BlueTeam, RedTeam);
}

void BattleLevel::LevelEnd(GameEngineLevel* _NextLevel)
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

}

void BattleLevel::UnitSetting()
{
	size_t BSize = BanPickInfo::Info.BlueTeamPick.size();
	size_t RSize = BanPickInfo::Info.BlueTeamPick.size();
	
	for (size_t i = 0; i < BSize; i++)
	{
		std::shared_ptr<GameUnit> Unit = CrateUnit(BanPickInfo::Info.BlueTeamPick[static_cast<int>(i)]);

		if (0 == i)
		{
			Unit->SetPlayerSpec(TeamInfo::MyInfo.OnePlayer->GetSpec());
		}
		if (1 == i)
		{
			Unit->SetPlayerSpec(TeamInfo::MyInfo.TwoPlayer->GetSpec());
		}

		BlueTeam.push_back(Unit->GetPointer());
	}
	for (size_t i = 0; i < RSize; i++)
	{
		std::shared_ptr<GameUnit> Unit = CrateUnit(BanPickInfo::Info.RedTeamPick[static_cast<int>(i)]);
		
		if (0 == i)
		{
			Unit->SetPlayerSpec(EnemyInfo::Info.GetOnePlayer());
		}
		if (1 == i)
		{
			Unit->SetPlayerSpec(EnemyInfo::Info.GetTwoPlayer());
		}
		RedTeam.push_back(Unit->GetPointer());
	}

	// 팀설정
	for (size_t i = 0; i < BlueTeam.size(); i++)
	{
		BlueTeam[static_cast<int>(i)]->EnemyUnitSetting(RedTeam);
		BlueTeam[static_cast<int>(i)]->TeamUnitSetting(BlueTeam);
		BlueTeam[static_cast<int>(i)]->TeamSet(TeamType::Blue);
	}

	for (size_t i = 0; i < RedTeam.size(); i++)
	{
		RedTeam[static_cast<int>(i)]->EnemyUnitSetting(BlueTeam);
		RedTeam[static_cast<int>(i)]->TeamUnitSetting(RedTeam);
		RedTeam[static_cast<int>(i)]->TeamSet(TeamType::Red);
	}
}

std::shared_ptr<GameUnit> BattleLevel::CrateUnit(std::string_view _Name)
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