#include "PreCompile.h"
#include "HouseUnit.h"


HouseUnit::HouseUnit()
{

}

HouseUnit::~HouseUnit()
{

}

void HouseUnit::Start()
{
	Transform.SetLocalPosition({640.0f, -380.0f, 200.0f});

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

	HairRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Hair);
	HairRenderer->Transform.AddLocalPosition({ 0.0f, 40.0f, -static_cast<float>(ContentsOrder::Hair) });

	GameEngineInput::AddInputObject(this);
}

void HouseUnit::LevelStart(GameEngineLevel* _NextLevel)
{

}

void HouseUnit::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void HouseUnit::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W', this))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S', this))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q', this))
	{
		BodyRenderer->ChangeAnimation("Idle");
	}

	if (GameEngineInput::IsPress('E', this))
	{
		BodyRenderer->ChangeAnimation("Sleep");
	}
}