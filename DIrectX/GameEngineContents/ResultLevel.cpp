#include "PreCompile.h"
#include "ResultLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>

#include "GameUnit.h"
#include "BattleField.h"
#include "Bird.h"
#include "BanPickManager.h"
#include "UI_Mouse.h"
#include "StadiumLevel.h"

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
	// ī�޶��� ��ġ�� ȭ���� ���ʸ����� 0,0�� ��ġ�ϵ��� �ڸ��� ��´�.
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void ResultLevel::Update(float _Delta)
{

}

void ResultLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if ("Loop_Electronic001.WAV" != StadiumLevel::BGMPlayer.GetCurSoundName())
	{
		StadiumLevel::BGMPlayer.Stop();
		StadiumLevel::BGMPlayer = GameEngineSound::SoundPlay("Loop_Electronic001.WAV");
		StadiumLevel::BGMPlayer.SetLoop(100);
	}

	CreateActor<UI_Mouse>();

	CreateActor<ResultBoard>();

	std::shared_ptr<class FadeEffect> FadeInEffect = GetLevelRenderTarget()->CreateEffect<FadeEffect>();
	FadeInEffect->SetFadeIn();
}

void ResultLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
