#include "PreCompile.h"
#include "Knight.h"


Knight::Knight()
{

}

Knight::~Knight()
{

}

void Knight::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });


}

void Knight::LevelStart(GameEngineLevel* _PrevLevel)
{
	// float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	// Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Knight_Idle", "Knight", 1.0f);
		MainSpriteRenderer->CreateAnimation("Knight_Move", "Knight", 0.2f, 2, 6);
		MainSpriteRenderer->ChangeAnimation("Knight_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	ChangeState(GameUnitState::Idle);
}

void Knight::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Knight::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Knight_Idle");

}

void Knight::MoveStart()
{
	MainSpriteRenderer->ChangeAnimation("Knight_Move");

}