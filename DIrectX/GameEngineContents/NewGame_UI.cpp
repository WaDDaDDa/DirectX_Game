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

	NewGameBoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	NewGameBoxRenderer->SetSprite("new_game_ui_bg.png");
	NewGameBoxRenderer->AutoSpriteSizeOn();
	NewGameBoxRenderer->SetAutoScaleRatio(2.0f);
	NewGameBoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });

	for (size_t i = 0; i < LogoSlot; i++)
	{
		TeamLogoButton.push_back(GetLevel()->CreateActor<SlotButton>());


		TeamLogoRenderer.push_back(CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage));	
		TeamLogoRenderer[i]->SetSprite("TeamLogo", static_cast<unsigned int>(i));
		TeamLogoRenderer[i]->AutoSpriteSizeOn();
		TeamLogoRenderer[i]->SetAutoScaleRatio(2.0f);
		TeamLogoRenderer[i]->Transform.AddLocalPosition({0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage)});

		if (5 > i)
		{
			TeamLogoButton[i]->Transform.AddLocalPosition(TeamLogoStartPos + (XInter * static_cast<float>(i)));
			TeamLogoRenderer[i]->Transform.AddLocalPosition(TeamLogoStartPos + (XInter * static_cast<float>(i)));
		}
		else if (5 <= i)
		{
			TeamLogoButton[i]->Transform.AddLocalPosition(TeamLogoStartPos2 + (XInter * static_cast<float>(i - 5)));
			TeamLogoRenderer[i]->Transform.AddLocalPosition(TeamLogoStartPos2 + (XInter * static_cast<float>(i - 5)));
		}
	}

	TeamLogoNextArrow = GetLevel()->CreateActor<GreenArrow>();
	TeamLogoNextArrow->DirChange();
}

void NewGame_UI::Update(float _Delta)
{

	if (TeamLogoNextArrow->GetIsClick())
	{
		TeamLogoPage += 1;
	}

	for (size_t i = 0; i < LogoSlot; i++)
	{
		size_t CurNum = i + (TeamLogoPage * LogoSlot);

		TeamLogoRenderer[i]->SetSprite("TeamLogo", static_cast<unsigned int>(CurNum));
	}


}
