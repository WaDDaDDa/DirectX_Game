#include "PreCompile.h"
#include "Pyromancer.h"
#include "FlameAttack.h"
#include "FireSpirit.h"
#include "FlameUlt.h"

Pyromancer::Pyromancer()
{

}

Pyromancer::~Pyromancer()
{

}

void Pyromancer::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Pyromancer\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Pyromancer\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

	}

	//SetUnitStatus(PyromancerStatus::PyromancerStat);
	SetUnitStatus(GameUnitStatus::PyromancerStat);

}

void Pyromancer::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Idle", "PyromancerAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Move", "PyromancerAni", 0.2f, 5, 8);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Attack", "PyromancerAni", 0.1f, 9, 12, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Attack2", "PyromancerAni", 0.1f, 13, 16, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Skill", "PyromancerAni", 0.05f, 26, 29, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Skill2", "PyromancerAni", 0.05f, 30, 38, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Ult", "PyromancerAni", 0.2f, 39, 40, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Ult2", "PyromancerAni", 0.2f, 41, 42, false);
		MainSpriteRenderer->CreateAnimation("Pyromancer_Die", "PyromancerAni", 0.1f, 17, 25, false);
		MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("PyromancerUltEffect", "PyromancerEffect", 0.2f, 38, 44, false);
		SkillEffectRenderer->CreateAnimation("PyromancerSkillBlack", "PyromancerEffect", 0.1f, 30, 30, false);
		SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::FrontEffect) });

		MainSpriteRenderer->ChangeAnimation("Pyromancer_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Pyromancer::SpwanStart()
{
	GameUnit::SpwanStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Idle");
}

void Pyromancer::IdleStart()
{
	GameUnit::IdleStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Idle");
}

void Pyromancer::MoveStart()
{
	GameUnit::MoveStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Move");
}

void Pyromancer::BackMoveStart()
{
	GameUnit::BackMoveStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Pyromancer_Move");
}

void Pyromancer::SearchMoveStart()
{
	
	GameUnit::SearchMoveStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Pyromancer_Move");
}

void Pyromancer::AttackStart()
{
	GameUnit::AttackStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Attack");
}

void Pyromancer::AttackUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}


void Pyromancer::Attack2Start()
{
	AttackValue = 0.0f;

	GetLevel()->CreateActor<FlameAttack>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Attack2");
}

void Pyromancer::Attack2Update(float _Delta)
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

void Pyromancer::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Skill");

	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

void Pyromancer::SkillUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Skill2);
		return;
	}

}

void Pyromancer::Skill2Start()
{
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Skill2");

	GetLevel()->CreateActor<FireSpirit>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

}

void Pyromancer::Skill2Update(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
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

void Pyromancer::UltStart()
{
	GameUnit::UltStart();
	SkillEffectRenderer->On();
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Ult");
	SkillEffectRenderer->ChangeAnimation("PyromancerUltEffect");
}

void Pyromancer::UltUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Ult2);
		return;
	}
}

void Pyromancer::Ult2Start()
{
	//GetLevel()->CreateActor<PyromancerUltEffect>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Ult2");
	GetLevel()->CreateActor<FlameUlt>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}

void Pyromancer::Ult2Update(float _Delta)
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

void Pyromancer::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("PyromancerSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Pyromancer_Die");
}

//bool Pyromancer::UltCheck()
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