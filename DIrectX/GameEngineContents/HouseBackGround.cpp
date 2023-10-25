#include "PreCompile.h"
#include "HouseBackGround.h"


HouseBackGround::HouseBackGround()
{

}

HouseBackGround::~HouseBackGround()
{

}

void HouseBackGround::Start()
{

}

void HouseBackGround::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 400.0f});

	BackGround = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	BackGround->SetSprite("BackGround", 0);
	//BackGround->SetImageScale(WindowScale);
	BackGround->AutoSpriteSizeOn();
	BackGround->SetAutoScaleRatio(2.0f);
	BackGround->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });
}

void HouseBackGround::Update(float _Delta)
{

}

void HouseBackGround::LevelEnd(GameEngineLevel* _NextLevel)
{

}