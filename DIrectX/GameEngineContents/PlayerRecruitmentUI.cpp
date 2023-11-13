#include "PreCompile.h"
#include "PlayerRecruitmentUI.h"
#include "RecruitCard.h"
#include "TeamInfo.h"

PlayerRecruitmentUI::PlayerRecruitmentUI()
{

}

PlayerRecruitmentUI::~PlayerRecruitmentUI()
{

}

void PlayerRecruitmentUI::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -100.0f });
	Transform.AddLocalPosition({ 0.0f, 20.0f });
	// 박스
	BoxRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	BoxRenderer->SetSprite("PlayerRecruitment", 5);
	BoxRenderer->AutoSpriteSizeOn();
	BoxRenderer->SetAutoScaleRatio(2.0f);
	BoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	//BoxRenderer->Transform.AddLocalPosition({ 0.0f, 325.0f });

	Card = GetLevel()->CreateActor<RecruitCard>();
	Card->Transform.AddLocalPosition({ -460.0f, 20.0f });

	CancelButton = GetLevel()->CreateActor<Default_Button>();
	CancelButton->Transform.SetLocalPositionZ({ -100.0f });
	CancelButton->SetButtonText("닫기");
	CancelButton->Transform.AddLocalPosition({ 540.0f, -220.0f });

	CostIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	CostIcon->SetSprite("MainUI", 2);
	CostIcon->AutoSpriteSizeOn();
	CostIcon->SetAutoScaleRatio(2.0f);
	CostIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	CostIcon->Transform.AddLocalPosition({ -585.0f , -237.0f });

	CostText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	CostText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	CostText->Transform.AddLocalPosition({ -395.0f, -228.0f });
	CostText->SetText("Galmuri14", std::to_string(TeamInfo::MyInfo.GetGold()), 20.0f, float4::WHITE, FW1_RIGHT);
	
	MainText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	MainText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	MainText->Transform.AddLocalPosition({ 0.0f, 250.0f });
	MainText->SetText("Galmuri14", "선수 영입", 40.0f, float4::WHITE, FW1_CENTER);

	RockBox = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	RockBox->SetSprite("PlayerRecruitment", 6);
	RockBox->AutoSpriteSizeOn();
	RockBox->SetAutoScaleRatio(2.0f);
	RockBox->Transform.AddLocalPosition({ -150.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	RockIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	RockIcon->SetSprite("PlayerRecruitment", 7);
	RockIcon->AutoSpriteSizeOn();
	RockIcon->SetAutoScaleRatio(2.0f);
	RockIcon->Transform.AddLocalPosition({ -150.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });

	RockText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	RockText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	RockText->Transform.AddLocalPosition({ -150.0f, -50.0f });
	RockText->SetText("Galmuri14", "시설 개선을 통해 영입\n슬롯을 확장할 수 있습니다.", 20.0f, float4::WHITE, FW1_CENTER);

	RockBox2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	RockBox2->SetSprite("PlayerRecruitment", 6);
	RockBox2->AutoSpriteSizeOn();
	RockBox2->SetAutoScaleRatio(2.0f);
	RockBox2->Transform.AddLocalPosition({ 156.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	RockIcon2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	RockIcon2->SetSprite("PlayerRecruitment", 7);
	RockIcon2->AutoSpriteSizeOn();
	RockIcon2->SetAutoScaleRatio(2.0f);
	RockIcon2->Transform.AddLocalPosition({ 156.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });

	RockText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	RockText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	RockText2->Transform.AddLocalPosition({ 156.0f, -50.0f });
	RockText2->SetText("Galmuri14", "시설 개선을 통해 영입\n슬롯을 확장할 수 있습니다.", 20.0f, float4::WHITE, FW1_CENTER);

	RockBox3 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	RockBox3->SetSprite("PlayerRecruitment", 6);
	RockBox3->AutoSpriteSizeOn();
	RockBox3->SetAutoScaleRatio(2.0f);
	RockBox3->Transform.AddLocalPosition({ 462.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	RockIcon3 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	RockIcon3->SetSprite("PlayerRecruitment", 7);
	RockIcon3->AutoSpriteSizeOn();
	RockIcon3->SetAutoScaleRatio(2.0f);
	RockIcon3->Transform.AddLocalPosition({ 462.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });

	RockText3 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	RockText3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	RockText3->Transform.AddLocalPosition({ 462.0f, -50.0f });
	RockText3->SetText("Galmuri14", "시설 개선을 통해 영입\n슬롯을 확장할 수 있습니다.", 20.0f, float4::WHITE, FW1_CENTER);

}

void PlayerRecruitmentUI::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayerRecruitmentUI::Update(float _Delta)
{
	CostText->SetText("Galmuri14", std::to_string(TeamInfo::MyInfo.GetGold()), 20.0f, float4::WHITE, FW1_RIGHT);

	if (true == CancelButton->GetIsClick())
	{
		AllOff();
	}

	if (nullptr == Card)
	{
		Card = GetLevel()->CreateActor<RecruitCard>();
		Card->Transform.AddLocalPosition({ -460.0f, 20.0f });
	}

	// 영입 확인.
	if (true == Card->Button3->GetIsClick())
	{
		Card->CreatePlayer();

		Card->AllDeath();
		Card = nullptr;
	}
	else if (true == Card->Button4->GetIsClick())
	{
		Card->AllDeath();
		Card = nullptr;
	}
}

void PlayerRecruitmentUI::AllOn()
{
	On();
	Card->AllOn();
	CancelButton->On();
}

void PlayerRecruitmentUI::AllOff()
{
	Off();
	Card->AllOff();
	CancelButton->Off();
}