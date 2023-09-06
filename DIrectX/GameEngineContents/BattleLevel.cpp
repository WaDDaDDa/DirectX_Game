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
	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


}

void BattleLevel::Update(float _Delta)
{

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


	// ������ ����
	RedTeam.push_back(CreateActor<Knight>()->GetPointer());
	RedTeam.push_back(CreateActor<Knight>()->GetPointer());

	// ����� ����
	BlueTeam.push_back(CreateActor<Knight>()->GetPointer());
	BlueTeam.push_back(CreateActor<Knight>()->GetPointer());
	
	// ������
	for (size_t i = 0; i < RedTeam.size(); i++)
	{
		RedTeam[static_cast<int>(i)]->EnemySetting(BlueTeam);
		float4 StartPos = NewRandom.RandomVectorBox2D(-200.0f, -180.0f, 0.0f, -100.0f);
		RedTeam[static_cast<int>(i)]->Transform.AddLocalPosition(StartPos);
	}

	for (size_t i = 0; i < BlueTeam.size(); i++)
	{
		BlueTeam[static_cast<int>(i)]->EnemySetting(RedTeam);

		BlueTeam[static_cast<int>(i)]->Transform.AddLocalRotation({ 0.0f, 180.0f });
		float4 StartPos = NewRandom.RandomVectorBox2D(200.0f, 180.0f, 0.0f, -100.0f);
		BlueTeam[static_cast<int>(i)]->Transform.AddLocalPosition(StartPos);
	}

}

void BattleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}