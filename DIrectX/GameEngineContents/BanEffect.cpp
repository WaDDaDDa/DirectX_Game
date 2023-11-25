#include "PreCompile.h"
#include "BanEffect.h"


BanEffect::BanEffect()
{

}

BanEffect::~BanEffect()
{

}

void BanEffect::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	Renderer->CreateAnimation("Ban", "BanPick", 0.05f, 0, 4, true);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	Renderer->ChangeAnimation("Ban");

	//»ç¿îµå
	GameEngineSound::SoundPlay("Dagger Stab.WAV");
}

void BanEffect::Init(float4 _Pos)
{
	Transform.SetWorldPosition(_Pos);
	Renderer->Transform.AddLocalPosition({ 0.0f, 10.0f, -static_cast<float>(ContentsOrder::UIImage) });
}

void BanEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BanEffect::Update(float _Delta)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		Death();
		return;
	}
}