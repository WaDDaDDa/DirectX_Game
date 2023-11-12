#include "PreCompile.h"
#include "RecruitCard.h"


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
	Renderer->CreateAnimation("Slect", "PlayerRecruitment", 0.1f, 2, 2, false);
	Renderer->CreateAnimation("Slect_Stay", "PlayerRecruitment", 0.1f, 3, 3, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	HeadText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	HeadText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	HeadText->Transform.AddLocalPosition({ 0.0f, 170.0f });
	HeadText->SetText("Galmuri14", "���� ���� ����", 16.0f, float4::WHITE, FW1_CENTER);

	InText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	InText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	InText->Transform.AddLocalPosition({ -120.0f, 100.0f });
	InText->SetText("Galmuri14", "�������� �پ �Ƿ��� \n���̴� ������ ã���ϴ�.", 20.0f, float4::WHITE);

	InText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	InText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	InText2->Transform.AddLocalPosition({ -120.0f, 60.0f });
	InText2->SetText("Galmuri14", "���� �Ƹ��߾� ���� ������\n������ �ɷ��� ���߰�\n�ֽ��ϴ�.", 20.0f, {1.0f, 184.0f / 255.0f, 13.0f / 255.0f });

	DateText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	DateText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	DateText->Transform.AddLocalPosition({ -110.0f, -40.0f });
	DateText->SetText("Galmuri14", "�ҿ� �ð�:         1��", 20.0f, float4::WHITE, FW1_LEFT);

	CostText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	CostText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	CostText->Transform.AddLocalPosition({ -110.0f, -70.0f });
	CostText->SetText("Galmuri14", "���:               10", 20.0f, float4::WHITE, FW1_LEFT);

	Button = GetLevel()->CreateActor<Default_Button>();
	Button->Transform.SetLocalPositionZ({ -100.0f });
	Button->IsImportantTrue();
	Button->SetButtonText("Ž���ϱ�");
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
	Button2->SetButtonText("���");
	Button2->Transform.AddLocalPosition({ -460.0f, -120.0f });
	Button2->Off();

	SearchText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	SearchText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	SearchText->Transform.AddLocalPosition({ 0.0f, 100.0f });
	SearchText->SetText("Galmuri14", "���� Ž����...", 30.0f, float4::WHITE, FW1_CENTER);
	SearchText->Off();

	SearchText2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	SearchText2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	SearchText2->Transform.AddLocalPosition({ 0.0f, 20.0f });
	SearchText2->SetText("Galmuri14", "���� ���縦 Ž���ϰ� �ֽ��ϴ�.", 16.0f, float4::WHITE, FW1_CENTER);
	SearchText2->Off();

}

void RecruitCard::Update(float _Delta)
{
	UI_Button::Update(_Delta);
	
	if (true == Button->GetIsClick())
	{
		SearchValue = true;
		Searching();
	}
	
	if (true == Button2->GetIsClick())
	{
		SearchValue = false;
		SearchingCancel();
	}
}


void RecruitCard::IdleStart()
{
	Renderer->ChangeAnimation("Null");
}

void RecruitCard::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
}

void RecruitCard::EndStart()
{
	Renderer->ChangeAnimation("Null");
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

	DateText->SetText("Galmuri14", "���� �ð�:         1��", 20.0f, float4::WHITE, FW1_LEFT);

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

	DateText->SetText("Galmuri14", "�ҿ� �ð�:         1��", 20.0f, float4::WHITE, FW1_LEFT);
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

	if (true == SearchValue)
	{
		Searching();
	}
	else if (false == SearchValue)
	{
		SearchingCancel();
	}
}