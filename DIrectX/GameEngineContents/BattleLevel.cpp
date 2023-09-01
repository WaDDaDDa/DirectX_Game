#include "PreCompile.h"
#include "BattleLevel.h"

#include "GameUnit.h"

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

	}


	std::shared_ptr<GameUnit> NewPlayer = CreateActor<GameUnit>();
}

void BattleLevel::Update(float _Delta)
{

}

void BattleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void BattleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}