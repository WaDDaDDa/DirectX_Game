#include "PreCompile.h"
#include "Swordman.h"


Swordman::Swordman()
{

}

Swordman::~Swordman()
{

}

void Swordman::Start()
{
	GameUnit::Start();

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Swordman\\");
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
		Dir.MoveChild("ContentsResources\\GameUnit\\Swordman\\");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("swordman_ult.png");
	}

	SetUnitStatus();

}

void Swordman::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Swordman_Idle", "SwordmanAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Swordman_Move", "SwordmanAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Swordman_Attack", "SwordmanAni", 0.2f, 14, 15, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Attack2", "SwordmanAni", 0.2f, 16, 17, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Skill", "SwordmanAni", 0.2f, 18, 20, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Skill2", "SwordmanAni", 0.1f, 21, 26, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Die", "SwordmanAni", 0.1f, 27, 34, false);
		
		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("SwordmanSkillEffect", "SwordmanEffect", 0.1f, 8, 13, false);
		SkillEffectRenderer->CreateAnimation("SwordmanSkillBlack", "SwordmanEffect", 0.1f, 23, 23, false);
		SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);

		MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Swordman::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Swordman::SpwanStart()
{
	GameUnit::SpwanStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
}

void Swordman::IdleStart()
{
	GameUnit::IdleStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
}

void Swordman::MoveStart()
{
	GameUnit::MoveStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::BackMoveStart()
{
	GameUnit::BackMoveStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::AttackStart()
{
	GameUnit::AttackStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Attack");
}

void Swordman::AttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Attack2);
		return;
	}
}


void Swordman::Attack2Start()
{
	GameUnit::Attack2Start();
	MainSpriteRenderer->ChangeAnimation("Swordman_Attack2");
}

void Swordman::Attack2Update(float _Delta)
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

void Swordman::SkillStart()
{
	GameUnit::SkillStart();
	MainSpriteRenderer->ChangeAnimation("Swordman_Skill");
}

void Swordman::SkillUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Skill2);
		return;
	}
}

void Swordman::Skill2Start()
{
	MainSpriteRenderer->ChangeAnimation("Swordman_Skill2");
	SkillEffectRenderer->ChangeAnimation("SwordmanSkillEffect");
	SkillDamageDeley = 0.1f;
	SkillTick = 3.0f;
}

void Swordman::Skill2Update(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");

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

	SkillDamageDeley -= _Delta;

	if (SkillTick <= 0.0f)
	{
		return;
	}

	if (SkillDamageDeley <= 0.0f)
	{
		if (TeamType::Blue == MyTeam)
		{
			SkillRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						// 공격대미지 공식
						reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 0.5f);
						SkillTick -= 1.0f;
						SkillDamageDeley = 0.1f;
						return;
					}
				});
		}
		else if (TeamType::Red == MyTeam)
		{

			SkillRangeCol->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						// 공격대미지 공식
						reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 0.5f);
						SkillTick -= 1.0f;
						SkillDamageDeley = 0.1f;
						return;
					}
				});
		}
	}

}

void Swordman::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Swordman_Die");
}