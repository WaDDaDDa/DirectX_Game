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
		GameEngineSprite::CreateSingle("stadium_bg.png");
		GameEngineSprite::CreateSingle("stadium_frame.png");
		GameEngineSprite::CreateSingle("stadium_chair.png");
		GameEngineSprite::CreateSingle("stadium_desk.png");
		GameEngineSprite::CreateSingle("stadium_frame_front.png");
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
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
}

void StadiumLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
