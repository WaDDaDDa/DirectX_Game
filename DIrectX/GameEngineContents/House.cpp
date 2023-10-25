#include "PreCompile.h"
#include "House.h"


House::House()
{

}

House::~House()
{

}

void House::Start()
{

}

void House::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 300.0f});

	Ground = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	Ground->SetSprite("House", 0);
	Ground->AutoSpriteSizeOn();
	Ground->SetAutoScaleRatio(3.0f);
	Ground->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });
	Ground->Transform.AddLocalPosition({ 0.0f, -290.0 });

	HouseRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	HouseRenderer->SetSprite("House", 1);
	HouseRenderer->AutoSpriteSizeOn();
	HouseRenderer->SetAutoScaleRatio(3.0f);
	HouseRenderer->Transform.AddLocalPosition({ 0.0f, -2.0f, -static_cast<float>(ContentsOrder::BackGround) });
}

void House::Update(float _Delta)
{

}

void House::LevelEnd(GameEngineLevel* _NextLevel)
{

}