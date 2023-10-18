#include "PreCompile.h"
#include "BattleLevel.h"

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"

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
	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
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

	// ���� ����
	// ����� ���� (����)
	BlueTeam.push_back(CreateActor<Ninja>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Archer>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Pyromancer>()->GetPointer());
	BlueTeam.push_back(CreateActor<Swordman>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Pythoness>()->GetPointer());


		// ������ ���� (������)
	RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	//RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	//RedTeam.push_back(CreateActor<Priest>()->GetPointer());
	RedTeam.push_back(CreateActor<Archer>()->GetPointer());
	//RedTeam.push_back(CreateActor<Archer>()->GetPointer());

	
	// ������
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