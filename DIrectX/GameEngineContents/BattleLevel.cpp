#include "PreCompile.h"
#include "BattleLevel.h"

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"

// GameUnit
#include "GameUnitUI.h"
#include "Knight.h"
#include "Swordman.h"
#include "Monk.h"
#include "Ninja.h"
#include "Archer.h"
#include "Pyromancer.h"
#include "Pythoness.h"


BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

}

void BattleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1'))
	{
		GameEngineLevel::DebugSwitch();
	}
}

void BattleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	{
		// ���� �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		// �̱� ��������Ʈ �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("stadium.png");
		GameEngineSprite::CreateSingle("stadium_sky_bg.png");
	}

	GameEngineRandom NewRandom;

	std::shared_ptr<BattleField> BF = CreateActor<BattleField>();

	// ���� ����
	
	// ������ ���� (������)
	RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	//RedTeam.push_back(CreateActor<Monk>()->GetPointer());
	//RedTeam.push_back(CreateActor<Pyromancer>()->GetPointer());
	RedTeam.push_back(CreateActor<Pythoness>()->GetPointer());




	// ����� ���� (����)
	BlueTeam.push_back(CreateActor<Swordman>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Monk>()->GetPointer());
	BlueTeam.push_back(CreateActor<Archer>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Ninja>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Pythoness>()->GetPointer());




	
	// ������
	for (size_t i = 0; i < RedTeam.size(); i++)
	{
		RedTeam[static_cast<int>(i)]->EnemyUnitSetting(BlueTeam);
		RedTeam[static_cast<int>(i)]->TeamUnitSetting(RedTeam);

		RedTeam[static_cast<int>(i)]->TeamSet(TeamType::Red);
	}

	for (size_t i = 0; i < BlueTeam.size(); i++)
	{
		BlueTeam[static_cast<int>(i)]->EnemyUnitSetting(RedTeam);
		BlueTeam[static_cast<int>(i)]->TeamUnitSetting(BlueTeam);

		BlueTeam[static_cast<int>(i)]->TeamSet(TeamType::Blue);
	}

	CreateActor<Bird>();
}

void BattleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}