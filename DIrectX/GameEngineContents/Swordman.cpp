#include "PreCompile.h"
#include "Swordman.h"


Swordman::Swordman()
{

}

Swordman::~Swordman()
{

}

void Swordman::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Swordman\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

}

void Swordman::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Swordman_Idle", "SwordmanAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Swordman_Move", "SwordmanAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Swordman_Attack", "SwordmanAni", 0.2f, 14, 19, false);
		MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Swordman::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Swordman::SpwanStart()
{
	GameUnit::SpwanStart();
}

void Swordman::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
}

void Swordman::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Swordman_Attack");
}

void Swordman::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::SearchMove);
		return;
	}
}
