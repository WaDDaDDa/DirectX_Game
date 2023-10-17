#include "PreCompile.h"
#include "BanPickLevel.h"

// UI
#include "BanPickBoard.h"
#include "UI_Mouse.h"
#include "UI_Button.h"


// GameUnit
#include "BanPickCard.h"


BanPickLevel::BanPickLevel()
{

}

BanPickLevel::~BanPickLevel()
{

}

void BanPickLevel::Start()
{
	//GameEngineRenderTarget::IsDepth = false;
	//����ī�޶� ��ġ���
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	//UI�� ���� ��ġ�����
	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	GameEngineInput::AddInputObject(this);

}

void BanPickLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1', this))
	{
		GameEngineLevel::DebugSwitch();
	}
}

void BanPickLevel::LevelStart(GameEngineLevel* _PrevLevel)
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
		// ���� �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\UI\\");
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
		GameEngineSprite::CreateSingle("stadium_VS.png");
		GameEngineSprite::CreateSingle("win_indicator_0.png");
		GameEngineSprite::CreateSingle("win_indicator_1.png");
		GameEngineSprite::CreateSingle("banpick_ui_bg.png");
	}

	{
		// �̱� ��������Ʈ ������
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

	CreateActor<UI_Mouse>();

	CreateActor<BanPickBoard>();
	CreateActor<BanPickCard>()->Init(ArcherStatus::ArcherStat);
	CreateActor<BanPickCard>()->Init(KnightStatus::KnightStat);
	CreateActor<BanPickCard>()->Init(MonkStatus::MonkStat);
	CreateActor<BanPickCard>()->Init(NinjaStatus::NinjaStat);
	CreateActor<BanPickCard>()->Init(PyromancerStatus::PyromancerStat);
	CreateActor<BanPickCard>()->Init(PriestStatus::PriestStat);
	CreateActor<BanPickCard>()->Init(SwordmanStatus::SwordmanStat);
	CreateActor<BanPickCard>()->Init(PythonessStatus::PythonessStat);
}

void BanPickLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}