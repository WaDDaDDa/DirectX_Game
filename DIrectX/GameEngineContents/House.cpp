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

	Table = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Table->SetSprite("furniture", 8);
	Table->AutoSpriteSizeOn();
	Table->SetAutoScaleRatio(3.0f);
	Table->SetPivotType(PivotType::Bottom);
	Table->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Table->Transform.AddLocalPosition({ -165.0f, -44.0 });

	Cabinet = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cabinet->SetSprite("furniture", 1);
	Cabinet->AutoSpriteSizeOn();
	Cabinet->SetAutoScaleRatio(3.0f);
	Cabinet->SetPivotType(PivotType::Bottom);
	Cabinet->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cabinet->Transform.AddLocalPosition({ -95.0f, -44.0 });

	Bed1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Bed1->SetSprite("furniture", 6);
	Bed1->AutoSpriteSizeOn();
	Bed1->SetAutoScaleRatio(3.0f);
	Bed1->SetPivotType(PivotType::Bottom);
	Bed1->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Bed1->Transform.AddLocalPosition({ -20.0f, -44.0 });

	Bed2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Bed2->SetSprite("furniture", 6);
	Bed2->AutoSpriteSizeOn();
	Bed2->SetAutoScaleRatio(3.0f);
	Bed2->SetPivotType(PivotType::Bottom);
	Bed2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Bed2->Transform.AddLocalPosition({ 75.0f, -44.0 });

	Bed3 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Bed3->SetSprite("furniture", 6);
	Bed3->AutoSpriteSizeOn();
	Bed3->SetAutoScaleRatio(3.0f);
	Bed3->SetPivotType(PivotType::Bottom);
	Bed3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Bed3->Transform.AddLocalPosition({ 170.0f, -44.0 });

	Cpu1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu1->SetSprite("furniture", 3);
	Cpu1->AutoSpriteSizeOn();
	Cpu1->SetAutoScaleRatio(3.0f);
	Cpu1->SetPivotType(PivotType::Bottom);
	Cpu1->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu1->Transform.AddLocalPosition({ -195.0f, -188.0 });

	Cpu2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu2->SetSprite("furniture", 3);
	Cpu2->AutoSpriteSizeOn();
	Cpu2->SetAutoScaleRatio(3.0f);
	Cpu2->SetPivotType(PivotType::Bottom);
	Cpu2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu2->Transform.AddLocalPosition({ -146.0f, -188.0 });

	Cpu3 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu3->SetSprite("furniture", 3);
	Cpu3->AutoSpriteSizeOn();
	Cpu3->SetAutoScaleRatio(3.0f);
	Cpu3->SetPivotType(PivotType::Bottom);
	Cpu3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu3->Transform.AddLocalPosition({ -97.0f, -188.0 });

	Cpu4 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu4->SetSprite("furniture", 3);
	Cpu4->AutoSpriteSizeOn();
	Cpu4->SetAutoScaleRatio(3.0f);
	Cpu4->SetPivotType(PivotType::Bottom);
	Cpu4->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu4->Transform.AddLocalPosition({ -48.0f, -188.0 });

	Cpu5 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu5->SetSprite("furniture", 3);
	Cpu5->AutoSpriteSizeOn();
	Cpu5->SetAutoScaleRatio(3.0f);
	Cpu5->SetPivotType(PivotType::Bottom);
	Cpu5->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu5->Transform.AddLocalPosition({ 1.0f, -188.0 });

	Cpu6 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Cpu6->SetSprite("furniture", 3);
	Cpu6->AutoSpriteSizeOn();
	Cpu6->SetAutoScaleRatio(3.0f);
	Cpu6->SetPivotType(PivotType::Bottom);
	Cpu6->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Cpu6->Transform.AddLocalPosition({ 50.0f, -188.0 });

	Tolilet = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	Tolilet->SetSprite("furniture", 21);
	Tolilet->AutoSpriteSizeOn();
	Tolilet->SetAutoScaleRatio(3.0f);
	Tolilet->SetPivotType(PivotType::Bottom);
	Tolilet->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	Tolilet->Transform.AddLocalPosition({ 122.0f, -188.0 });
	Tolilet->GetColorData().MulColor += {0.8f, 0.8f, 0.8f};


	ShowerRoom = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackEffect);
	ShowerRoom->SetSprite("furniture", 32);
	ShowerRoom->AutoSpriteSizeOn();
	ShowerRoom->SetAutoScaleRatio(3.0f);
	ShowerRoom->SetPivotType(PivotType::Bottom);
	ShowerRoom->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackEffect) });
	ShowerRoom->Transform.AddLocalPosition({ 195.0f, -188.0 });
	ShowerRoom->GetColorData().MulColor += {0.8f, 0.8f, 0.8f};

}

void House::Update(float _Delta)
{

}

void House::LevelEnd(GameEngineLevel* _NextLevel)
{

}