#include "PreCompile.h"
#include "PriestHealEffect.h"


PriestHealEffect::PriestHealEffect()
{

}

PriestHealEffect::~PriestHealEffect()
{

}

void PriestHealEffect::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("PriestHealEffect", "PriestEffect", 0.1f, 30, 35, false);
	Renderer->ChangeAnimation("PriestHealEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::FrontEffect) });
}

void PriestHealEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void PriestHealEffect::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}
}