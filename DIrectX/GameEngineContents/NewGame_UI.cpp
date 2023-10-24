#include "PreCompile.h"
#include "NewGame_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"

NewGame_UI::NewGame_UI()
{

}

NewGame_UI::~NewGame_UI()
{

}


void NewGame_UI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 100.0f });

	// UI 전체창
	NewGameBoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	NewGameBoxRenderer->SetSprite("new_game_ui_bg.png");
	NewGameBoxRenderer->AutoSpriteSizeOn();
	NewGameBoxRenderer->SetAutoScaleRatio(2.0f);
	NewGameBoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });

	// 로고 70개
	for (size_t i = 0; i < 70; i++)
	{
		TeamLogoButton.push_back(GetLevel()->CreateActor<SlotButton>());

		TeamLogoRenderer.push_back(TeamLogoButton[i]->CreateRenderer("TeamLogo", static_cast<unsigned int>(i), ContentsOrder::UIImage));
		TeamLogoRenderer[i]->SetSprite("TeamLogo", static_cast<unsigned int>(i));

		if (5 > LogoCount)
		{
			TeamLogoButton[i]->Transform.AddLocalPosition(TeamLogoStartPos + (XInter * static_cast<float>(LogoCount)));
		}
		else if (5 <= LogoCount)
		{
			TeamLogoButton[i]->Transform.AddLocalPosition(TeamLogoStartPos2 + (XInter * static_cast<float>(LogoCount - 5)));
		}

		LogoCount++;

		if (10 == LogoCount)
		{
			LogoCount = 0;
		}

		TeamLogoButton[i]->Off();
	}

	CurLogo = TeamLogoButton[CurNum];

	// 로고 페이지 화살표
	TeamLogoPrevArrow = GetLevel()->CreateActor<GreenArrow>();
	TeamLogoPrevArrow->Transform.AddLocalPosition(TeamLogoPrevArrowPos);

	TeamLogoNextArrow = GetLevel()->CreateActor<GreenArrow>();
	TeamLogoNextArrow->DirChange();
	TeamLogoNextArrow->Transform.AddLocalPosition(TeamLogoNextArrowPos);

	MyTeamLogoBg = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MyTeamLogoBg->CreateAnimation("Null", "ButtonSlot", 0.1f, 0, 0, false);
	MyTeamLogoBg->ChangeAnimation("Null");
	MyTeamLogoBg->AutoSpriteSizeOn();
	MyTeamLogoBg->SetAutoScaleRatio(2.0f);
	MyTeamLogoBg->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MyTeamLogoBg->Transform.AddLocalPosition(MyTeamLogoPos);

	MyTeamLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MyTeamLogo->SetSprite("TeamLogo");
	MyTeamLogo->AutoSpriteSizeOn();
	MyTeamLogo->SetAutoScaleRatio(2.0f);
	MyTeamLogo->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	MyTeamLogo->Transform.AddLocalPosition(MyTeamLogoPos);

}

void NewGame_UI::AllButtonOff()
{
	for (size_t i = 0; i < 70; i++)
	{
		TeamLogoButton[i]->Off();
	}
}

void NewGame_UI::Update(float _Delta)
{
	if (0 == TeamLogoPage)
	{
		TeamLogoPrevArrow->Off();
	}
	else
	{
		TeamLogoPrevArrow->On();
	}

	if (6 == TeamLogoPage)
	{
		TeamLogoNextArrow->Off();
	}
	else
	{
		TeamLogoNextArrow->On();
	}

	if (TeamLogoPrevArrow->GetIsClick())
	{
		AllButtonOff();
		TeamLogoPage -= 1;
	}

	if (TeamLogoNextArrow->GetIsClick())
	{
		AllButtonOff();
		TeamLogoPage += 1;
	}


	for (size_t i = 0; i < LogoSlot; i++)
	{
		CurNum = i + (TeamLogoPage * LogoSlot);

		TeamLogoButton[CurNum]->On();

		if (TeamLogoButton[CurNum]->GetIsClick())
		{
			// 로고 70개
			for (size_t i = 0; i < 70; i++)
			{
				TeamLogoButton[i]->IsSelectFalse();
			}

			TeamLogoButton[CurNum]->IsSelectTrue();

			CurLogo = TeamLogoButton[CurNum];
			MyTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(CurNum));
		}
	}


}
