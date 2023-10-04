#include "PreCompile.h"
#include "FlameEffect.h"


FlameEffect::FlameEffect()
{

}

FlameEffect::~FlameEffect()
{

}

void FlameEffect::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	Renderer->CreateAnimation("FlameEffect", "PyromancerEffect", 0.1f, 17, 24, false);
	Renderer->ChangeAnimation("FlameEffect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(1.3f);
}

void FlameEffect::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}
}