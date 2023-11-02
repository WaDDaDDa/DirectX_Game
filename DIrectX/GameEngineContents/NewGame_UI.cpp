#include "PreCompile.h"
#include "NewGame_UI.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "TeamInfo.h"

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
	CurLogo->IsSelectTrue();

	// 로고 페이지 화살표
	TeamLogoPrevArrow = GetLevel()->CreateActor<GreenArrow>();
	TeamLogoPrevArrow->Transform.AddLocalPosition(TeamLogoPrevArrowPos);

	TeamLogoNextArrow = GetLevel()->CreateActor<GreenArrow>();
	TeamLogoNextArrow->DirChange();
	TeamLogoNextArrow->Transform.AddLocalPosition(TeamLogoNextArrowPos);

	// 내가 선택한 로고
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

	// 코치 마네킹
	MyCoachHairBg = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MyCoachHairBg->CreateAnimation("Null", "ButtonSlot", 0.1f, 0, 0, false);
	MyCoachHairBg->ChangeAnimation("Null");
	MyCoachHairBg->AutoSpriteSizeOn();
	MyCoachHairBg->SetAutoScaleRatio(2.0f);
	MyCoachHairBg->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MyCoachHairBg->Transform.AddLocalPosition(MyCoachPos);

	MyCoach = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	MyCoach->SetSprite("Character_Coach");
	MyCoach->AutoSpriteSizeOn();
	MyCoach->SetAutoScaleRatio(2.0f);
	MyCoach->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	MyCoach->Transform.AddLocalPosition(MyCoachPos);

	// 내 코치 머리
	MyCoachHair = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MyCoachHair->SetSprite("Coach_Hair");
	MyCoachHair->AutoSpriteSizeOn();
	MyCoachHair->SetAutoScaleRatio(2.0f);
	MyCoachHair->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	MyCoachHair->Transform.AddLocalPosition(MyCoachHairPos);
	//MyCoachHair->SetPivotType(PivotType::LeftTop);

	// 헤어 30개
	for (size_t i = 0; i < 30; i++)
	{
		CoachHair.push_back(GetLevel()->CreateActor<SlotButton>());

		CoachHairRenderer.push_back(CoachHair[i]->CreateRenderer("Coach_Hair", static_cast<unsigned int>(i), ContentsOrder::UIImage));
		CoachHairRenderer[i]->SetSprite("Coach_Hair", static_cast<unsigned int>(i));

		if (5 > HairCount)
		{
			CoachHair[i]->Transform.AddLocalPosition(CoachHairStartPos + (XInter * static_cast<float>(HairCount)));
		}
		else if (5 <= HairCount)
		{
			CoachHair[i]->Transform.AddLocalPosition(CoachHairStartPos2 + (XInter * static_cast<float>(HairCount - 5)));
		}

		HairCount++;

		if (10 == HairCount)
		{
			HairCount = 0;
		}

		CoachHair[i]->Off();
	}

	CurHair = CoachHair[CurNum];
	CurHair->IsSelectTrue();

	// 헤어 페이지 화살표
	HairPrevArrow = GetLevel()->CreateActor<GreenArrow>();
	HairPrevArrow->Transform.AddLocalPosition(HairPrevArrowPos);
	
	HairNextArrow = GetLevel()->CreateActor<GreenArrow>();
	HairNextArrow->DirChange();
	HairNextArrow->Transform.AddLocalPosition(HairNextArrowPos);

	StartButton = GetLevel()->CreateActor<Default_Button>();
	StartButton->Transform.AddLocalPosition(StartButtonPos);
	StartButton->IsImportantTrue();
	StartButton->SetButtonText("게임 시작");

	ExitButton = GetLevel()->CreateActor<Default_Button>();
	ExitButton->Transform.AddLocalPosition(ExitButtonPos);
	ExitButton->SetButtonText("취소");

	// Text
	NewGameText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	NewGameText->SetText("Galmuri14", "새 게임", 35.0f, float4::WHITE, FW1_CENTER);
	NewGameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	NewGameText->Transform.AddLocalPosition({ 0.0f, 232.0f});

	TeamNameText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	TeamNameText->SetText("Galmuri14", "팀 이름", 25.0f, float4::WHITE, FW1_CENTER);
	TeamNameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	TeamNameText->Transform.AddLocalPosition({ -220.0f, 165.0f });

	CoachNameText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	CoachNameText->SetText("Galmuri14", "감독 이름", 25.0f, float4::WHITE, FW1_CENTER);
	CoachNameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	CoachNameText->Transform.AddLocalPosition({ 220.0f, 165.0f });

	TeamLogoText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	TeamLogoText->SetText("Galmuri14", "팀 로고", 25.0f, float4::WHITE, FW1_CENTER);
	TeamLogoText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	TeamLogoText->Transform.AddLocalPosition({ -220.0f, 18.0f });

	CoachHairText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	CoachHairText->SetText("Galmuri14", "감독 외형", 25.0f, float4::WHITE, FW1_CENTER);
	CoachHairText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	CoachHairText->Transform.AddLocalPosition({ 220.0f, 18.0f });

}

void NewGame_UI::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void NewGame_UI::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void NewGame_UI::AllButtonOff()
{
	for (size_t i = 0; i < 70; i++)
	{
		TeamLogoButton[i]->Off();
	}
}

void NewGame_UI::AllHairButtonOff()
{
	for (size_t i = 0; i < 30; i++)
	{
		CoachHair[i]->Off();
	}
}


void NewGame_UI::Update(float _Delta)
{
	// 팀 로고 페이지 변경
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
	else if (TeamLogoNextArrow->GetIsClick())
	{
		AllButtonOff();
		TeamLogoPage += 1;
	}
	else if (StartButton->GetIsClick())
	{
		TeamInfo::MyInfo.SetIconNum(static_cast<int>(CurNum));
		TeamInfo::MyInfo.SetHairNum(static_cast<int>(CurHairNum));
		GameEngineCore::ChangeLevel("MainLevel");
		// 커넘버 넘겨준다.
		return;
	}
	else if (ExitButton->GetIsClick())
	{
		GameEngineCore::ChangeLevel("IntroLevel");
		return;
	}

	// 헤어 페이지 변경
	if (0 == HairPage)
	{
		HairPrevArrow->Off();
	}
	else
	{
		HairPrevArrow->On();
	}

	if (2 == HairPage)
	{
		HairNextArrow->Off();
	}
	else
	{
		HairNextArrow->On();
	}

	if (HairPrevArrow->GetIsClick())
	{
		AllHairButtonOff();
		HairPage -= 1;
	}

	if (HairNextArrow->GetIsClick())
	{
		AllHairButtonOff();
		HairPage += 1;
	}

	// 팀로고 온오프
	for (size_t i = 0; i < LogoSlot; i++)
	{
		size_t IconNum = i + (TeamLogoPage * LogoSlot);

		TeamLogoButton[IconNum]->On();

		if (TeamLogoButton[IconNum]->GetIsClick())
		{
			// 로고 70개
			for (size_t i = 0; i < 70; i++)
			{
				TeamLogoButton[i]->IsSelectFalse();
			}
			CurNum = IconNum;

			TeamLogoButton[CurNum]->IsSelectTrue();

			CurLogo = TeamLogoButton[CurNum];
			MyTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(CurNum));
		}
	}

	// 헤어 온오프
	for (size_t i = 0; i < HairSlot; i++)
	{
		size_t HairNum = i + (HairPage * HairSlot);

		CoachHair[HairNum]->On();

		if (CoachHair[HairNum]->GetIsClick())
		{
			// 로고 70개
			for (size_t i = 0; i < 30; i++)
			{
				CoachHair[i]->IsSelectFalse();
			}
			CurHairNum = HairNum;

			CoachHair[CurHairNum]->IsSelectTrue();

			CurHair = CoachHair[CurHairNum];
			MyCoachHair->SetSprite("Coach_Hair", static_cast<unsigned int>(CurHairNum));
		}
	}
}
