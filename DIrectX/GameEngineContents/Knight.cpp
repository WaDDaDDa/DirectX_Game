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
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Knight\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

}

void Knight::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Knight_Idle", "KnightAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Knight_Move", "KnightAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Knight_Attack", "KnightAni", 0.2f, 14, 19, false);
		MainSpriteRenderer->ChangeAnimation("Knight_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
		MainSpriteRenderer->SetPivotType(PivotType::Bottom);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Knight::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Knight::SpwanStart()
{
	GameUnit::SpwanStart();
}

void Knight::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Idle");
}

void Knight::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Move");
}

void Knight::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Move");
}

void Knight::AttackStart()
{
	GameUnit::AttackStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Attack");
}

void Knight::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Move);
		return;
	}
}
