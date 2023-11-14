#include "PreCompile.h"
#include "PlayerSquadUI.h"
#include "PlayerSquadCard.h"
#include "TeamInfo.h"
#include "GamePlayer.h"

PlayerSquadUI::PlayerSquadUI()
{

}

PlayerSquadUI::~PlayerSquadUI()
{

}

void PlayerSquadUI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -100.0f });
	//Transform.AddLocalPosition({ 0.0f, 20.0f });

	// 박스
	BoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	BoxRenderer->SetSprite("Squad", 4);
	BoxRenderer->AutoSpriteSizeOn();
	BoxRenderer->SetAutoScaleRatio(2.0f);
	BoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });

	MainText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText->Transform.AddLocalPosition({ -480.0f, 160.0f });
	MainText->SetText("Galmuri14", "이름", 20.0f, float4::WHITE, FW1_CENTER);

	MainText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText2->Transform.AddLocalPosition({ -320.0f, 160.0f });
	MainText2->SetText("Galmuri14", "나이", 20.0f, float4::WHITE, FW1_CENTER);

	MainText3 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText3->Transform.AddLocalPosition({ -140.0f, 160.0f });
	MainText3->SetText("Galmuri14", "공격력", 20.0f, float4::WHITE, FW1_CENTER);

	MainText4 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText4->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText4->Transform.AddLocalPosition({ 15.0f, 160.0f });
	MainText4->SetText("Galmuri14", "방어력", 20.0f, float4::WHITE, FW1_CENTER);

	MainText5 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText5->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText5->Transform.AddLocalPosition({ 190.0f, 160.0f });
	MainText5->SetText("Galmuri14", "재계약 비용", 20.0f, float4::WHITE, FW1_CENTER);

	std::list<std::shared_ptr<class GamePlayer>> PlayerGroup = TeamInfo::MyInfo.GetMyPlayer();
	size_t Size = 0;

	for (std::shared_ptr<GamePlayer>& Player : PlayerGroup)
	{
		CardGroup.push_back(GetLevel()->CreateActor<PlayerSquadCard>());
		CardGroup[Size]->Transform.AddLocalPosition(StartPos + (InterY * static_cast<float>(Size)));
		CardGroup[Size]->SetInfo(Player->GetSpec());
		Size++;
	}

	Button = GetLevel()->CreateActor<Default_Button>();
	Button->Transform.SetLocalPositionZ({ -150.0f });
	Button->SetButtonText("닫기");
	Button->Transform.AddLocalPosition({ 520.0f, -240.0f });
	
}

void PlayerSquadUI::AllDeath()
{
	for (size_t i = 0; i < CardGroup.size(); i++)
	{
		CardGroup[i]->AllDeath();
	}
	
	Button->Death();
	Death();
}


void PlayerSquadUI::Update(float _Delta)
{
	if (true == Button->GetIsClick())
	{
		AllDeath();
	}
}

void PlayerSquadUI::LevelStart(GameEngineLevel* _PrevLevel)
{

}