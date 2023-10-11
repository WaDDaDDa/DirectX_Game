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

	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackGround);
	
	Renderer->SetSprite("stadium_VS.png");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->SetPivotType(PivotType::Top);
}

void StadiumBoard::Update(float _Delta)
{

}

void StadiumBoard::LevelEnd(GameEngineLevel* _NextLevel)
{

}