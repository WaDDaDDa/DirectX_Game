#include "PreCompile.h"
#include "KnightEffect.h"
#include "GameUnit.h"


KnightEffect::KnightEffect()
{

}

KnightEffect::~KnightEffect()
{

}

void KnightEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("KnightEffect", "KnightEffect", 0.1f, 15, 19, false);
	Renderer->CreateAnimation("KnightEffect2", "KnightEffect", 0.1f, 20, 20, false);
	Renderer->ChangeAnimation("KnightEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
	//Renderer->Transform.AddLocalPosition({ 20.0f, -20.0f });
	//Renderer->SetPivotType(PivotType::Bottom);
}

void KnightEffect::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void KnightEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void KnightEffect::Update(float _Delta)
{
	Unit->AggroSetting(AgrUnit->GetPointer());

	Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());

	LifeTime -= _Delta;

	if (LifeTime <= 0.0f)
	{
		Death();
		return;
	}

	if (GameUnitState::DiePrev == Unit->GetState() || GameUnitState::Die == Unit->GetState())
	{
		Death();
		return;
	}

	if (true == Renderer->IsCurAnimation("KnightEffect"))
	{
		if (Renderer->IsCurAnimationEnd())
		{
			Renderer->Transform.AddLocalPosition({ 0.0f, 35.0f });

			Renderer->ChangeAnimation("KnightEffect2");
		}
		return;
	}
}