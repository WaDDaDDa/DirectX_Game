#include "PreCompile.h"
#include "IntroLevel.h"
#include "IntroCut.h"


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
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<IntroCut> NewIntro = CreateActor<IntroCut>();
}

void IntroLevel::Update(float _Delta)
{

}

void IntroLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	
}

void IntroLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}