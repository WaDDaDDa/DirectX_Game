#include "PreCompile.h"
#include "HouseBackGround.h"
#include "Cloud.h"


HouseBackGround::HouseBackGround()
{

}

HouseBackGround::~HouseBackGround()
{

}

void HouseBackGround::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 400.0f });

	BackGround = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	BackGround->SetSprite("BackGround", 0);
	//BackGround->SetImageScale(WindowScale);
	BackGround->AutoSpriteSizeOn();
	BackGround->SetAutoScaleRatio(2.0f);
	BackGround->Transform.AddLocalPosition({ 0.0f, 100.0f, -static_cast<float>(ContentsOrder::BackGround) });

	GetLevel()->CreateActor<Cloud>();
}

void HouseBackGround::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void HouseBackGround::Update(float _Delta)
{
	CloudDelta += _Delta;

	if (1.5f <= CloudDelta)
	{
		GetLevel()->CreateActor<Cloud>();
		CloudDelta = 0.0f;
	}
}

void HouseBackGround::LevelEnd(GameEngineLevel* _NextLevel)
{

}