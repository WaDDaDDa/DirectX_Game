#include "PreCompile.h"
#include "House_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "TeamBundle.h"

House_UI::House_UI()
{

}

House_UI::~House_UI()
{

}

void House_UI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	// 헤더
	HeaderRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	HeaderRenderer->SetSprite("MainUI", 0);
	HeaderRenderer->AutoSpriteSizeOn();
	HeaderRenderer->SetAutoScaleRatio(2.0f);
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });

	TeamButton = GetLevel()->CreateActor<MenuButton>();
	TeamButton->SetButtonText("팀 관리");
	TeamButton->SetIcon("MainUI", 3);
	TeamButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	ManagerButton = GetLevel()->CreateActor<MenuButton>();
	ManagerButton->SetButtonText("운영");
	ManagerButton->SetIcon("MainUI", 4);
	ManagerButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	BattleButton = GetLevel()->CreateActor<MenuButton>();
	BattleButton->SetButtonText("대회");
	BattleButton->SetIcon("MainUI", 5);
	BattleButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	GameButton = GetLevel()->CreateActor<MenuButton>();
	GameButton->SetButtonText("게임");
	GameButton->SetIcon("MainUI", 6);
	GameButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	SystemButton = GetLevel()->CreateActor<MenuButton>();
	SystemButton->SetButtonText("시스템");
	SystemButton->SetIcon("MainUI", 7);
	SystemButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	TeamPopMenu = GetLevel()->CreateActor<TeamBundle>();
}

void House_UI::Update(float _Delta)
{
	//TeamPopMenu->Transform.AddLocalPosition(float4::RIGHT * _Delta * 100.0f);
}
