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

	Desk = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	Desk->SetSprite("stadium_desk.png");
	Desk->AutoSpriteSizeOn();
	Desk->SetAutoScaleRatio(2.7f);
	Desk->Transform.AddLocalPosition({ 0.0f, -92.0f, -static_cast<float>(ContentsOrder::BackEffect2) });

	Frame = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect2);
	Frame->SetSprite("stadium_frame_front.png");
	Frame->AutoSpriteSizeOn();
	Frame->SetAutoScaleRatio(2.7f);
	Frame->Transform.AddLocalPosition({ 0.0f, -156.0f, -static_cast<float>(ContentsOrder::BackEffect2) });

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

}

void Stadium::LevelEnd(GameEngineLevel* _NextLevel)
{

}