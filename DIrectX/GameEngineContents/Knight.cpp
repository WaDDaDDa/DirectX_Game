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

	SetUnitStatus();
}

void Knight::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Knight_Idle", "KnightAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Knight_Move", "KnightAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Knight_Attack", "KnightAni", 0.2f, 14, 19, false);
		MainSpriteRenderer->CreateAnimation("Knight_Skill", "KnightAni", 0.1f, 30, 36, false);

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("KnightSkillEffect", "KnightEffect", 0.1f, 1, 5, false);
		SkillEffectRenderer->CreateAnimation("KnightSkillBlack", "KnightEffect", 0.1f, 0, 0, false);
		SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({0, -20.0f});
		SkillEffectRenderer->SetPivotType(PivotType::Bottom);

		MainSpriteRenderer->ChangeAnimation("Knight_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
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

void Knight::BackMoveStart()
{
	GameUnit::BackMoveStart();
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
		GameEngineRandom NewRand;
		int MoveRand = NewRand.RandomInt(0, 5);
		static long long RandSeed = reinterpret_cast<long long>(this);
		RandSeed++;
		NewRand.SetSeed(RandSeed);

		switch (MoveRand)
		{
		case 0:
			ChangeState(GameUnitState::Move);
			return;
		case 1:
		case 2:
		case 3:
			ChangeState(GameUnitState::SearchMove);
			return;
		case 4:
		case 5:
			ChangeState(GameUnitState::BackMove);
			return;
		default:
			break;
		}
	}
}

void Knight::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Skill");
	SkillEffectRenderer->ChangeAnimation("KnightSkillEffect");
	// 어그로를 자신에게 끌고 자신의 방어력을 증가시킨다.

}

void Knight::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");

		GameEngineRandom NewRand;
		int MoveRand = NewRand.RandomInt(0, 5);
		static long long RandSeed = reinterpret_cast<long long>(this);
		RandSeed++;
		NewRand.SetSeed(RandSeed);

		switch (MoveRand)
		{
		case 0:
			ChangeState(GameUnitState::Move);
			return;
		case 1:
		case 2:
		case 3:
			ChangeState(GameUnitState::SearchMove);
			return;
		case 4:
		case 5:
			ChangeState(GameUnitState::BackMove);
			return;
		default:
			break;
		}
	}
}