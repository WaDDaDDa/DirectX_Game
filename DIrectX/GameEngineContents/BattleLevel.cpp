#include "PreCompile.h"
#include "BattleLevel.h"

#include "GameUnit.h"
#include "Knight.h"
#include "BattleField.h"

BattleLevel::BattleLevel()
{

}

BattleLevel::~BattleLevel()
{

}

void BattleLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


}

void BattleLevel::Update(float _Delta)
{

}

void BattleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Test\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
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


	std::shared_ptr<BattleField> BF = CreateActor<BattleField>();

	// 레드팀 유닛
	std::shared_ptr<GameUnit> RedUnit1 = CreateActor<Knight>();
	//std::shared_ptr<GameUnit> RedUnit2 = CreateActor<Knight>();
	
	// 레드팀 스타트 위치셋팅
	RedUnit1->Transform.AddLocalPosition({-200.0f,0.0f});

	// 블루팀 유닛
	std::shared_ptr<GameUnit> BlueUnit1 = CreateActor<Knight>();
	//std::shared_ptr<GameUnit> BlueUnit2 = CreateActor<Knight>();

	// 블루팀 스타트 위치셋팅
	BlueUnit1->Transform.AddLocalRotation({0.0f, 180.0f});
	BlueUnit1->Transform.AddLocalPosition({ 200.0f,0.0f });

	// 팀설정
	RedUnit1->EnemySetting(BlueUnit1);
	BlueUnit1->EnemySetting(RedUnit1);

}

void BattleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}