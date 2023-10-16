#include "PreCompile.h"
#include "BanPickBoard.h"
#include "GameUnit.h"

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
	Transform.SetLocalPosition({ 0.0f, HalfWindowScale.Y , 100.0f});

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
}

void BanPickBoard::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BanPickBoard::Update(float _Delta)
{

}

void BanPickBoard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}