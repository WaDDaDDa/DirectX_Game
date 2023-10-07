#include "PreCompile.h"
#include "Archer.h"
#include "Arrow.h"

Archer::Archer()
{

}

Archer::~Archer()
{

}

void Archer::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Archer\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Archer\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Archer_ult.png");
		GameEngineSprite::CreateSingle("arrow.png");
	}

	SetUnitStatus();

}

void Archer::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Archer_Idle", "ArcherAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Archer_Move", "ArcherAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Archer_Attack", "ArcherAni", 0.1f, 13, 17, false);
		MainSpriteRenderer->CreateAnimation("Archer_Attack2", "ArcherAni", 0.1f, 18, 19, false);
		MainSpriteRenderer->CreateAnimation("Archer_Skill", "ArcherAni", 0.1f, 30, 35, false);
		MainSpriteRenderer->CreateAnimation("Archer_Skill2", "ArcherAni", 0.1f, 36, 37, false);
		MainSpriteRenderer->CreateAnimation("Archer_Ult", "ArcherAni", 0.1f, 38, 42, false);
		MainSpriteRenderer->CreateAnimation("Archer_Ult2", "ArcherAni", 0.1f, 43, 46, false);
		MainSpriteRenderer->CreateAnimation("Archer_Die", "ArcherAni", 0.1f, 20, 29, false);
		
		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("ArcherAttackEffect", "ArcherEffect", 0.1f, 7, 8, false);
		SkillEffectRenderer->CreateAnimation("ArcherSkillEffect", "ArcherEffect", 0.1f, 14, 15, false);
		SkillEffectRenderer->CreateAnimation("ArcherUltEffect", "ArcherEffect", 0.1f, 17, 25, false);
		SkillEffectRenderer->CreateAnimation("ArcherSkillBlack", "ArcherEffect", 0.1f, 26, 26, false);
		SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({ 30.0f, 4.0f});

		MainSpriteRenderer->ChangeAnimation("Archer_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Archer::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Archer::SpwanStart()
{
	GameUnit::SpwanStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Archer_Idle");
}

void Archer::IdleStart()
{
	GameUnit::IdleStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Archer_Idle");
}

void Archer::MoveStart()
{
	GameUnit::MoveStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Archer_Move");
}

void Archer::BackMoveStart()
{
	GameUnit::BackMoveStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Archer_Move");
}

void Archer::SearchMoveStart()
{
	
	GameUnit::SearchMoveStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");

	MainSpriteRenderer->ChangeAnimation("Archer_Move");
}

void Archer::AttackStart()
{
	GameUnit::AttackStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Archer_Attack");
}

void Archer::AttackUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}


void Archer::Attack2Start()
{
	AttackValue = 0.0f;

	GetLevel()->CreateActor<Arrow>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
	SkillEffectRenderer->ChangeAnimation("ArcherAttackEffect");
	MainSpriteRenderer->ChangeAnimation("Archer_Attack2");
}

void Archer::Attack2Update(float _Delta)
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

void Archer::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Archer_Skill");

	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

void Archer::SkillUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Skill2);
		return;
	}

	Transform.AddLocalPosition((MoveDir * UnitSpeed * 2.0f * _Delta));

}

void Archer::Skill2Start()
{
	MainSpriteRenderer->ChangeAnimation("Archer_Skill2");
	SkillEffectRenderer->ChangeAnimation("ArcherSkillEffect");
	GetLevel()->CreateActor<Arrow>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();

}

void Archer::Skill2Update(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
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

void Archer::UltStart()
{
	GameUnit::UltStart();

	MainSpriteRenderer->ChangeAnimation("Archer_Ult");
	SkillEffectRenderer->ChangeAnimation("ArcherUltEffect");
}

void Archer::UltUpdate(float _Delta)
{
	ChangeDir();

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Ult2);
		return;
	}
}

void Archer::Ult2Start()
{
	//GetLevel()->CreateActor<ArcherUltEffect>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
	MainSpriteRenderer->ChangeAnimation("Archer_Ult2");
	GetLevel()->CreateActor<Arrow>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}

void Archer::Ult2Update(float _Delta)
{
	ChangeDir();
	ArcherUltInter -= _Delta;
	if (0.0f >= ArcherUltInter)
	{
		GetLevel()->CreateActor<Arrow>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
		NextAggroChange();
		ArcherUltInter = 0.05f;
	}

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

void Archer::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("ArcherSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Archer_Die");
}

//bool Archer::UltCheck()
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