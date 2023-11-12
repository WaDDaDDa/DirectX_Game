#include "PreCompile.h"
#include "RecruitCard.h"
#include "TeamInfo.h"
#include "GamePlayer.h"


RecruitCard::RecruitCard()
{

}

RecruitCard::~RecruitCard()
{

}

void RecruitCard::Start()
{
	UI_Button::Start();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ 0.0f, 0.0f, -100.0f });

	float4 TeamLogoColScale = { 300.0f , 400.0f };
	SetButtonColScale(TeamLogoColScale);
	//Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "PlayerRecruitment", 0.1f, 3, 3, false);
	Renderer->CreateAnimation("Null_Stay", "PlayerRecruitment", 0.1f, 4, 4, false);
	Renderer->CreateAnimation("Search", "PlayerRecruitment", 0.1f, 0, 0, false);
	Renderer->CreateAnimation("Search_Stay", "PlayerRecruitment", 0.1f, 1, 1, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	HeadText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	HeadText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	HeadText->Transform.AddLocalPosition({ 0.0f, 170.0f });
	HeadText->SetText("Galmuri14", "지역 인재 영입", 16.0f, float4::WHITE, FW1_CENTER);

	InText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	InText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	InText->Transform.AddLocalPosition({ -120.0f, 100.0f });
	InText->SetText("Galmuri14", "지역에서 뛰어난 실력을 \n보이는 선수를 찾습니다.", 20.0f, float4::WHITE);

	InText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	InText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	InText2->Transform.AddLocalPosition({ -120.0f, 60.0f });
	InText2->SetText("Galmuri14", "보통 아마추어 리그 상위권\n정도의 능력을 갖추고\n있습니다.", 20.0f, {1.0f, 184.0f / 255.0f, 13.0f / 255.0f });

	DateText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	DateText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	DateText->Transform.AddLocalPosition({ -110.0f, -40.0f });
	DateText->SetText("Galmuri14", "소요 시간:         1주", 20.0f, float4::WHITE, FW1_LEFT);

	CostText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	CostText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	CostText->Transform.AddLocalPosition({ -110.0f, -70.0f });
	CostText->SetText("Galmuri14", "비용:               10", 20.0f, float4::WHITE, FW1_LEFT);

	Button = GetLevel()->CreateActor<Default_Button>();
	Button->Transform.SetLocalPositionZ({ -100.0f });
	Button->IsImportantTrue();
	Button->SetButtonText("탐색하기");
	Button->Transform.AddLocalPosition({ -460.0f, -120.0f });

	DateIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	DateIcon->SetSprite("MainUI", 1);
	DateIcon->AutoSpriteSizeOn();
	DateIcon->SetAutoScaleRatio(2.0f);
	DateIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	DateIcon->Transform.AddLocalPosition({ 110.0f , -50.0f });

	CostIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	CostIcon->SetSprite("MainUI", 2);
	CostIcon->AutoSpriteSizeOn();
	CostIcon->SetAutoScaleRatio(2.0f);
	CostIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	CostIcon->Transform.AddLocalPosition({ 110.0f , -80.0f });

	Button2 = GetLevel()->CreateActor<Default_Button>();
	Button2->Transform.SetLocalPositionZ({ -100.0f });
	Button2->SetButtonText("취소");
	Button2->Transform.AddLocalPosition({ -460.0f, -120.0f });
	Button2->Off();

	SearchText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	SearchText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	SearchText->Transform.AddLocalPosition({ 0.0f, 100.0f });
	SearchText->SetText("Galmuri14", "선수 탐색중...", 30.0f, float4::WHITE, FW1_CENTER);
	SearchText->Off();

	SearchText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	SearchText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	SearchText2->Transform.AddLocalPosition({ 0.0f, 20.0f });
	SearchText2->SetText("Galmuri14", "지역 인재를 탐색하고 있습니다.", 16.0f, float4::WHITE, FW1_CENTER);
	SearchText2->Off();

}

void RecruitCard::Update(float _Delta)
{
	UI_Button::Update(_Delta);
	
	if (true == Button->GetIsClick() && false == SearchEnd)
	{
		SearchValue = true;
		TeamInfo::MyInfo.AddGold(-10);
		EndWeek = TeamInfo::MyInfo.GetWeek() + 1;
		if (5 <= EndWeek)
		{
			EndWeek = EndWeek - 4;
		}
		Searching();
	}
	if (true == Button2->GetIsClick() && false == SearchEnd)
	{
		SearchValue = false;
		SearchingCancel();
	}

	if (TeamInfo::MyInfo.GetWeek() == EndWeek && false == SearchEnd)
	{
		SearchEnd = true;
		Renderer->ChangeAnimation("Search");
		RecruitResult();
	}

	if (true == SearchEnd)
	{
	}
}


void RecruitCard::IdleStart()
{
	if (false == SearchEnd)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == SearchEnd)
	{
		Renderer->ChangeAnimation("Search");

	}
}

void RecruitCard::StayStart()
{
	if (false == SearchEnd)
	{
		Renderer->ChangeAnimation("Null_Stay");
	}
	else if (true == SearchEnd)
	{
		Renderer->ChangeAnimation("Search_Stay");

	}
}

void RecruitCard::EndStart()
{
	if (false == SearchEnd)
	{
		Renderer->ChangeAnimation("Null");
	}
	else if (true == SearchEnd)
	{
		Renderer->ChangeAnimation("Search");

	}
}

void RecruitCard::ClickStart()
{
	UI_Button::ClickStart();
}

void RecruitCard::Searching()
{
	CostText->Off();
	CostIcon->Off();
	InText->Off();
	InText2->Off();
	Button->Off();

	SearchText->On();
	SearchText2->On();
	Button2->On();

	DateText->SetText("Galmuri14", "남은 시간:         1주", 20.0f, float4::WHITE, FW1_LEFT);

}

void RecruitCard::SearchingCancel()
{
	SearchText->Off();
	SearchText2->Off();
	Button2->Off();

	CostText->On();
	CostIcon->On();
	InText->On();
	InText2->On();
	Button->On();

	DateText->SetText("Galmuri14", "소요 시간:         1주", 20.0f, float4::WHITE, FW1_LEFT);
}

void RecruitCard::AllOff()
{
	Off();
	Button->Off();
	Button2->Off();
}

void RecruitCard::AllOn()
{
	On();

	if (true == SearchValue && false == SearchEnd)
	{
		Searching();
	}
	else if (false == SearchValue && false == SearchEnd)
	{
		SearchingCancel();
	}
}

void RecruitCard::RecruitResult()
{
	Button->Off();
	Button2->Off();
	SearchText->Off();
	SearchText2->Off();

	CostText->Off();
	CostIcon->Off();
	InText->Off();
	InText2->Off();
	Button->Off();
	DateText->Off();
	DateIcon->Off();
	HeadText->Off();

	GamePlayerInfo Info;
	Info.Random();


}