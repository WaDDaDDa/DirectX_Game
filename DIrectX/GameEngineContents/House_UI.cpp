#include "PreCompile.h"
#include "House_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"

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

	// 庆歹
	HeaderRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	HeaderRenderer->SetSprite("MainUI", 0);
	HeaderRenderer->AutoSpriteSizeOn();
	HeaderRenderer->SetAutoScaleRatio(2.0f);
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });

	TeamButton = GetLevel()->CreateActor<MenuButton>();
	TeamButton->SetButtonText("评 包府");
	TeamButton->SetIcon("MainUI", 3);
	TeamButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	ManagerButton = GetLevel()->CreateActor<MenuButton>();
	ManagerButton->SetButtonText("评 包府");
	ManagerButton->SetIcon("MainUI", 3);
	ManagerButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	BattleButton = GetLevel()->CreateActor<MenuButton>();
	BattleButton->SetButtonText("评 包府");
	BattleButton->SetIcon("MainUI", 3);
	BattleButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	GameButton = GetLevel()->CreateActor<MenuButton>();
	GameButton->SetButtonText("评 包府");
	GameButton->SetIcon("MainUI", 3);
	GameButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	SystemButton = GetLevel()->CreateActor<MenuButton>();
	SystemButton->SetButtonText("评 包府");
	SystemButton->SetIcon("MainUI", 3);
	SystemButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

}

void House_UI::Update(float _Delta)
{
	
}
