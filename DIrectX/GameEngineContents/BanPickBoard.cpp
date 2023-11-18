#include "PreCompile.h"
#include "BanPickBoard.h"
#include "GameUnit.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"

BanPickBoard::BanPickBoard()
{

}

BanPickBoard::~BanPickBoard()
{

}

void BanPickBoard::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, 0.0f , 100.0f });

	BackGround = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackGround);
	BackGround->SetSprite("banpick_ui_bg.png");
	BackGround->SetImageScale(WindowScale);
	//BackGround->SetPivotType(PivotType::Top);
	BackGround->Transform.AddLocalPosition({ 0.0f, -HalfWindowScale.Y, -static_cast<float>(ContentsOrder::BackGround) });

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->SetSprite("stadium_VS.png");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->SetPivotType(PivotType::Top);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });

	BlueWin = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueWin->SetSprite("win_indicator_0.png");
	BlueWin->AutoSpriteSizeOn();
	BlueWin->SetAutoScaleRatio(2.0f);
	BlueWin->Transform.AddLocalPosition({ -135.0f,-65.0f });
	BlueWin->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueWin2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueWin2->SetSprite("win_indicator_0.png");
	BlueWin2->AutoSpriteSizeOn();
	BlueWin2->SetAutoScaleRatio(2.0f);
	BlueWin2->Transform.AddLocalPosition({ -115.0f,-65.0f });
	BlueWin2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	RedWin = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedWin->SetSprite("win_indicator_0.png");
	RedWin->AutoSpriteSizeOn();
	RedWin->SetAutoScaleRatio(2.0f);
	RedWin->Transform.AddLocalPosition({ 115.0f,-65.0f });
	RedWin->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	RedWin2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedWin2->SetSprite("win_indicator_0.png");
	RedWin2->AutoSpriteSizeOn();
	RedWin2->SetAutoScaleRatio(2.0f);
	RedWin2->Transform.AddLocalPosition({ 135.0f,-65.0f });
	RedWin2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BlueLogo->AutoSpriteSizeOn();
	BlueLogo->SetAutoScaleRatio(2.0f);
	BlueLogo->Transform.AddLocalPosition({ -600.0f, -35.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueTeamName = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
	BlueTeamName->Transform.AddLocalPosition({ -400.0f, -20.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueTeamWinCount = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueTeamWinCount->SetText("Galmuri14", "0", 32.0f, float4::WHITE, FW1_CENTER);
	BlueTeamWinCount->Transform.AddLocalPosition({ -90.0f, -15.0f, -static_cast<float>(ContentsOrder::UIImage) });

	RedLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
	RedLogo->AutoSpriteSizeOn();
	RedLogo->SetAutoScaleRatio(2.0f);
	RedLogo->Transform.AddLocalPosition({ 600.0f, -35.0f, -static_cast<float>(ContentsOrder::UIImage) });

	RedTeamName = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedTeamName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
	RedTeamName->Transform.AddLocalPosition({ 400.0f, -20.0f, -static_cast<float>(ContentsOrder::UIImage) });

	RedTeamWinCount = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedTeamWinCount->SetText("Galmuri14", "0", 32.0f, float4::WHITE, FW1_CENTER);
	RedTeamWinCount->Transform.AddLocalPosition({ 90.0f, -15.0f, -static_cast<float>(ContentsOrder::UIImage) });
}

void BanPickBoard::LevelStart(GameEngineLevel* _PrevLevel)
{
	BlueLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);

}

void BanPickBoard::Update(float _Delta)
{

}

void BanPickBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}