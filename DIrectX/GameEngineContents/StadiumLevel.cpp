#include "PreCompile.h"
#include "StadiumLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"
#include "BanPickManager.h"
#include "UI_Mouse.h"

#include "TeamInfo.h"
#include "HouseBackGround.h"
#include "House.h"
#include "House_UI.h"
#include "Coach.h"
#include "GamePlayer.h"
#include "Stadium.h"
#include "Audience.h"

class GameEngineSoundPlayer StadiumLevel::BGMPlayer;


StadiumLevel::StadiumLevel()
{

}

StadiumLevel::~StadiumLevel()
{

}

void StadiumLevel::Start()
{

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
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
	}

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
		if (nullptr == GameEngineSound::FindSound("Stupid_Dancer.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("Stupid_Dancer.WAV"));
		}
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	CreateActor<Stadium>();
}

void StadiumLevel::Update(float _Delta)
{

}

void StadiumLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	for (size_t i = 0; i < 300; i++)
	{
		CreateActor<Audience>();
	}

	if (nullptr == FadeInEffect)
	{
		FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
		FadeInEffect->SetFadeIn();
	}

	StadiumLevel::BGMPlayer = GameEngineSound::SoundPlay("Stupid_Dancer.WAV");
	StadiumLevel::BGMPlayer.SetLoop(100);
}

void StadiumLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != FadeInEffect)
	{
		FadeInEffect->Death();
		FadeInEffect = nullptr;
	}

}
