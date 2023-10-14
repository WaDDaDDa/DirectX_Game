#include "PreCompile.h"
#include "BattleField.h"


BattleField::BattleField()
{

}

BattleField::~BattleField()
{

}

void BattleField::Start()
{

}

void BattleField::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 400.0f});

	BackGround = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	BackGround->SetSprite("stadium_sky_bg.png");
	BackGround->SetImageScale(WindowScale);
	BackGround->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });

	//BackGround->SetPivotType(PivotType::Bottom);

	Water1 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Water);
	Water1->CreateAnimation("Waterfall", "Waterfall");
	Water1->ChangeAnimation("Waterfall");
	Water1->AutoSpriteSizeOn();
	Water1->SetAutoScaleRatio(1.3f);
	Water1->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Water) });
	Water1->Transform.AddLocalPosition({-140.0f, -450.0f});

	Fleid = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Map);
	Fleid->SetSprite("stadium.png");
	Fleid->AutoSpriteSizeOn();
	Fleid->SetAutoScaleRatio(1.3f);
	Fleid->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Map) });
	Fleid->Transform.AddLocalPosition({0, -100.0f});

	Water2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Water);
	Water2->CreateAnimation("Waterfall", "Waterfall");
	Water2->ChangeAnimation("Waterfall");
	Water2->AutoSpriteSizeOn();
	Water2->SetAutoScaleRatio(1.3f);
	Water2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Water) });
	Water2->Transform.AddLocalPosition({ 140.0f, -450.0f });
}

void BattleField::Update(float _Delta)
{

}

void BattleField::LevelEnd(GameEngineLevel* _NextLevel)
{

}