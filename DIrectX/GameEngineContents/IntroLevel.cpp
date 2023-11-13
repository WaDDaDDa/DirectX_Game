#include "PreCompile.h"
#include "IntroLevel.h"
#include "IntroCut.h"
#include "UI_Mouse.h"
#include <GameEngineCore/FadePostEffect.h>


IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}

void IntroLevel::Start()
{
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	GameEngineFont::Load("Galmuri14");
	GameEngineFont::Load("Galmuri9");

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Intro\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("cutscene1.png");
		GameEngineSprite::CreateSingle("cutscene2.png");
		GameEngineSprite::CreateSingle("cutscene3.png");
		GameEngineSprite::CreateSingle("cutscene4.png");
		GameEngineSprite::CreateSingle("cutscene5.png");
		GameEngineSprite::CreateSingle("cutscene6.png");
		GameEngineSprite::CreateSingle("equipment_slot_bg_0.png");
		GameEngineSprite::CreateSingle("new_game_ui_bg.png");
		GameEngineSprite::CreateSingle("Black_0.png");
		GameEngineSprite::CreateSingle("IntroMask.png");
	}

	{
		// ���� �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\NewGame\\Logo\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
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

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	CreateActor<UI_Mouse>();
}

void IntroLevel::Update(float _Delta)
{

}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// ����Ʈ����Ʈ - ���̵�ƿ�
	//GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
	std::shared_ptr<IntroCut> NewIntro = CreateActor<IntroCut>();
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}