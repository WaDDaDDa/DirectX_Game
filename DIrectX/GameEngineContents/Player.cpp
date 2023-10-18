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
	{
		//MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		//MainSpriteRenderer->CreateAnimation("Run", "HoHoYee_AttackABC");
		//MainSpriteRenderer->ChangeAnimation("Run");
		//MainSpriteRenderer->AutoSpriteSizeOn();

		// MainSpriteRenderer->SetSprite("TestPlayer.png", 5);
		// MaiSpriteRenderer->CreateAnimation
	}
}

void Player::Update(float _Delta)
{
	// 페이드 예제
	// Renderer->GetColorData().MulColor.A -= _DeltaTime;

}