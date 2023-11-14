#include "PreCompile.h"
#include "Stadium.h"


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
}

void Stadium::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void Stadium::Update(float _Delta)
{

}

void Stadium::LevelEnd(GameEngineLevel* _NextLevel)
{

}