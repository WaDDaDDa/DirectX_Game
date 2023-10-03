#include "PreCompile.h"
#include "Ninja.h"
#include "NinjaUlt.h"
#include "GameUnitUI.h"

Ninja::Ninja()
{

}

Ninja::~Ninja()
{

}

void Ninja::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Ninja\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Ninja\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Ninja_ult.png");
	}

	SetUnitStatus();
}

void Ninja::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Ninja_Idle", "NinjaAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Ninja_Move", "NinjaAni", 0.2f, 5, 12);
		MainSpriteRenderer->CreateAnimation("Ninja_Attack", "NinjaAni", 0.1f, 13, 14, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Attack2", "NinjaAni", 0.1f, 15, 17, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill", "NinjaAni", 0.05f, 28, 35, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill2", "NinjaAni", 0.1f, 36, 38, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Ult", "NinjaAni", 0.2f, 44, 49, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Die", "NinjaAni", 0.1f, 18, 27, false);

		MainSpriteRenderer->FindAnimation("Ninja_Skill2")->Inter[2] = 0.2;

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("NinjaSkillEffect", "NinjaEffect", 0.05f, 7, 13, false);
		SkillEffectRenderer->CreateAnimation("NinjaSkillBlack", "NinjaEffect", 0.1f, 0, 0, false);
		SkillEffectRenderer->CreateAnimation("NinjaUltEffect", "NinjaEffect", 0.2f, 22, 27, false);
		SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({0, -20.0f});
		SkillEffectRenderer->SetPivotType(PivotType::Bottom);

		MainSpriteRenderer->ChangeAnimation("Ninja_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Ninja::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Ninja::SpwanStart()
{
	GameUnit::SpwanStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Idle");
}

void Ninja::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Idle");
}

void Ninja::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Move");
}

void Ninja::BackMoveStart()
{
	GameUnit::BackMoveStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Move");
}

void Ninja::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Move");
}

void Ninja::AttackStart()
{
	GameUnit::AttackStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Attack");
}

void Ninja::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}

void Ninja::Attack2Start()
{
	GameUnit::Attack2Start();
	MainSpriteRenderer->ChangeAnimation("Ninja_Attack2");
}

void Ninja::Attack2Update(float _Delta)
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

void Ninja::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Skill");
	SkillEffectRenderer->ChangeAnimation("NinjaSkillEffect");
}

void Ninja::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Skill2);
		return;
	}
}

void Ninja::Skill2Start()
{
	GameUnit::SkillStart();
	Transform.SetWorldPosition(AggroUnit->Transform.GetWorldPosition());

	if (AggroUnit->GetDir() == GameUnitDir::Left)
	{
		Transform.AddWorldPosition({ 30.0f,0.0f});
	}
	else if (AggroUnit->GetDir() == GameUnitDir::Right)
	{
		Transform.AddWorldPosition({ -30.0f,0.0f });
	}
	MainSpriteRenderer->ChangeAnimation("Ninja_Skill2");
	SkillTick = 1;
}

void Ninja::Skill2Update(float _Delta)
{
	ChangeDir();
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");
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

	if (SkillTick <= 0)
	{
		return;
	}


	if (TeamType::Blue == MyTeam)
	{
		AttackRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			{
				for (size_t i = 0; i < _Collision.size(); i++)
				{
					// 공격대미지 공식
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 1.3f);
					SkillTick -= 1;
					return;
				}
			});
	}
	else if (TeamType::Red == MyTeam)
	{

		AttackRangeCol->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			{
				for (size_t i = 0; i < _Collision.size(); i++)
				{
					// 공격대미지 공식
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 1.3f);
					SkillTick -= 1;
					return;
				}
			});
	}
}

void Ninja::UltStart()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Ult");
	SkillEffectRenderer->ChangeAnimation("NinjaUltEffect");

	GameUnit* NinNin = GetLevel()->CreateActor<NinjaUlt>()->GetPointer();
	NinNin->EnemyUnitSetting(EnemyGroup);
	NinNin->TeamUnitSetting(TeamGroup);
	NinNin->ChangeDir(Dir);

	if (TeamType::Blue == MyTeam)
	{
		NinNin->TeamSet(TeamType::Blue);
	}
	else if (TeamType::Red == MyTeam)
	{
		NinNin->TeamSet(TeamType::Red);
	}

	NinNin->AggroSetting(AggroUnit);
	if (GameUnitDir::Left == Dir)
	{
		float4 PosValue = { 30.0f };
		NinNin->Transform.SetWorldPosition(Transform.GetWorldPosition() + PosValue);
	}
	else if (GameUnitDir::Right == Dir)
	{
		float4 PosValue = { -30.0f };
		NinNin->Transform.SetWorldPosition(Transform.GetWorldPosition() + PosValue);
	}
	// ChangeState(GameUnitState::Spwan);
	// HPUI 생성
	GetLevel()->CreateActor<GameUnitUI>()->SetUnit(NinNin->GetDynamic_Cast_This<GameUnit>());
}

void Ninja::UltUpdate(float _Delta)
{
	//UltEffectRenderer->Transform.AddWorldRotation({ 0.0f, 360.0f * _Delta  });	if (MainSpriteRenderer->IsCurAnimationEnd())

	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");

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

void Ninja::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Ninja_Die");
}
