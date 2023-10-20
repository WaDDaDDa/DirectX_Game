#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	Transform.SetWorldPosition(float4::ZERO);
	{
		MainSpriteRenderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
		MainSpriteRenderer->SetMaskTexture("TestMask.png");
		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("TestMask.png");
		Tex->SetScaleRatio(2.0f);
		MainSpriteRenderer->CreateAnimation("TestAni", "ArcherCardAni", 0.1f, 0, 4, false);
		MainSpriteRenderer->ChangeAnimation("TestAni");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(2.0f);
		MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
		GameEngineInput::AddInputObject(this);
	}
	BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::TestType);
	BodyCol->Transform.SetLocalScale(BodyColScale);
}

void Player::Update(float _Delta)
{
	// 페이드 예제
	// Renderer->GetColorData().MulColor.A -= _DeltaTime;
	float Speed = 100.0f;

	float4 WPos = Transform.GetWorldPosition();

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