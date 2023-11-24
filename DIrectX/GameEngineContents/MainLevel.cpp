#include "PreCompile.h"
#include "MainLevel.h"
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

MainLevel::MainLevel()
{

}

MainLevel::~MainLevel()
{

}

void MainLevel::Start()
{

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

	{
		// 폴더 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\MainHouse\\");
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
		GameEngineSprite::CreateSingle("banpick_ui_bg.png");
	}

	{
		if (nullptr == GameEngineSound::FindSound("InfiniteDoors.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("InfiniteDoors.WAV"));
		}
	}

	//GameEngineRenderTarget::IsDepth = false;

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	// GameEngineInput::AddInputObject(this);
	CreateActor<UI_Mouse>();

	CreateActor<HouseBackGround>();
	CreateActor<House>();
	CreateActor<House_UI>();

	TeamInfo::MyInfo.SetCoach(CreateActor<Coach>());
	TeamInfo::MyInfo.AddPlayer(CreateActor<GamePlayer>());
	TeamInfo::MyInfo.AddPlayer(CreateActor<GamePlayer>());
	TeamInfo::MyInfo.AddPlayer(CreateActor<GamePlayer>());

	std::list<std::shared_ptr<class GamePlayer>>& PlayerGroup = TeamInfo::MyInfo.GetMyPlayer();

	std::list<std::shared_ptr<GamePlayer>>::iterator Start = PlayerGroup.begin();
	std::list<std::shared_ptr<GamePlayer>>::iterator End = PlayerGroup.end();

	TeamInfo::MyInfo.OnePlayer = (*Start);
	Start++;
	TeamInfo::MyInfo.TwoPlayer = (*Start);

}

void MainLevel::Update(float _Delta)
{

}

void MainLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();

	BGMPlayer = GameEngineSound::SoundPlay("InfiniteDoors.WAV");
	BGMPlayer.SetLoop(100);
}

void MainLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

}
