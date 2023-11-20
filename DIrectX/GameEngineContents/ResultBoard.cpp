#include "PreCompile.h"
#include "ResultBoard.h"
#include "GameUnit.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"

ResultBoard::ResultBoard()
{

}

ResultBoard::~ResultBoard()
{

}

void ResultBoard::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, 0.0f , 200.0f });

	BackGround = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackGround);
	BackGround->SetSprite("set_result_ui_bg.png");
	BackGround->SetImageScale(WindowScale);
	//BackGround->SetPivotType(PivotType::Top);
	BackGround->Transform.AddLocalPosition({ 0.0f, -HalfWindowScale.Y, -static_cast<float>(ContentsOrder::BackGround) });

	ResultText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	ResultText->SetText("Galmuri14", "경기 결과", 32.0f, float4::WHITE, FW1_CENTER);
	ResultText->Transform.AddLocalPosition({ 0.0f, -165.0f, -static_cast<float>(ContentsOrder::Text) });

	WinText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	WinText->SetText("Galmuri14", "승리", 32.0f, float4::WHITE, FW1_CENTER);
	WinText->Transform.AddLocalPosition({ 0.0f, -280.0f, -static_cast<float>(ContentsOrder::Text) });

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

	MainBlueLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MainBlueLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	MainBlueLogo->AutoSpriteSizeOn();
	MainBlueLogo->SetAutoScaleRatio(2.0f);
	MainBlueLogo->Transform.AddLocalPosition({ -128.0f, -410.0f, -static_cast<float>(ContentsOrder::UIImage) });

	MainRedLogo = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MainRedLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
	MainRedLogo->AutoSpriteSizeOn();
	MainRedLogo->SetAutoScaleRatio(2.0f);
	MainRedLogo->Transform.AddLocalPosition({ 128.0f, -410.0f, -static_cast<float>(ContentsOrder::UIImage) });

	BlueWinCountText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	BlueWinCountText->SetText("Galmuri14", std::to_string(TeamInfo::MyInfo.WinCount), 32.0f, float4::WHITE, FW1_CENTER);
	BlueWinCountText->Transform.AddLocalPosition({ -30.0f, -400.0f, -static_cast<float>(ContentsOrder::Text) });

	Text = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	Text->SetText("Galmuri14", ":", 32.0f, float4::WHITE, FW1_CENTER);
	Text->Transform.AddLocalPosition({ 0.0f, -400.0f, -static_cast<float>(ContentsOrder::Text) });

	RedWinCountText = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	RedWinCountText->SetText("Galmuri14", std::to_string(EnemyInfo::Info.WinCount), 32.0f, float4::WHITE, FW1_CENTER);
	RedWinCountText->Transform.AddLocalPosition({ 30.0f, -400.0f, -static_cast<float>(ContentsOrder::Text) });

	MainBlueName = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MainBlueName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 24.0f, float4::WHITE, FW1_CENTER);
	MainBlueName->Transform.AddLocalPosition({ -126.0f, -460.0f, -static_cast<float>(ContentsOrder::UIImage) });

	MainRedName = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	MainRedName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 24.0f, float4::WHITE, FW1_CENTER);
	MainRedName->Transform.AddLocalPosition({ 126.0f, -460.0f, -static_cast<float>(ContentsOrder::UIImage) });

	Button = GetLevel()->CreateActor<Default_Button>();
	Button->Transform.SetLocalPositionZ({ 200.0f });
	Button->SetButtonText("진행하기");
	Button->Transform.AddLocalPosition({ 0.0f, -220.0f });

}

void ResultBoard::LevelStart(GameEngineLevel* _PrevLevel)
{
	BlueLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);

	BlueTeamWinCount->SetText("Galmuri14", std::to_string(TeamInfo::MyInfo.KillCount), 32.0f, float4::WHITE, FW1_CENTER);
	RedTeamWinCount->SetText("Galmuri14", std::to_string(EnemyInfo::Info.KillCount), 32.0f, float4::WHITE, FW1_CENTER);
	
	// 블루 윈
	if (TeamInfo::MyInfo.KillCount > EnemyInfo::Info.KillCount)
	{
		WinText->SetText("Galmuri14", "승리", 32.0f, { 204.0f / 255.0f, 1.0f, 58.0f / 255.0f }, FW1_CENTER);
		BlueWinCountText->SetText("Galmuri14", std::to_string(TeamInfo::MyInfo.WinCount), 32.0f, { 204.0f / 255.0f, 1.0f, 58.0f / 255.0f }, FW1_CENTER);

	}// 레드 윈
	else if (TeamInfo::MyInfo.KillCount < EnemyInfo::Info.KillCount)
	{
		WinText->SetText("Galmuri14", "패배", 32.0f, float4::RED, FW1_CENTER);
		RedWinCountText->SetText("Galmuri14", std::to_string(EnemyInfo::Info.WinCount), 32.0f, float4::RED, FW1_CENTER);
	}

	if (1 <= TeamInfo::MyInfo.WinCount)
	{
		BlueWin->SetSprite("win_indicator_1.png");
	}

	if (2 <= TeamInfo::MyInfo.WinCount)
	{
		BlueWin2->SetSprite("win_indicator_1.png");
	}

	if (1 <= EnemyInfo::Info.WinCount)
	{
		RedWin->SetSprite("win_indicator_1.png");
	}

	if (2 <= EnemyInfo::Info.WinCount)
	{
		RedWin2->SetSprite("win_indicator_1.png");
	}
}

void ResultBoard::Update(float _Delta)
{
	if (true == Button->GetIsClick())
	{
		if (2 == TeamInfo::MyInfo.WinCount)
		{
			TeamInfo::MyInfo.Win = true;
			GameEngineCore::ChangeLevel("AwardsLevel");
			return;
			// 엔딩레벨 진입
		}
		else if (2 == EnemyInfo::Info.WinCount)
		{
			TeamInfo::MyInfo.Win = false;
			// 엔딩레벨 진입
			GameEngineCore::ChangeLevel("AwardsLevel");
			return;
		}

		GameEngineCore::ChangeLevel("BanPickLevel");
	}
}

void ResultBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Button->Death();
	Death();
}