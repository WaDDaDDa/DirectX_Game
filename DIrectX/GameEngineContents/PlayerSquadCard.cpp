#include "PreCompile.h"
#include "PlayerSquadCard.h"
#include "TeamInfo.h"

PlayerSquadCard::PlayerSquadCard()
{

}

PlayerSquadCard::~PlayerSquadCard()
{

}

void PlayerSquadCard::Start()
{
	UI_Button::Start();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ 0.0f, 0.0f, -100.0f });

	float4 TeamLogoColScale = { 1180.0f , 60.0f };
	SetButtonColScale(TeamLogoColScale);
	//Transform.AddLocalPosition({ 0.0f, 0.0f, 100.0f });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("Null", "Squad", 0.1f, 2, 2, false);
	Renderer->CreateAnimation("Null_Stay", "Squad", 0.1f, 3, 3, false);
	Renderer->ChangeAnimation("Null");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	PlayerFaceBG = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	PlayerFaceBG->SetSprite("CardUI", 0);
	PlayerFaceBG->AutoSpriteSizeOn();
	PlayerFaceBG->SetAutoScaleRatio(2.0f);
	PlayerFaceBG->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	PlayerFaceBG->Transform.AddLocalPosition({ -550.0f, 0.0f });

	BodyRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer2);
	BodyRenderer->SetSprite("GamePlayer", 0);
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->SetAutoScaleRatio(1.5f);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer2) });
	BodyRenderer->Transform.AddLocalPosition({ -550.0f, 0.0f });

	HairRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	HairRenderer->SetSprite("Coach_Hair", 0);
	HairRenderer->AutoSpriteSizeOn();
	HairRenderer->SetAutoScaleRatio(1.5f);
	HairRenderer->Transform.AddLocalPosition({ -550.0f, 10.0f });

	PlayerFaceFG = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	PlayerFaceFG->SetSprite("CardUI", 2);
	PlayerFaceFG->AutoSpriteSizeOn();
	PlayerFaceFG->SetAutoScaleRatio(2.0f);
	PlayerFaceFG->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	PlayerFaceFG->Transform.AddLocalPosition({ -550.0f, 0.0f });

	NameText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	NameText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	NameText->Transform.AddLocalPosition({ -510.0f, 5.0f });
	NameText->SetText("Galmuri14", "", 16.0f, float4::WHITE, FW1_LEFT);

	AgeText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	AgeText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	AgeText->Transform.AddLocalPosition({ -335.0f, 10.0f });
	AgeText->SetText("Galmuri14", "21", 20.0f, float4::WHITE, FW1_LEFT);

	AttIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	AttIcon->SetSprite("attack_icon.png");
	AttIcon->AutoSpriteSizeOn();
	AttIcon->SetAutoScaleRatio(2.0f);
	AttIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	AttIcon->Transform.AddLocalPosition({ -150.0f, 0.0f });

	AttText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	AttText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	AttText->Transform.AddLocalPosition({ -135.0f, 10.0f });
	AttText->SetText("Galmuri14", "", 20.0f, float4::WHITE, FW1_LEFT);

	DefIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UILayer1);
	DefIcon->SetSprite("armor_icon.png");
	DefIcon->AutoSpriteSizeOn();
	DefIcon->SetAutoScaleRatio(2.0f);
	DefIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UILayer1) });
	DefIcon->Transform.AddLocalPosition({ 0.0f, 0.0f });

	DefText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	DefText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	DefText->Transform.AddLocalPosition({ 15.0f, 10.0f });
	DefText->SetText("Galmuri14", "", 20.0f, float4::WHITE, FW1_LEFT);

	PayText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	PayText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	PayText->Transform.AddLocalPosition({ 150.0f, 10.0f });
	PayText->SetText("Galmuri14", "", 24.0f, float4::WHITE, FW1_LEFT);

	PayIcon = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	PayIcon->SetSprite("MainUI", 2);
	PayIcon->AutoSpriteSizeOn();
	PayIcon->SetAutoScaleRatio(2.0f);
	PayIcon->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	PayIcon->Transform.AddLocalPosition({ 220.0f , 0.0f });

	Button = GetLevel()->CreateActor<Default_Button>();
	Button->Transform.SetLocalPositionZ({ -150.0f });
	Button->IsImportantTrue();
	Button->SetButtonText("해고하기");
	Button->Transform.AddLocalPosition({ 460.0f, 0.0f });
}

void PlayerSquadCard::SetInfo(class GamePlayerInfo _Info)
{
	Info = _Info;

	HairRenderer->SetSprite("Coach_Hair", Info.HairNum);
	NameText->SetText("Galmuri14", Info.Name, 16.0f, float4::WHITE, FW1_LEFT);

	std::string AttString = GameEngineString::Format("{:.0f}", Info.Att);
	std::string DefString = GameEngineString::Format("{:.0f}", Info.Def);

	AttText->SetText("Galmuri14", AttString, 20.0f, float4::WHITE, FW1_LEFT);
	DefText->SetText("Galmuri14", DefString, 20.0f, float4::WHITE, FW1_LEFT);
	PayText->SetText("Galmuri14", std::to_string(Info.Cost), 24.0f, float4::WHITE, FW1_LEFT);


	Button->Transform.SetLocalPositionY(Transform.GetWorldPosition().Y);

}

void PlayerSquadCard::AllDeath()
{
	Button->Death();
	Death();
}

void PlayerSquadCard::Update(float _Delta)
{
	UI_Button::Update(_Delta);

	if (true == Button->GetIsClick())
	{
		std::list<std::shared_ptr<class GamePlayer>>& PlayerGroup = TeamInfo::MyInfo.GetMyPlayer();

		std::list<std::shared_ptr<GamePlayer>>::iterator Start = PlayerGroup.begin();
		std::list<std::shared_ptr<GamePlayer>>::iterator End = PlayerGroup.end();

		for (; Start != End;)
		{
			if ((*Start)->GetSpec().Name == Info.Name && (*Start)->GetSpec().HairNum == Info.HairNum)
			{
				(*Start)->Death();
				AllDeath();
				Start = PlayerGroup.erase(Start);
				return;
			}
			Start++;
		}


	}
}

void PlayerSquadCard::IdleStart()
{
	Renderer->ChangeAnimation("Null");
}

void PlayerSquadCard::StayStart()
{
	Renderer->ChangeAnimation("Null_Stay");
}

void PlayerSquadCard::EndStart()
{
	Renderer->ChangeAnimation("Null");
}

void PlayerSquadCard::ClickStart()
{
	UI_Button::ClickStart();
}
