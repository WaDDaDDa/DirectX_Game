#include "PreCompile.h"
#include "Knight.h"
#include "KnightUltEffect.h"
#include "KnightEffect.h"

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Knight\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("knight_ult.png");
	}

	SetUnitStatus();
}

void Knight::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Knight_Idle", "KnightAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Knight_Move", "KnightAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Knight_Attack", "KnightAni", 0.1f, 14, 15, false);
		MainSpriteRenderer->CreateAnimation("Knight_Attack2", "KnightAni", 0.1f, 16, 19, false);
		MainSpriteRenderer->CreateAnimation("Knight_Skill", "KnightAni", 0.1f, 30, 36, false);
		MainSpriteRenderer->CreateAnimation("Knight_Ult", "KnightAni", 0.1f, 37, 43, false);
		MainSpriteRenderer->CreateAnimation("Knight_Die", "KnightAni", 0.1f, 22, 29, false);

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
	SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Knight_Idle");
}

void Knight::IdleStart()
{
	GameUnit::IdleStart();
	SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");
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
		ChangeState(GameUnitState::Attack2);
		return;
	}
}

void Knight::Attack2Start()
{
	GameUnit::Attack2Start();
	MainSpriteRenderer->ChangeAnimation("Knight_Attack2");
}

void Knight::Attack2Update(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		//이벤트 사용.
		if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
		{
			return;
		}
		else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
		{
			return;
		}
		ChangeState(GameUnitState::Idle);
		return;
	}
}

void Knight::SkillStart()
{
	GameUnit::SkillStart();
	AttackValue = 1.0f;
	MainSpriteRenderer->ChangeAnimation("Knight_Skill");
	SkillEffectRenderer->ChangeAnimation("KnightSkillEffect");
	// 어그로를 자신에게 끈다

	for (size_t i = 0; i < EnemyGroup.size(); i++)
	{
		if (EnemyGroup[i]->GetState() != GameUnitState::Die || EnemyGroup[i]->GetState() != GameUnitState::DiePrev)
		{
			// 전사 방어력 만큼 방어력 상승.
			GetLevel()->CreateActor<KnightEffect>()->SetUnit(EnemyGroup[i]->GetDynamic_Cast_This<GameUnit>(), GetDynamic_Cast_This<GameUnit>());

		}
	}

}

void Knight::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");

		//이벤트 사용.
		if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
		{
			return;
		}
		else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
		{
			return;
		}

		ChangeState(GameUnitState::Idle);
		return;
	}
}

void Knight::UltStart()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Knight_Ult");

	for (size_t i = 0; i < TeamGroup.size(); i++)
	{
		if (TeamGroup[i]->GetState() != GameUnitState::Die || TeamGroup[i]->GetState() != GameUnitState::DiePrev)
		{
			// 전사 방어력 만큼 방어력 상승.
			TeamGroup[i]->AddDef(UnitDef);
			GetLevel()->CreateActor<KnightUltEffect>()->SetUnit(TeamGroup[i]->GetDynamic_Cast_This<GameUnit>());
		}
	}
	//CreateUltEffect();
	// 어그로를 자신에게 끌고 자신의 방어력을 증가시킨다.
}

void Knight::UltUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		//이벤트 사용.
		if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
		{
			return;
		}
		else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
		{
			return;
		}

		ChangeState(GameUnitState::Idle);
		return;
	}
}

void Knight::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("KnightSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Knight_Die");
}

void Knight::CreateUltEffect()
{
	GetLevel()->CreateActor<KnightUltEffect>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}