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

	{
		// 폴더 로드
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
		// 싱글 스프라이트 로드
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
		GameEngineSprite::CreateSingle("stadium_VS.png");
		GameEngineSprite::CreateSingle("win_indicator_0.png");
		GameEngineSprite::CreateSingle("win_indicator_1.png");
	}

	{
		// 싱글 스프라이트 아이콘
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Icon");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("armor_icon.png");
		GameEngineSprite::CreateSingle("attack_icon.png");
	}

	GameEngineRandom NewRandom;

	std::shared_ptr<BattleField> BF = CreateActor<BattleField>();

	// 유닛 생성
	// 블루팀 유닛 (왼쪽)
	BlueTeam.push_back(CreateActor<Ninja>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Archer>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Pyromancer>()->GetPointer());
	BlueTeam.push_back(CreateActor<Swordman>()->GetPointer());
	//BlueTeam.push_back(CreateActor<Pythoness>()->GetPointer());


		// 레드팀 유닛 (오른쪽)
	RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	//RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	//RedTeam.push_back(CreateActor<Priest>()->GetPointer());
	RedTeam.push_back(CreateActor<Archer>()->GetPointer());
	//RedTeam.push_back(CreateActor<Archer>()->GetPointer());

	
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