#include "PreCompile.h"
#include "IntroLevel.h"
#include "IntroCut.h"
#include "UI_Mouse.h"

IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}

void IntroLevel::Start()
{
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Intro");

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
	std::shared_ptr<IntroCut> NewIntro = CreateActor<IntroCut>();
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}