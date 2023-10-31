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

	// ���
	HeaderRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	HeaderRenderer->SetSprite("MainUI", 0);
	HeaderRenderer->AutoSpriteSizeOn();
	HeaderRenderer->SetAutoScaleRatio(2.0f);
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	HeaderRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });

	TeamButton = GetLevel()->CreateActor<MenuButton>();
	TeamButton->SetButtonText("�� ����");
	TeamButton->SetIcon("MainUI", 3);
	TeamButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	ManagerButton = GetLevel()->CreateActor<MenuButton>();
	ManagerButton->SetButtonText("�� ����");
	ManagerButton->SetIcon("MainUI", 3);
	ManagerButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	BattleButton = GetLevel()->CreateActor<MenuButton>();
	BattleButton->SetButtonText("�� ����");
	BattleButton->SetIcon("MainUI", 3);
	BattleButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	GameButton = GetLevel()->CreateActor<MenuButton>();
	GameButton->SetButtonText("�� ����");
	GameButton->SetIcon("MainUI", 3);
	GameButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

	SystemButton = GetLevel()->CreateActor<MenuButton>();
	SystemButton->SetButtonText("�� ����");
	SystemButton->SetIcon("MainUI", 3);
	SystemButton->Transform.AddLocalPosition(TeamButtonPos);
	TeamButtonPos += ButtonXInter;

}

void House_UI::Update(float _Delta)
{
	
}
