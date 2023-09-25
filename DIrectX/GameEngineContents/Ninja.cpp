#include "PreCompile.h"
#include "Ninja.h"


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
		MainSpriteRenderer->CreateAnimation("Ninja_Attack", "NinjaAni", 0.2f, 13, 14, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Attack2", "NinjaAni", 0.2f, 15, 17, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill", "NinjaAni", 0.05f, 28, 35, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Skill2", "NinjaAni", 0.1f, 36, 38, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Ult", "NinjaAni", 0.1f, 37, 43, false);
		MainSpriteRenderer->CreateAnimation("Ninja_Die", "NinjaAni", 0.1f, 18, 27, false);

		MainSpriteRenderer->FindAnimation("Ninja_Skill2")->Inter[2] = 0.2;

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("NinjaSkillEffect", "NinjaEffect", 0.05f, 7, 13, false);
		SkillEffectRenderer->CreateAnimation("NinjaSkillBlack", "NinjaEffect", 0.1f, 0, 0, false);
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
		Transform.AddWorldPosition({40.0f,0.0f});
	}
	else if (AggroUnit->GetDir() == GameUnitDir::Right)
	{
		Transform.AddWorldPosition({ -40.0f,0.0f });
	}
	MainSpriteRenderer->ChangeAnimation("Ninja_Skill2");
	SkillTick = 1.0f;
}

void Ninja::Skill2Update(float _Delta)
{
	ChangeDir();
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");

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

	if (SkillTick <= 0.0f)
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
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 1.5f);
					SkillTick -= 1.0f;
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
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 1.5f);
					SkillTick -= 1.0f;
					return;
				}
			});
	}
}

void Ninja::UltStart()
{
	GameUnit::UltStart();
	MainSpriteRenderer->ChangeAnimation("Ninja_Ult");

	//CreateUltEffect();
	// 어그로를 자신에게 끌고 자신의 방어력을 증가시킨다.
}

void Ninja::UltUpdate(float _Delta)
{
	//UltEffectRenderer->Transform.AddWorldRotation({ 0.0f, 360.0f * _Delta  });
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Idle);
		return;
	}
}

void Ninja::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("NinjaSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Ninja_Die");
}
