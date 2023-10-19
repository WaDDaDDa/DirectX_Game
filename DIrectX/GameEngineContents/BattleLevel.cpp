#include "PreCompile.h"
#include "BattleLevel.h"

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

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	GameEngineInput::AddInputObject(this);

}

void BattleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1', this))
	{
		GameEngineLevel::DebugSwitch();
	}
}

void BattleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	GameEngineRandom NewRandom;

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

	int a = 0;
}

void BattleLevel::UnitSetting()
{
	size_t BSize = BanPickInfo::Info.BlueTeamPick.size();
	size_t RSize = BanPickInfo::Info.BlueTeamPick.size();

	
	for (size_t i = 0; i < BSize; i++)
	{
		std::shared_ptr<GameUnit> Unit = CrateUnit(BanPickInfo::Info.BlueTeamPick[i]);
		BlueTeam.push_back(Unit->GetPointer());
	}
	for (size_t i = 0; i < RSize; i++)
	{
		std::shared_ptr<GameUnit> Unit = CrateUnit(BanPickInfo::Info.RedTeamPick[i]);
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

}