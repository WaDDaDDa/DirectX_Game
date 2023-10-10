#include "PreCompile.h"
#include "MonkShield.h"
#include "GameUnit.h"


MonkShield::MonkShield()
{

}

MonkShield::~MonkShield()
{

}

void MonkShield::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("MonkShield", "MonkEffect", 0.1f, 37, 37, false);
	Renderer->CreateAnimation("MonkShield2", "MonkEffect", 0.2f, 38, 42, true);
	Renderer->ChangeAnimation("MonkShield");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.5f);
	//Renderer->Transform.AddLocalPosition({ 20.0f, -20.0f });
	//Renderer->SetPivotType(PivotType::Bottom);
}

void MonkShield::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void MonkShield::Update(float _Delta)
{
	Unit->Immune = true;
	Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());

	LifeTime -= _Delta;

	if (LifeTime <= 0.0f)
	{
		Unit->Immune = false;
		Death();
	}

	if (GameUnitState::DiePrev == Unit->GetState() || GameUnitState::Die == Unit->GetState())
	{
		Unit->Immune = false;
		Death();
	}

	if (true == Renderer->IsCurAnimation("MonkShield"))
	{
		if (Renderer->IsCurAnimationEnd())
		{
			//Renderer->Transform.AddLocalPosition({ 20.0f, -20.0f });

			Renderer->ChangeAnimation("MonkShield2");
		}
		return;
	}

	//Transform.AddLocalRotation({ 0.0f, 360.0f * _Delta });

}