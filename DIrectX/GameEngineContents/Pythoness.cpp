#include "PreCompile.h"
#include "Pythoness.h"
#include "PythonessAttack.h"
#include "PythonessHeal.h"
#include "PythonessSkill.h"
#include "PythonessUlt.h"

Pythoness::Pythoness()
{

}

Pythoness::~Pythoness()
{

}

void Pythoness::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Pythoness\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Pythoness\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Pythoness_ult.png");
	}

	SetUnitStatus();

}

void Pythoness::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Pythoness_Idle", "PythonessAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Pythoness_Move", "PythonessAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Pythoness_Attack", "PythonessAni", 0.2f, 13, 14, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Attack2", "PythonessAni", 0.2f, 15, 16, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Heal1", "PythonessAni", 0.2f, 17, 18, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Heal2", "PythonessAni", 0.2f, 19, 20, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Skill", "PythonessAni", 0.2f, 72, 74, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Skill2", "PythonessAni", 0.2f, 75, 77, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Ult", "PythonessAni", 0.2f, 78, 81, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Ult2", "PythonessAni", 0.2f, 82, 83, false);
		MainSpriteRenderer->CreateAnimation("Pythoness_Die", "PythonessAni", 0.1f, 61, 71, false);
		
		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("PythonessAttack1Effect", "PythonessEffect", 0.2f, 0, 1, false);
		SkillEffectRenderer->CreateAnimation("PythonessAttack2Effect", "PythonessEffect", 0.2f, 2, 3, false);
		SkillEffectRenderer->CreateAnimation("PythonessHeal1Effect", "PythonessEffect", 0.2f, 4, 5, false);
		SkillEffectRenderer->CreateAnimation("PythonessHeal2Effect", "PythonessEffect", 0.2f, 6, 7, false);
		SkillEffectRenderer->CreateAnimation("PythonessSkill1Effect", "PythonessEffect", 0.2f, 8, 10, false);
		SkillEffectRenderer->CreateAnimation("PythonessSkill2Effect", "PythonessEffect", 0.2f, 11, 13, false);
		SkillEffectRenderer->CreateAnimation("PythonessUlt1Effect", "PythonessEffect", 0.2f, 14, 17, false);
		SkillEffectRenderer->CreateAnimation("PythonessUlt2Effect", "PythonessEffect", 0.2f, 18, 19, false);
		SkillEffectRenderer->CreateAnimation("PythonessSkillBlack", "PythonessEffect", 0.1f, 13, 13, false);
		SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);

		MainSpriteRenderer->ChangeAnimation("Pythoness_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Pythoness::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Pythoness::SpwanStart()
{
	GameUnit::SpwanStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pythoness_Idle");
}

void Pythoness::IdleStart()
{
	GameUnit::IdleStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pythoness_Idle");
}

void Pythoness::MoveStart()
{
	GameUnit::MoveStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pythoness_Move");
}

void Pythoness::BackMoveStart()
{
	GameUnit::BackMoveStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Pythoness_Move");
}

void Pythoness::SearchMoveStart()
{
	
	GameUnit::SearchMoveStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Pythoness_Move");
}

void Pythoness::AttackStart()
{
	GameUnit::AttackStart();

	// true면 공격  false면 힐
	if (true == AttVariable)
	{
		SkillEffectRenderer->ChangeAnimation("PythonessAttack1Effect");
		MainSpriteRenderer->ChangeAnimation("Pythoness_Attack");
	}
	else if (false == AttVariable)
	{
		SkillEffectRenderer->ChangeAnimation("PythonessHeal1Effect");
		MainSpriteRenderer->ChangeAnimation("Pythoness_Heal1");
	}
}

void Pythoness::AttackUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}


void Pythoness::Attack2Start()
{
	AttackValue = 0.0f;

	// true면 공격  false면 힐
	if (true == AttVariable)
	{
		SkillEffectRenderer->ChangeAnimation("PythonessAttack2Effect");
		MainSpriteRenderer->ChangeAnimation("Pythoness_Attack2");
		// 공격
		GetLevel()->CreateActor<PythonessAttack>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
		AttVariableSwitch();
	}
	else if (false == AttVariable)
	{
		SkillEffectRenderer->ChangeAnimation("PythonessHeal2Effect");
		MainSpriteRenderer->ChangeAnimation("Pythoness_Heal2");
		//힐
		GetLevel()->CreateActor<PythonessHeal>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
		AttVariableSwitch();
	}

}

void Pythoness::Attack2Update(float _Delta)
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

void Pythoness::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Pythoness_Skill");
	SkillEffectRenderer->ChangeAnimation("PythonessSkill1Effect");

	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

void Pythoness::SkillUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Skill2);
		return;
	}

}

void Pythoness::Skill2Start()
{
	MainSpriteRenderer->ChangeAnimation("Pythoness_Skill2");
	SkillEffectRenderer->ChangeAnimation("PythonessSkill2Effect");

	GetLevel()->CreateActor<PythonessSkill>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

}

void Pythoness::Skill2Update(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
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

	//Transform.AddLocalPosition((MoveDir * UnitSpeed * 2.0f * _Delta));

}

void Pythoness::UltStart()
{
	GameUnit::UltStart();

	MainSpriteRenderer->ChangeAnimation("Pythoness_Ult");
	SkillEffectRenderer->ChangeAnimation("PythonessUlt1Effect");
}

void Pythoness::UltUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Ult2);
		return;
	}
}

void Pythoness::Ult2Start()
{
	MainSpriteRenderer->ChangeAnimation("Pythoness_Ult2");
	SkillEffectRenderer->ChangeAnimation("PythonessUlt2Effect");

	GetLevel()->CreateActor<PythonessUlt>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}

void Pythoness::Ult2Update(float _Delta)
{
	ChangeDir();

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

void Pythoness::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("PythonessSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pythoness_Die");
}

//bool Pythoness::UltCheck()
//{
//	//이벤트 사용.
//	if (TeamType::Blue == MyTeam)
//	{
//		UltRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, Event);
//	}
//	else if (TeamType::Red == MyTeam)
//	{
//		UltRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
//	}
//
//}