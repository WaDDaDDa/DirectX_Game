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
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::FrontEffect) });
}

void FlameEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FlameEffect::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}
}