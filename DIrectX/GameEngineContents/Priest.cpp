#include "PreCompile.h"
#include "Priest.h"
#include "PriestUlt.h"

Priest::Priest()
{

}

Priest::~Priest()
{

}

void Priest::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Priest\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Priest\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Priest_ult.png");
	}

	SetUnitStatus();
}

void Priest::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Priest_Idle", "PriestAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Priest_Move", "PriestAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Priest_Attack", "PriestAni", 0.1f, 13, 17, false);
		MainSpriteRenderer->CreateAnimation("Priest_Attack2", "PriestAni", 0.1f, 18, 22, false);
		MainSpriteRenderer->CreateAnimation("Priest_Skill", "PriestAni", 0.1f, 33, 41, false);
		MainSpriteRenderer->CreateAnimation("Priest_Ult", "PriestAni", 0.1f, 42, 45, false);
		MainSpriteRenderer->CreateAnimation("Priest_Ult2", "PriestAni", 0.1f, 46, 51, false);
		MainSpriteRenderer->CreateAnimation("Priest_Die", "PriestAni", 0.1f, 23, 32, false);

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("PriestAttackEffect", "PriestEffect", 0.1f, 2, 8, false);
		SkillEffectRenderer->CreateAnimation("PriestSkillEffect", "PriestEffect", 0.1f, 2, 8, false);
		SkillEffectRenderer->CreateAnimation("PriestUltEffect", "PriestEffect", 0.1f, 22, 28, false);
		SkillEffectRenderer->CreateAnimation("PriestSkillBlack", "PriestEffect", 0.1f, 0, 0, false);
		SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({0, -20.0f});
		SkillEffectRenderer->SetPivotType(PivotType::Bottom);

		MainSpriteRenderer->ChangeAnimation("Priest_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

bool Priest::AttCheck()
{
	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			return true;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			return true;
		}
	}

	return false;
}


void Priest::SpwanStart()
{
	GameUnit::SpwanStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Idle");
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
}

void Priest::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Idle");
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
}

void Priest::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Move");
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
}

void Priest::BackMoveStart()
{
	GameUnit::BackMoveStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Move");
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
}

void Priest::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Move");
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
}

void Priest::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Priest_Attack");
	SkillEffectRenderer->ChangeAnimation("PriestAttackEffect");

}

void Priest::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}

void Priest::Attack2Start()
{
	MainSpriteRenderer->ChangeAnimation("Priest_Attack2");

	AttackValue = 0.0f;

	float CurHpRate = 1.0f;
	size_t TeamNum = 0;
	float HealTick = 1.0f;
	// 회복 한다.
	while (HealTick > 0.0f)
	{
		for (size_t i = 0; i < EnemyGroup.size(); i++)
		{
			if (TeamGroup[i]->GetState() == GameUnitState::Die || TeamGroup[i]->GetState() == GameUnitState::DiePrev)
			{
				continue;
			}

			if (CurHpRate >= TeamGroup[i]->GetHPRate())
			{
				CurHpRate = TeamGroup[i]->GetHPRate();
				TeamNum = i;
			}
		}

		TeamGroup[TeamNum]->HealHP(UnitAtt);
		HealTick -= 1.0f;
	}

}

void Priest::Attack2Update(float _Delta)
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

void Priest::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Skill");
	SkillEffectRenderer->ChangeAnimation("PriestSkillEffect");

	float CurHpRate = 1.0f;
	size_t TeamNum = 0;
	float HealTick = 2.0f;
	// 회복 한다.
	while (HealTick > 0.0f)
	{
		for (size_t i = 0; i < EnemyGroup.size(); i++)
		{
			if (TeamGroup[i]->GetState() != GameUnitState::Die || TeamGroup[i]->GetState() != GameUnitState::DiePrev)
			{
				if (CurHpRate >= TeamGroup[i]->GetHPRate())
				{
					CurHpRate = TeamGroup[i]->GetHPRate();
					TeamNum = i;
				}
			}
		}

		TeamGroup[TeamNum]->HealHP(UnitAtt * 0.6f);
		HealTick -= 1.0f;
	}

}

void Priest::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");

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

void Priest::UltStart()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Ult");
}

void Priest::UltUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Ult2);
		return;
	}
}

void Priest::Ult2Start()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Priest_Ult2");
	SkillEffectRenderer->ChangeAnimation("PriestUltEffect");
	GetLevel()->CreateActor<PriestUlt>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

	//CreateUltEffect();
	// 어그로를 자신에게 끌고 자신의 방어력을 증가시킨다.
}

void Priest::Ult2Update(float _Delta)
{
	//UltEffectRenderer->Transform.AddWorldRotation({ 0.0f, 360.0f * _Delta  });
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

void Priest::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("PriestSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Priest_Die");
}
