#include "PreCompile.h"
#include "Stadium.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"

Stadium::Stadium()
{

}

Stadium::~Stadium()
{

}

void Stadium::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 300.0f });

	StadiumRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	StadiumRenderer->SetSprite("stadium_bg.png");
	StadiumRenderer->AutoSpriteSizeOn();
	StadiumRenderer->SetAutoScaleRatio(2.7f);
	StadiumRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });

	BackDesk = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Map);
	BackDesk->SetSprite("stadium_frame.png");
	BackDesk->AutoSpriteSizeOn();
	BackDesk->SetAutoScaleRatio(2.7f);
	BackDesk->Transform.AddLocalPosition({ 0.0f, -65.0f, -static_cast<float>(ContentsOrder::Map) });

	Chair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Chair->SetSprite("stadium_chair.png");
	Chair->AutoSpriteSizeOn();
	Chair->SetAutoScaleRatio(2.7f);
	Chair->Transform.AddLocalPosition({ 0.0f, -75.0f, -static_cast<float>(ContentsOrder::BackEffect) });

	Desk = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect3);
	Desk->SetSprite("stadium_desk.png");
	Desk->AutoSpriteSizeOn();
	Desk->SetAutoScaleRatio(2.7f);
	Desk->Transform.AddLocalPosition({ 0.0f, -92.0f, -static_cast<float>(ContentsOrder::BackEffect3) });

	Frame = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect3);
	Frame->SetSprite("stadium_frame_front.png");
	Frame->AutoSpriteSizeOn();
	Frame->SetAutoScaleRatio(2.7f);
	Frame->Transform.AddLocalPosition({ 0.0f, -156.0f, -static_cast<float>(ContentsOrder::BackEffect3) });

	BlueTeamName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BlueTeamName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	BlueTeamName->Transform.AddLocalPosition({ -320.0f, 182.0f });
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 26.0f, float4::WHITE, FW1_RIGHT);

	BlueTeamLogo = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BlueTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BlueTeamLogo->AutoSpriteSizeOn();
	BlueTeamLogo->SetAutoScaleRatio(1.3f);
	BlueTeamLogo->Transform.AddLocalPosition({ -293.0f, 173.0f, -static_cast<float>(ContentsOrder::UI) });

	BigBlueTeamLogoBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BigBlueTeamLogoBg->SetSprite("CardUI", 0);
	BigBlueTeamLogoBg->AutoSpriteSizeOn();
	BigBlueTeamLogoBg->SetAutoScaleRatio(3.0f);
	BigBlueTeamLogoBg->Transform.AddLocalPosition({ -140.0f, 140.0f, -static_cast<float>(ContentsOrder::UI) });

	BigBlueTeamLogo = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	BigBlueTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BigBlueTeamLogo->AutoSpriteSizeOn();
	BigBlueTeamLogo->SetAutoScaleRatio(2.5f);
	BigBlueTeamLogo->Transform.AddLocalPosition({ -140.0f, 140.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BigBlueTeamName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BigBlueTeamName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	BigBlueTeamName->Transform.AddLocalPosition({ -140.0f, 80.0f });
	BigBlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 26.0f, float4::BLACK, FW1_CENTER);

	VSText = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	VSText->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	VSText->Transform.AddLocalPosition({ 0.0f, 140.0f });
	VSText->SetText("Galmuri14", "VS", 45.0f, float4::BLACK, FW1_CENTER);

	RedTeamName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	RedTeamName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	RedTeamName->Transform.AddLocalPosition({ 320.0f, 182.0f });
	RedTeamName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 26.0f, float4::WHITE, FW1_LEFT);

	RedTeamLogo = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	RedTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
	RedTeamLogo->AutoSpriteSizeOn();
	RedTeamLogo->SetAutoScaleRatio(1.3f);
	RedTeamLogo->Transform.AddLocalPosition({ 293.0f, 173.0f, -static_cast<float>(ContentsOrder::UI) });

	BigRedTeamLogoBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BigRedTeamLogoBg->SetSprite("CardUI", 0);
	BigRedTeamLogoBg->AutoSpriteSizeOn();
	BigRedTeamLogoBg->SetAutoScaleRatio(3.0f);
	BigRedTeamLogoBg->Transform.AddLocalPosition({ 140.0f, 140.0f, -static_cast<float>(ContentsOrder::UI) });

	BigRedTeamLogo = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	BigRedTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
	BigRedTeamLogo->AutoSpriteSizeOn();
	BigRedTeamLogo->SetAutoScaleRatio(2.5f);
	BigRedTeamLogo->Transform.AddLocalPosition({ 140.0f, 140.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BigRedTeamName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BigRedTeamName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	BigRedTeamName->Transform.AddLocalPosition({ 140.0f, 80.0f });
	BigRedTeamName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 26.0f, float4::BLACK, FW1_CENTER);

	BlueOnePlayerBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackUI);
	BlueOnePlayerBg->SetSprite("PlayerCard", 13);
	BlueOnePlayerBg->AutoSpriteSizeOn();
	BlueOnePlayerBg->SetAutoScaleRatio(2.8f);
	BlueOnePlayerBg->Transform.AddLocalPosition({ -301.0f, 76.0f, -static_cast<float>(ContentsOrder::BackUI) });

	BlueOnePlayerBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BlueOnePlayerBody->SetSprite("GamePlayer", 0);
	BlueOnePlayerBody->AutoSpriteSizeOn();
	BlueOnePlayerBody->SetAutoScaleRatio(2.5f);
	BlueOnePlayerBody->Transform.AddLocalPosition({ -301.0f, 86.0f, -static_cast<float>(ContentsOrder::UI) });

	BlueOnePlayerHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	BlueOnePlayerHair->SetSprite("Coach_Hair", TeamInfo::MyInfo.OnePlayer->GetSpec().HairNum);
	BlueOnePlayerHair->AutoSpriteSizeOn();
	BlueOnePlayerHair->SetAutoScaleRatio(2.5f);
	BlueOnePlayerHair->Transform.AddLocalPosition({ -301.0f, 102.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueOnePlayerName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	BlueOnePlayerName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	BlueOnePlayerName->Transform.AddLocalPosition({ -301.0f, 40.0f });
	BlueOnePlayerName->SetText("Galmuri14", TeamInfo::MyInfo.OnePlayer->GetSpec().Name, 16.0f, float4::WHITE, FW1_CENTER);

	BlueTwoPlayerBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackUI);
	BlueTwoPlayerBg->SetSprite("PlayerCard", 13);
	BlueTwoPlayerBg->AutoSpriteSizeOn();
	BlueTwoPlayerBg->SetAutoScaleRatio(2.8f);
	BlueTwoPlayerBg->Transform.AddLocalPosition({ -379.0f, 76.0f, -static_cast<float>(ContentsOrder::BackUI) });

	BlueTwoPlayerBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	BlueTwoPlayerBody->SetSprite("GamePlayer", 0);
	BlueTwoPlayerBody->AutoSpriteSizeOn();
	BlueTwoPlayerBody->SetAutoScaleRatio(2.5f);
	BlueTwoPlayerBody->Transform.AddLocalPosition({ -379.0f, 86.0f, -static_cast<float>(ContentsOrder::UI) });

	BlueTwoPlayerHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	BlueTwoPlayerHair->SetSprite("Coach_Hair", TeamInfo::MyInfo.TwoPlayer->GetSpec().HairNum);
	BlueTwoPlayerHair->AutoSpriteSizeOn();
	BlueTwoPlayerHair->SetAutoScaleRatio(2.5f);
	BlueTwoPlayerHair->Transform.AddLocalPosition({ -379.0f, 102.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueTwoPlayerName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	BlueTwoPlayerName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	BlueTwoPlayerName->Transform.AddLocalPosition({ -379.0f, 40.0f });
	BlueTwoPlayerName->SetText("Galmuri14", TeamInfo::MyInfo.TwoPlayer->GetSpec().Name, 16.0f, float4::WHITE, FW1_CENTER);

	/// Red
	RedOnePlayerBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackUI);
	RedOnePlayerBg->SetSprite("PlayerCard", 14);
	RedOnePlayerBg->AutoSpriteSizeOn();
	RedOnePlayerBg->SetAutoScaleRatio(2.8f);
	RedOnePlayerBg->Transform.AddLocalPosition({ 301.0f, 76.0f, -static_cast<float>(ContentsOrder::BackUI) });
	
	RedOnePlayerBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	RedOnePlayerBody->SetSprite("GamePlayer", 0);
	RedOnePlayerBody->AutoSpriteSizeOn();
	RedOnePlayerBody->SetAutoScaleRatio(2.5f);
	RedOnePlayerBody->Transform.AddLocalPosition({ 301.0f, 86.0f, -static_cast<float>(ContentsOrder::UI) });
	RedOnePlayerBody->LeftFlip();
	
	RedOnePlayerHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	RedOnePlayerHair->SetSprite("Coach_Hair", EnemyInfo::Info.GetOnePlayer().HairNum);
	RedOnePlayerHair->AutoSpriteSizeOn();
	RedOnePlayerHair->SetAutoScaleRatio(2.5f);
	RedOnePlayerHair->Transform.AddLocalPosition({ 301.0f, 102.0f, -static_cast<float>(ContentsOrder::UIImage) });
	RedOnePlayerHair->LeftFlip();

	RedOnePlayerName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	RedOnePlayerName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	RedOnePlayerName->Transform.AddLocalPosition({ 301.0f, 40.0f });
	RedOnePlayerName->SetText("Galmuri14", EnemyInfo::Info.GetOnePlayer().Name, 16.0f, float4::WHITE, FW1_CENTER);
	
	RedTwoPlayerBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackUI);
	RedTwoPlayerBg->SetSprite("PlayerCard", 14);
	RedTwoPlayerBg->AutoSpriteSizeOn();
	RedTwoPlayerBg->SetAutoScaleRatio(2.8f);
	RedTwoPlayerBg->Transform.AddLocalPosition({ 379.0f, 76.0f, -static_cast<float>(ContentsOrder::BackUI) });
	
	RedTwoPlayerBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	RedTwoPlayerBody->SetSprite("GamePlayer", 0);
	RedTwoPlayerBody->AutoSpriteSizeOn();
	RedTwoPlayerBody->SetAutoScaleRatio(2.5f);
	RedTwoPlayerBody->Transform.AddLocalPosition({ 379.0f, 86.0f, -static_cast<float>(ContentsOrder::UI) });
	RedTwoPlayerBody->LeftFlip();

	RedTwoPlayerHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	RedTwoPlayerHair->SetSprite("Coach_Hair", EnemyInfo::Info.GetTwoPlayer().HairNum);
	RedTwoPlayerHair->AutoSpriteSizeOn();
	RedTwoPlayerHair->SetAutoScaleRatio(2.5f);
	RedTwoPlayerHair->Transform.AddLocalPosition({ 379.0f, 102.0f, -static_cast<float>(ContentsOrder::UIImage) });
	RedTwoPlayerHair->LeftFlip();

	RedTwoPlayerName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	RedTwoPlayerName->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	RedTwoPlayerName->Transform.AddLocalPosition({ 379.0f, 40.0f });
	RedTwoPlayerName->SetText("Galmuri14", EnemyInfo::Info.GetTwoPlayer().Name, 16.0f, float4::WHITE, FW1_CENTER);

	BluePlayerBody1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect1);
	BluePlayerBody1->SetSprite("GamePlayer", 0);
	BluePlayerBody1->AutoSpriteSizeOn();
	BluePlayerBody1->SetAutoScaleRatio(2.5f);
	BluePlayerBody1->Transform.AddLocalPosition({ -175.0f, -70.0f, -static_cast<float>(ContentsOrder::BackEffect1) });

	BluePlayerHair1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	BluePlayerHair1->SetSprite("Coach_Hair", TeamInfo::MyInfo.OnePlayer->GetSpec().HairNum);
	BluePlayerHair1->AutoSpriteSizeOn();
	BluePlayerHair1->SetAutoScaleRatio(2.5f);
	BluePlayerHair1->Transform.AddLocalPosition({ -175.0f, -54.0f, -static_cast<float>(ContentsOrder::BackEffect2) });

	BluePlayerBody2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect1);
	BluePlayerBody2->SetSprite("GamePlayer", 0);
	BluePlayerBody2->AutoSpriteSizeOn();
	BluePlayerBody2->SetAutoScaleRatio(2.5f);
	BluePlayerBody2->Transform.AddLocalPosition({ -242.0f, -70.0f, -static_cast<float>(ContentsOrder::BackEffect1) });

	BluePlayerHair2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	BluePlayerHair2->SetSprite("Coach_Hair", TeamInfo::MyInfo.TwoPlayer->GetSpec().HairNum);
	BluePlayerHair2->AutoSpriteSizeOn();
	BluePlayerHair2->SetAutoScaleRatio(2.5f);
	BluePlayerHair2->Transform.AddLocalPosition({ -242.0f, -54.0f, -static_cast<float>(ContentsOrder::BackEffect2) });

	RedPlayerBody1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect1);
	RedPlayerBody1->SetSprite("GamePlayer", 0);
	RedPlayerBody1->AutoSpriteSizeOn();
	RedPlayerBody1->SetAutoScaleRatio(2.5f);
	RedPlayerBody1->Transform.AddLocalPosition({ 175.0f, -70.0f, -static_cast<float>(ContentsOrder::BackEffect1) });
	RedPlayerBody1->LeftFlip();

	RedPlayerHair1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	RedPlayerHair1->SetSprite("Coach_Hair", EnemyInfo::Info.GetOnePlayer().HairNum);
	RedPlayerHair1->AutoSpriteSizeOn();
	RedPlayerHair1->SetAutoScaleRatio(2.5f);
	RedPlayerHair1->Transform.AddLocalPosition({ 175.0f, -54.0f, -static_cast<float>(ContentsOrder::BackEffect2) });
	RedPlayerHair1->LeftFlip();

	RedPlayerBody2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect1);
	RedPlayerBody2->SetSprite("GamePlayer", 0);
	RedPlayerBody2->AutoSpriteSizeOn();
	RedPlayerBody2->SetAutoScaleRatio(2.5f);
	RedPlayerBody2->Transform.AddLocalPosition({ 242.0f, -70.0f, -static_cast<float>(ContentsOrder::BackEffect1) });
	RedPlayerBody2->LeftFlip();

	RedPlayerHair2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	RedPlayerHair2->SetSprite("Coach_Hair", EnemyInfo::Info.GetTwoPlayer().HairNum);
	RedPlayerHair2->AutoSpriteSizeOn();
	RedPlayerHair2->SetAutoScaleRatio(2.5f);
	RedPlayerHair2->Transform.AddLocalPosition({ 242.0f, -54.0f, -static_cast<float>(ContentsOrder::BackEffect2) });
	RedPlayerHair2->LeftFlip();
}

void Stadium::LevelStart(GameEngineLevel* _PrevLevel)
{
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 26.0f, float4::WHITE, FW1_RIGHT);

	BlueTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));

	BigBlueTeamLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));

	BigBlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 26.0f, float4::BLACK, FW1_CENTER);
}

void Stadium::Update(float _Delta)
{
	if (5.0f <= GetLiveTime())
	{
		FadeOutEffect = GetLevel()->GetLevelRenderTarget()->CreateEffect<FadeEffect>();
		FadeOutEffect->SetChangeLevelName("BanPickLevel");
		ResetLiveTime();
	}
}

void Stadium::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != FadeOutEffect)
	{
		FadeOutEffect->Death();
		FadeOutEffect = nullptr;
	}
}