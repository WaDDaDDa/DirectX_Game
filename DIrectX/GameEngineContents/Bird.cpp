#include "PreCompile.h"
#include "Bird.h"


Bird::Bird()
{

}

Bird::~Bird()
{

}

void Bird::Start()
{

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	Renderer->CreateAnimation("Bird", "Bird", 0.2f);
	Renderer->ChangeAnimation("Bird");
	Renderer->AutoSpriteSizeOn();
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });

	BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::TestType);
	BodyCol->Transform.SetLocalScale(BodyColScale);

	GameEngineInput::AddInputObject(this);

}

void Bird::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Bird::Update(float _Delta)
{
	float Speed = 100.0f;

	float4 WPos = Transform.GetWorldPosition();

	if (true == BodyCol->Collision(CollisionOrder::UnitBody))
	{
		int a = 0;
	}

	if (GameEngineInput::IsPress('2', this))
	{
		BodyCol->Off();
	}

	if (GameEngineInput::IsPress('3', this))
	{
		BodyCol->On();
	}

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
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E', this))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}