#include "PreCompile.h"
#include "BanPickLevel.h"
#include "BanPickManager.h"
#include "UI_Mouse.h"
#include "StadiumLevel.h"
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
	//메인카메라 위치잡기
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	//UI도 같은 위치로잡기
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
		// 폴더 로드
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

	if ("Stupid_Dancer.WAV" != StadiumLevel::BGMPlayer.GetCurSoundName())
	{
		StadiumLevel::BGMPlayer.Stop();
		StadiumLevel::BGMPlayer = GameEngineSound::SoundPlay("Stupid_Dancer.WAV");
		StadiumLevel::BGMPlayer.SetLoop(100);
	}


	CreateActor<UI_Mouse>();

	CreateActor<BanPickManager>();

	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();

}

void BanPickLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}