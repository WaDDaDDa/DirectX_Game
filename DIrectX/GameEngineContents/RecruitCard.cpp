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

	NameText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	NameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	NameText->Transform.AddLocalPosition({ -60.0f, 175.0f });
	NameText->SetText("Galmuri14", "", 16.0f, float4::WHITE, FW1_LEFT);
	NameText->Off();

	PlayerFaceBG = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	PlayerFaceBG->SetSprite("CardUI", 0);
	PlayerFaceBG->AutoSpriteSizeOn();
	PlayerFaceBG->SetAutoScaleRatio(2.5f);
	PlayerFaceBG->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	PlayerFaceBG->Transform.AddLocalPosition({ -105.0f, 150.0f });
	PlayerFaceBG->Off();

	BodyRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer2);
	BodyRenderer->SetSprite("GamePlayer", 0);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(2.0f);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer2) });
	BodyRenderer->Transform.AddLocalPosition({ -105.0f, 140.0f });
	BodyRenderer->Off();

	HairRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	HairRenderer->SetSprite("Coach_Hair", 0);
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(2.0f);
	HairRenderer->Transform.AddLocalPosition({ -105.0f, 155.0f });
	HairRenderer->Off();

	PlayerFaceFG = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	PlayerFaceFG->SetSprite("CardUI", 2);
	PlayerFaceFG->AutoSpriteSizeOn();
	PlayerFaceFG->SetAutoScaleRatio(2.5f);
	PlayerFaceFG->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	PlayerFaceFG->Transform.AddLocalPosition({ -105.0f, 150.0f });
	PlayerFaceFG->Off();

	AttIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	AttIcon->SetSprite("attack_icon.png");
	AttIcon->AutoSpriteSizeOn();
	AttIcon->SetAutoScaleRatio(2.0f);
	AttIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	AttIcon->Transform.AddLocalPosition({ -50.0f, 135.0f });
	AttIcon->Off();

	AttText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	AttText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	AttText->Transform.AddLocalPosition({ -32.0f, 142.0f });
	AttText->SetText("Galmuri14", "0", 16.0f, float4::WHITE, FW1_LEFT);
	AttText->Off();

	DefIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	DefIcon->SetSprite("armor_icon.png");
	DefIcon->AutoSpriteSizeOn();
	DefIcon->SetAutoScaleRatio(2.0f);
	DefIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	DefIcon->Transform.AddLocalPosition({ 40.0f, 135.0f });
	DefIcon->Off();

	DefText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	DefText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	DefText->Transform.AddLocalPosition({ 58.0f, 142.0f });
	DefText->SetText("Galmuri14", "0", 16.0f, float4::WHITE, FW1_LEFT);
	DefText->Off();

	PayText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	PayText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	PayText->Transform.AddLocalPosition({ -120.0f, -90.0f });
	PayText->SetText("Galmuri14", "계약금:         ", 24.0f, float4::WHITE, FW1_LEFT);
	PayText->Off();

	PayIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	PayIcon->SetSprite("MainUI", 2);
	PayIcon->AutoSpriteSizeOn();
	PayIcon->SetAutoScaleRatio(2.0f);
	PayIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	PayIcon->Transform.AddLocalPosition({ 115.0f , -100.0f });
	PayIcon->Off();

	Button3 = GetLevel()->CreateActor<Default_Button>();
	Button3->Transform.SetLocalPositionZ({ -100.0f });
	Button3->IsImportantTrue();
	Button3->SetButtonText("영입하기");
	Button3->Transform.AddLocalPosition({ -535.0f, -135.0f });
	Button3->Off();

	Button4 = GetLevel()->CreateActor<Default_Button>();
	Button4->Transform.SetLocalPositionZ({ -100.0f });
	Button4->SetButtonText("삭제");
	Button4->Transform.AddLocalPosition({ -385.0f, -135.0f });
	Button4->Off();
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

}

void RecruitCard::CreatePlayer()
{
	std::shared_ptr<GamePlayer> NewPlayer = GetLevel()->CreateActor<GamePlayer>();
	NewPlayer->Init(GetLevel());
	NewPlayer->SpecInit(Info);
	TeamInfo::MyInfo.AddPlayer(NewPlayer);

	TeamInfo::MyInfo.AddGold(-Info.Cost);
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
	Button3->Off();
	Button4->Off();
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

	if (true == SearchEnd)
	{
		Button3->On();
		Button4->On();
	}
}

void RecruitCard::AllDeath()
{
	Button->Death();
	Button2->Death();
	Button3->Death();
	Button4->Death();
	Death();
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

	Info.Random();

	NameText->On();
	NameText->SetText("Galmuri14", Info.Name, 16.0f, float4::WHITE, FW1_LEFT);
	PlayerFaceBG->On();
	BodyRenderer->On();
	HairRenderer->On();
	HairRenderer->SetSprite("Coach_Hair", Info.HairNum);
	PlayerFaceFG->On();
	AttIcon->On();
	AttText->On();
	DefIcon->On();
	DefText->On();
	std::string AttString = GameEngineString::Format("{:.0f}", Info.Att);
	std::string DefString = GameEngineString::Format("{:.0f}", Info.Def);

	AttText->SetText("Galmuri14", AttString, 16.0f, float4::WHITE, FW1_LEFT);
	DefText->SetText("Galmuri14", DefString, 16.0f, float4::WHITE, FW1_LEFT);
	PayText->On();

	PayText->SetText("Galmuri14", "계약금:         " + std::to_string(Info.Cost), 24.0f, float4::WHITE, FW1_LEFT);
	PayIcon->On();
	Button3->On();
	Button4->On();

}