#include "PreCompile.h"
#include "StadiumBoard.h"


StadiumBoard::StadiumBoard()
{

}

StadiumBoard::~StadiumBoard()
{

}

void StadiumBoard::Start()
{

}

void StadiumBoard::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 0.0f, HalfWindowScale.Y});

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	
	Renderer->SetSprite("stadium_VS.png");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->SetPivotType(PivotType::Top);

	BlueWin = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueWin->SetSprite("win_indicator_0.png");
	BlueWin->AutoSpriteSizeOn();
	BlueWin->SetAutoScaleRatio(2.0f);
	BlueWin->Transform.SetLocalPosition({ -135.0f,-65.0f });

	BlueWin2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	BlueWin2->SetSprite("win_indicator_0.png");
	BlueWin2->AutoSpriteSizeOn();
	BlueWin2->SetAutoScaleRatio(2.0f);
	BlueWin2->Transform.SetLocalPosition({ -115.0f,-65.0f });

	RedWin = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedWin->SetSprite("win_indicator_0.png");
	RedWin->AutoSpriteSizeOn();
	RedWin->SetAutoScaleRatio(2.0f);
	RedWin->Transform.SetLocalPosition({ 115.0f,-65.0f });
	
	RedWin2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	RedWin2->SetSprite("win_indicator_0.png");
	RedWin2->AutoSpriteSizeOn();
	RedWin2->SetAutoScaleRatio(2.0f);
	RedWin2->Transform.SetLocalPosition({ 135.0f,-65.0f });

}

void StadiumBoard::Update(float _Delta)
{

}

void StadiumBoard::LevelEnd(GameEngineLevel* _NextLevel)
{

}