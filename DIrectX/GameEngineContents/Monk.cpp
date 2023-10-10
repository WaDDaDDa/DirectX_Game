#include "PreCompile.h"
#include "Monk.h"


Monk::Monk()
{

}

Monk::~Monk()
{

}

void Monk::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Monk\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Monk\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Monk_ult.png");
	}

	SetUnitStatus();
}

void Monk::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Monk_Idle", "MonkAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Monk_Move", "MonkAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Monk_Attack", "MonkAni", 0.1f, 13, 15, false);
		MainSpriteRenderer->CreateAnimation("Monk_Attack2", "MonkAni", 0.1f, 16, 18, false);
		MainSpriteRenderer->CreateAnimation("Monk_Skill", "MonkAni", 0.1f, 34, 43, false);
		MainSpriteRenderer->CreateAnimation("Monk_Ult", "MonkAni", 0.1f, 44, 53, false);
		MainSpriteRenderer->CreateAnimation("Monk_Die", "MonkAni", 0.1f, 19, 33, false);

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("MonkSkillEffect", "MonkEffect", 0.1f, 17, 26, false);
		SkillEffectRenderer->CreateAnimation("MonkSkillBlack", "MonkEffect", 0.1f, 0, 0, false);
		SkillEffectRenderer->ChangeAnimation("MonkSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({0, -20.0f});
		SkillEffectRenderer->SetPivotType(PivotType::Bottom);

		MainSpriteRenderer->ChangeAnimation("Monk_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Monk::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Monk::SpwanStart()
{
	GameUnit::SpwanStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Idle");
}

void Monk::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Idle");
}

void Monk::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Move");
}

void Monk::BackMoveStart()
{
	GameUnit::BackMoveStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Move");
}

void Monk::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Move");
}

void Monk::AttackStart()
{
	GameUnit::AttackStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Attack");
}

void Monk::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}

void Monk::Attack2Start()
{
	GameUnit::Attack2Start();
	MainSpriteRenderer->ChangeAnimation("Monk_Attack2");
}

void Monk::Attack2Update(float _Delta)
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

		ChangeState(GameUnitState::Move);
		return;
	}
}

void Monk::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Skill");
	SkillEffectRenderer->ChangeAnimation("MonkSkillEffect");

	float CurHpRate = 1.0f;
	size_t TeamNum = 0;
	float HealTick = 2.0f;
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

		TeamGroup[TeamNum]->HealHP(UnitAtt * 0.6f);
		HealTick -= 1.0f;
	}

}

void Monk::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("MonkSkillBlack");

		//이벤트 사용.
		if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
		{
			return;
		}
		else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
		{
			return;
		}

		ChangeState(GameUnitState::Move);
		return;
	}
}

void Monk::UltStart()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Monk_Ult");

	//CreateUltEffect();
	// 어그로를 자신에게 끌고 자신의 방어력을 증가시킨다.
}

void Monk::UltUpdate(float _Delta)
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

		ChangeState(GameUnitState::Move);
		return;
	}
}

void Monk::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("MonkSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Monk_Die");
}
