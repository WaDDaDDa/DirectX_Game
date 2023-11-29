#include "PreCompile.h"
#include "StadiumBoard.h"
#include "GameUnit.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"

StadiumBoard::StadiumBoard()
{

}

StadiumBoard::~StadiumBoard()
{

}

void StadiumBoard::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, 0.0f , 100.0f});

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

	NumCount1 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::Text);
	//NumCount1->SetSprite("Number", 0);
	//NumCount1->AutoSpriteSizeOn();
	//NumCount1->SetAutoScaleRatio(3.0f);
	NumCount1->SetText("Galmuri14", "", 32.0f, float4::WHITE, FW1_CENTER);
	NumCount1->Transform.AddLocalPosition({ 0.0f, -63.0f });
	NumCount1->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
}

void StadiumBoard::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameTime = 60.0f;

	TeamInfo::MyInfo.KillCount = 0;
	EnemyInfo::Info.KillCount = 0;

	BlueLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
	BlueTeamName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);

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

void StadiumBoard::Update(float _Delta)
{
	GameTime -= _Delta;

	BlueDieCount = 0;
	RedDieCount = 0;

	std::string TimeText = GameEngineString::Format("{:.1f}", GameTime);

	NumCount1->SetText("Galmuri14", TimeText, 16.0f, float4::WHITE, FW1_CENTER);

	// 팀설정
	for (size_t i = 0; i < BlueTeam.size(); i++)
	{
		BlueDieCount += BlueTeam[static_cast<int>(i)]->GetDieCount();
	}

	for (size_t i = 0; i < RedTeam.size(); i++)
	{
		RedDieCount += RedTeam[static_cast<int>(i)]->GetDieCount();
	}

	BlueKillCount = RedDieCount;
	RedKillCount = BlueDieCount;

	TeamInfo::MyInfo.KillCount = BlueKillCount;
	EnemyInfo::Info.KillCount = RedKillCount;

	BlueTeamWinCount->SetText("Galmuri14", std::to_string(BlueKillCount), 32.0f, float4::WHITE, FW1_CENTER);
	RedTeamWinCount->SetText("Galmuri14", std::to_string(RedKillCount), 32.0f, float4::WHITE, FW1_CENTER);

	if (0.0f >= GameTime)
	{
		if (BlueKillCount == RedKillCount)
		{
			return;
		}

		GameEngineCore::ChangeLevel("ResultLevel");
		return;
	}

}

void StadiumBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	// if 승패 머시기 해서 값 살려두기
	if (BlueKillCount > RedKillCount)
	{
		TeamInfo::MyInfo.WinCount += 1;
	}
	else if (RedKillCount > BlueKillCount)
	{
		EnemyInfo::Info.WinCount += 1;
	}

	Death();
}