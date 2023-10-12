#include "PreCompile.h"
#include "KnightUltEffect.h"
#include "GameUnit.h"


KnightUltEffect::KnightUltEffect()
{

}

KnightUltEffect::~KnightUltEffect()
{

}

void KnightUltEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("KnightUltEffect", "KnightEffect", 0.1f, 8, 14, false);
	Renderer->CreateAnimation("KnightUltEffect2", "KnightEffect", 0.1f, 14, 14, false);
	Renderer->CreateAnimation("KnightUltBlack", "KnightEffect", 0.1f, 0, 0, false);
	Renderer->ChangeAnimation("KnightUltEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
	//Renderer->Transform.AddLocalPosition({ 20.0f, -20.0f });
	Renderer->SetPivotType(PivotType::Bottom);

	Renderer2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer2->CreateAnimation("KnightUltEffect", "KnightEffect", 0.1f, 8, 14, false);
	Renderer2->CreateAnimation("KnightUltEffect2", "KnightEffect", 0.1f, 14, 14, false);
	Renderer2->CreateAnimation("KnightUltBlack", "KnightEffect", 0.1f, 0, 0, false);
	Renderer2->ChangeAnimation("KnightUltBlack");
	Renderer2->AutoSpriteSizeOn();
	Renderer2->SetAutoScaleRatio(1.3f);
	Renderer2->Transform.AddLocalPosition({ -20.0f, -20.0f });
	Renderer2->SetPivotType(PivotType::Bottom);
}

void KnightUltEffect::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void KnightUltEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}


void KnightUltEffect::Update(float _Delta)
{
	Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());

	LifeTime -= _Delta;

	if (LifeTime <= 0.0f)
	{
		Unit->DefAbsolute();
		Death();
	}

	if (GameUnitState::DiePrev == Unit->GetState() || GameUnitState::Die == Unit->GetState())
	{
		Unit->DefAbsolute();
		Death();
	}

	if (true == Renderer->IsCurAnimation("KnightUltEffect"))
	{
		if (Renderer->IsCurAnimationEnd())
		{
			Renderer->Transform.AddLocalPosition({ 20.0f, -20.0f });

			Renderer->ChangeAnimation("KnightUltEffect2");
			Renderer2->ChangeAnimation("KnightUltEffect2");
		}
		return;
	}

	Transform.AddLocalRotation({ 0.0f, 360.0f * _Delta });
	// 방패가같이돌지않게 고정시키면 order에의해 캐릭터 뒤로 이펙트가 가지않음
	// 오더링이 해결되면 하는것으로.
	//Renderer->Transform.SetWorldRotation({ 0.0f,0.0f });
	//Renderer->SetOrder(ContentsOrder::BackEffect);
	//Renderer2->Transform.SetWorldRotation({ 0.0f,0.0f });
}