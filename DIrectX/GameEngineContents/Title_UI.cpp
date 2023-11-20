#include "PreCompile.h"
#include "Title_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "ButtonBundle.h"
#include "TeamBundle.h"
#include "ManagerBundle.h"
#include "BattleBundle.h"
#include "GameBundle.h"
#include "SystemBundle.h"
#include "ProceedButton.h"
#include "HeaderInfo.h"
#include "TeamInfo.h"
#include <GameEngineCore/FadePostEffect.h>
#include "FadeEffect.h"
#include "EnemyInfo.h"


Title_UI::Title_UI()
{

}

Title_UI::~Title_UI()
{

}

void Title_UI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 0.0f });

	// ∏ﬁ¿Œ
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->SetSprite("teamfight_manager_title_bg.png");
	Renderer->SetImageScale({ 1280.0f, 720.0f });

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f });

	LogoRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	LogoRenderer->SetSprite("logo_tp.png");
	LogoRenderer->AutoSpriteSizeOn();
	LogoRenderer->SetAutoScaleRatio(2.0f);
	LogoRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	LogoRenderer->Transform.AddLocalPosition({ 0.0f, 200.0f });


	GameEngineInput::AddInputObject(this);
}

void Title_UI::LevelStart(GameEngineLevel* _PrevLevel)
{

}


void Title_UI::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		FadeOutEffect = GetLevel()->GetLevelRenderTarget()->CreateEffect<FadeEffect>();
		FadeOutEffect->SetChangeLevelName("IntroLevel");
		return;
	}

}

void Title_UI::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != FadeOutEffect)
	{
		FadeOutEffect->Death();
		FadeOutEffect = nullptr;
	}
}

