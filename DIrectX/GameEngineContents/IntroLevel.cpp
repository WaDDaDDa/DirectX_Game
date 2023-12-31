#include "PreCompile.h"
#include "IntroLevel.h"
#include "IntroCut.h"
#include "UI_Mouse.h"
#include <GameEngineCore/FadePostEffect.h>
#include "EnemyInfo.h"


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
		// 폴더 로드
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
		// 스탯관련 아이콘들(흑백)
		GameEngineSprite::CreateSingle("ingame_stat_icon_0.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_1.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_2.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_3.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_4.png");
		GameEngineSprite::CreateSingle("ingame_stat_icon_5.png");
		GameEngineSprite::CreateSingle("patch_icons_1.png");
		GameEngineSprite::CreateSingle("TestMask.png");


		// 공격방어 아이콘들
		GameEngineSprite::CreateSingle("armor_icon.png");
		GameEngineSprite::CreateSingle("attack_icon.png");

		// 유닛 아이콘들
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

	{
		if (nullptr == GameEngineSound::FindSound("BGM_Chunky_Monkey.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("BGM_Chunky_Monkey.WAV"));
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
		GameEngineSprite::CreateSingle("banpick_ui_bg.png");
		GameEngineSprite::CreateSingle("stadium_bg.png");
		GameEngineSprite::CreateSingle("stadium_frame.png");
		GameEngineSprite::CreateSingle("stadium_chair.png");
		GameEngineSprite::CreateSingle("stadium_desk.png");
		GameEngineSprite::CreateSingle("stadium_frame_front.png");
		GameEngineSprite::CreateSingle("set_result_ui_bg.png");
		GameEngineSprite::CreateSingle("teamfight_manager_title_bg.png");
		GameEngineSprite::CreateSingle("logo_tp.png");	
		GameEngineSprite::CreateSingle("tmouse_curosr.png");
	}




	EnemyInfo::Info.Init();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();


	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
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
	// 포스트이펙트 - 페이드아웃
	//GetLevelRenderTarget()->CreateEffect<FadePostEffect>();

	BGMPlayer = GameEngineSound::SoundPlay("BGM_Chunky_Monkey.WAV");
	BGMPlayer.SetLoop(100);

	std::shared_ptr<IntroCut> NewIntro = CreateActor<IntroCut>();
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}