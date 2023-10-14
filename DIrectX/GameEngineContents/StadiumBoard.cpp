#include "PreCompile.h"
#include "StadiumBoard.h"
#include "GameUnit.h"

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
	Transform.SetLocalPosition({ 0.0f, HalfWindowScale.Y , 100.0f});

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
}

void StadiumBoard::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameTime = 60.0f;

}

void StadiumBoard::Update(float _Delta)
{
	GameTime -= _Delta;

	BlueDieCount = 0;
	RedDieCount = 0;

	// ÆÀ¼³Á¤
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

	if (0.0f >= GameTime)
	{
		GameEngineCore::ChangeLevel("IntroLevel");

	}

}

void StadiumBoard::LevelEnd(GameEngineLevel* _NextLevel)
{

}