#include "PreCompile.h"
#include "ResultLevel.h"
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
#include "ResultBoard.h"

ResultLevel::ResultLevel()
{

}

ResultLevel::~ResultLevel()
{

}

void ResultLevel::Start()
{

	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != Window)
	{
		Window->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// 카메라의 위치를 화면의 왼쪽맨위에 0,0이 위치하도록 자리를 잡는다.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void ResultLevel::Update(float _Delta)
{

}

void ResultLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<UI_Mouse>();

	CreateActor<ResultBoard>();

	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();
}

void ResultLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
