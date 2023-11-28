#include "PreCompile.h"
#include "FontEffect.h"

FontEffect::FontEffect()
{

}

FontEffect::~FontEffect()
{

}

void FontEffect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });

	Renderer->SetText("Galmuri14", "", 32.0f, float4::WHITE, FW1_CENTER);
}

void FontEffect::Init(float4 _Pos, float _Damage, float4 _Color, bool _Dir)
{
	std::string Text = GameEngineString::Format("{:.0f}", _Damage);

	Renderer->SetText("Galmuri14", Text, 16.0f, _Color, FW1_CENTER);

	Transform.SetWorldPosition(_Pos);

	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });

	if (false == _Dir)
	{
		GravityVector = float4::UP * 200.0f + float4::LEFT * 80.0f;

	}
	else if (true == _Dir)
	{
		GravityVector = float4::UP * 200.0f + float4::RIGHT * 80.0f;
	}


}

void FontEffect::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FontEffect::Update(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		Death();
		return;
	}

	GravityVector += float4::DOWN * GravityPower * _Delta;

	Transform.AddLocalPosition(GravityVector * _Delta);
}