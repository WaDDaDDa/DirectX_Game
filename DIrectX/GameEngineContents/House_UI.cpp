#include "PreCompile.h"
#include "House_UI.h"
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

	// 바닥가림막
	GroundRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	GroundRenderer->SetSprite("House", 8);
	GroundRenderer->AutoSpriteSizeOn();
	GroundRenderer->SetAutoScaleRatio(3.0f);
	GroundRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	GroundRenderer->Transform.AddLocalPosition({ 0.0f, -335.0f , -200.0f});
	{
		TeamButton = GetLevel()->CreateActor<MenuButton>();
		TeamButton->SetButtonText("팀 관리");
		TeamButton->SetIcon("MainUI", 3);
		TeamButton->Transform.AddLocalPosition(TeamButtonPos);

		TeamPopMenu = GetLevel()->CreateActor<TeamBundle>();
		TeamButtonPos += ButtonXInter;
	}
	{
		ManagerButton = GetLevel()->CreateActor<MenuButton>();
		ManagerButton->SetButtonText("운영");
		ManagerButton->SetIcon("MainUI", 4);
		ManagerButton->Transform.AddLocalPosition(TeamButtonPos);

		ManagerPopMenu = GetLevel()->CreateActor<ManagerBundle>();
		ManagerPopMenu->Transform.AddLocalPosition(ButtonXInter);
		TeamButtonPos += ButtonXInter;
	}
	{
		BattleButton = GetLevel()->CreateActor<MenuButton>();
		BattleButton->SetButtonText("대회");
		BattleButton->SetIcon("MainUI", 5);
		BattleButton->Transform.AddLocalPosition(TeamButtonPos);

		BattlePopMenu = GetLevel()->CreateActor<BattleBundle>();
		BattlePopMenu->Transform.AddLocalPosition(ButtonXInter * 2.0f);

		TeamButtonPos += ButtonXInter;
	}
	{
		GameButton = GetLevel()->CreateActor<MenuButton>();
		GameButton->SetButtonText("게임");
		GameButton->SetIcon("MainUI", 6);
		GameButton->Transform.AddLocalPosition(TeamButtonPos);

		GamePopMenu = GetLevel()->CreateActor<GameBundle>();
		GamePopMenu->Transform.AddLocalPosition(ButtonXInter * 3.0f);

		TeamButtonPos += ButtonXInter;
	}
	{
		SystemButton = GetLevel()->CreateActor<MenuButton>();
		SystemButton->SetButtonText("시스템");
		SystemButton->SetIcon("MainUI", 7);
		SystemButton->Transform.AddLocalPosition(TeamButtonPos);
		SystemPopMenu = GetLevel()->CreateActor<SystemBundle>();
		SystemPopMenu->Transform.AddLocalPosition(ButtonXInter * 4.0f);
		TeamButtonPos += ButtonXInter;
	}

	Proceed = GetLevel()->CreateActor<ProceedButton>();
	Proceed->SetButtonText("경기장으로");
	Proceed->Transform.AddLocalPosition({480.0f, -290.0f});

	Day = GetLevel()->CreateActor<HeaderInfo>();
	Day->Transform.AddLocalPosition({ 920.0f, -35.0f });
	Day->SetIcon("MainUI", 1);
	Day->SetText(TeamInfo::MyInfo.GetDate());

	Gold = GetLevel()->CreateActor<HeaderInfo>();
	Gold->Transform.AddLocalPosition({ 1150.0f, -35.0f });
	Gold->SetIcon("MainUI", 2);
	Gold->SetText(std::to_string(TeamInfo::MyInfo.GetGold()));

	TeamLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	TeamLogo->SetSprite("TeamLogo", TeamInfo::MyInfo.GetIconNum());
	TeamLogo->AutoSpriteSizeOn();
	TeamLogo->SetAutoScaleRatio(2.0f);
	TeamLogo->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	TeamLogo->Transform.AddLocalPosition({-590.0f, 325.0f});

	GameEngineInput::AddInputObject(this);
}

void House_UI::LevelStart(GameEngineLevel* _PrevLevel)
{
	TeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
}


void House_UI::PopBundle(std::shared_ptr<class MenuButton> _Menu, std::shared_ptr<class ButtonBundle> _Bundle)
{
	if (true == _Menu->GetIsClick() && true == _Bundle->IsPopUp)
	{
		_Bundle->State.ChangeState(BundleState::PopDown);
		_Menu->IsSelectFalse();
	}
	else if (true == _Menu->GetIsClick() && false == _Bundle->IsPopUp)
	{
		_Bundle->State.ChangeState(BundleState::PopUp);
		_Menu->IsSelectTrue();
	}
	//else if (true == _Bundle->IsPopUp && true == GameEngineInput::IsDown(VK_LBUTTON, this))
	//{
	//	if (true == _Bundle->IsButtonsClick())
	//	{
	//		return;
	//	}
	//	_Bundle->State.ChangeState(BundleState::PopDown);
	//	_Menu->IsSelectFalse();
	//}
	//else if (true == _Bundle->IsPopUp && true == GameEngineInput::IsDown(VK_LBUTTON, this))
	//{
	//	//_Bundle->State.ChangeState(BundleState::PopDown);
	//	//_Menu->IsSelectFalse();
	//}
}


void House_UI::Update(float _Delta)
{
	PopBundle(TeamButton, TeamPopMenu);
	PopBundle(ManagerButton, ManagerPopMenu);
	PopBundle(BattleButton, BattlePopMenu);
	PopBundle(GameButton, GamePopMenu);
	PopBundle(SystemButton, SystemPopMenu);

	if (true == Proceed->GetIsClick() && true == BattlePhase)
	{
		GameEngineCore::ChangeLevel("BanPickLevel");
		return;
	}
	else if (true == Proceed->GetIsClick() && false == BattlePhase)
	{
		BattlePhase = true;
		GameEngineCore::ChangeLevel("MainLevel");
		return;
	}
}
