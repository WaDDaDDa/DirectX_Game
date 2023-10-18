#include "PreCompile.h"
#include "BanPickLevel.h"
#include "BanPickManager.h"
#include "UI_Mouse.h"
// UI


// GameUnit


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

	CreateActor<UI_Mouse>();
}

void BanPickLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1', this))
	{
		GameEngineLevel::DebugSwitch();
	}
	
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
		return;
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
		// ���Ȱ��� �����ܵ�(���)
		GameEngineSprite::CreateSingle("ingame_stat_icon_0.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_1.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_2.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_3.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_4.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_5.png");
		GameEngineSprite::CreateSingle("patch_icons_1.png");
		GameEngineSprite::CreateSingle("TestMask.png");


		// ���ݹ�� �����ܵ�
		GameEngineSprite::CreateSingle("armor_icon.png");
		GameEngineSprite::CreateSingle("attack_icon.png");

		// ���� �����ܵ�
		GameEngineSprite::CreateSingle("Archer_ult.png");
		GameEngineSprite::CreateSingle("Archer_skill.png");
		GameEngineSprite::CreateSingle("arrow.png");
		GameEngineSprite::CreateSingle("knight_ult.png");
		GameEngineSprite::CreateSingle("knight_skill.png");
		GameEngineSprite::CreateSingle("Monk_ult.png");
		GameEngineSprite::CreateSingle("Monk_skill.png");
		GameEngineSprite::CreateSingle("Ninja_ult.png");
		GameEngineSprite::CreateSingle("Ninja_skill.png");
		GameEngineSprite::CreateSingle("Priest_ult.png");
		GameEngineSprite::CreateSingle("Priest_skill.png");
		GameEngineSprite::CreateSingle("Pyromancer_ult.png");
		GameEngineSprite::CreateSingle("Pyromancer_skill.png");
		GameEngineSprite::CreateSingle("Pythoness_ult.png");
		GameEngineSprite::CreateSingle("Pythoness_skill.png");
		GameEngineSprite::CreateSingle("swordman_ult.png");
		GameEngineSprite::CreateSingle("swordman_skill.png");

	}

	CreateActor<BanPickManager>();

}

void BanPickLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}