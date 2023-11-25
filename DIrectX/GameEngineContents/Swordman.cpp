#include "PreCompile.h"
#include "Swordman.h"
#include "SwordmanUltEffect.h"

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

	}

	// 이벤트 셋팅
	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			if (TeamType::Blue == MyTeam)
			{
				// 궁극기 사용
				if (UltRangeCol->Collision(CollisionOrder::RedTeamBody) && UltCooltime <= UltValue && false == UseUlt)
				{
					AggroUnit = reinterpret_cast<GameUnit*>(_Col->GetActor());
					SwordUlt = true;
					return;
				}
			}
			else if (TeamType::Red == MyTeam)
			{
				// 궁극
				if (UltRangeCol->Collision(CollisionOrder::BlueTeamBody) && UltCooltime <= UltValue && false == UseUlt)
				{
					AggroUnit = reinterpret_cast<GameUnit*>(_Col->GetActor());
					SwordUlt = true;
					return;
				}
			}
		};

	Event.Stay = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			return false;
		};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			return false;
		};

	//SetUnitStatus(SwordmanStatus::SwordmanStat);
	SetUnitStatus(GameUnitStatus::SwordmanStat);

}

void Swordman::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
		MainSpriteRenderer->CreateAnimation("Swordman_Idle", "SwordmanAni", 0.2f, 0, 4);
		MainSpriteRenderer->CreateAnimation("Swordman_Move", "SwordmanAni", 0.2f, 5, 13);
		MainSpriteRenderer->CreateAnimation("Swordman_Attack", "SwordmanAni", 0.1f, 14, 15, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Attack2", "SwordmanAni", 0.1f, 16, 17, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Skill", "SwordmanAni", 0.1f, 18, 20, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Skill2", "SwordmanAni", 0.1f, 21, 26, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Ult", "SwordmanAni", 0.1f, 36, 39, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Ult2", "SwordmanAni", 0.1f, 40, 43, false);
		MainSpriteRenderer->CreateAnimation("Swordman_Die", "SwordmanAni", 0.1f, 27, 34, false);
		MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

		SkillEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
		SkillEffectRenderer->CreateAnimation("SwordmanSkillEffect", "SwordmanEffect", 0.1f, 8, 13, false);
		SkillEffectRenderer->CreateAnimation("SwordmanSkillBlack", "SwordmanEffect", 0.1f, 23, 23, false);
		SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
		SkillEffectRenderer->AutoSpriteSizeOn();
		SkillEffectRenderer->SetAutoScaleRatio(1.3f);
		SkillEffectRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::FrontEffect) });

		MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.3f);
	}

	GameUnit::LevelStart(_PrevLevel);
}

void Swordman::SpwanStart()
{
	GameUnit::SpwanStart();
	SkillEffectRenderer->On();
	SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
}

void Swordman::IdleStart()
{
	GameUnit::IdleStart();
	SkillEffectRenderer->On();
	SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Swordman_Idle");
}

void Swordman::MoveStart()
{
	GameUnit::MoveStart();
	SkillEffectRenderer->Off();

	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::BackMoveStart()
{
	GameUnit::BackMoveStart();
	SkillEffectRenderer->Off();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::SearchMoveStart()
{
	GameUnit::SearchMoveStart();
	SkillEffectRenderer->Off();
	MainSpriteRenderer->ChangeAnimation("Swordman_Move");
}

void Swordman::AttackStart()
{
	GameUnit::AttackStart();
	SkillEffectRenderer->Off();
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
	SkillEffectRenderer->Off();
	MainSpriteRenderer->ChangeAnimation("Swordman_Attack2");

	// 사운드
	GameEngineSound::SoundPlay("Light Sword Swing 3.WAV");
}

void Swordman::Attack2Update(float _Delta)
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

void Swordman::SkillStart()
{
	GameUnit::SkillStart();
	SkillEffectRenderer->Off();
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
	SkillEffectRenderer->On();
	SkillEffectRenderer->ChangeAnimation("SwordmanSkillEffect");
	SkillDamageDeley = 0.1f;
	SkillTick = 3.0f;
}

void Swordman::Skill2Update(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		SkillEffectRenderer->Off();
		SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
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

	SkillDamageDeley -= _Delta;

	if (SkillTick <= 0.0f)
	{
		return;
	}

	if (SkillDamageDeley <= 0.0f)
	{
		if (TeamType::Blue == MyTeam)
		{
			SkillCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						// 공격대미지 공식
						reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 0.9f, GetDynamic_Cast_This<GameUnit>());
						SkillTick -= 1.0f;
						SkillDamageDeley = 0.05f;
						// 사운드
						GameEngineSound::SoundPlay("Light Sword Swing 3.WAV");
						return;
					}
				});
		}
		else if (TeamType::Red == MyTeam)
		{

			SkillCol->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						// 공격대미지 공식
						reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt * 0.9f, GetDynamic_Cast_This<GameUnit>());
						SkillTick -= 1.0f;
						SkillDamageDeley = 0.05f;
						// 사운드
						GameEngineSound::SoundPlay("Light Sword Swing 3.WAV");
						return;
					}
				});
		}
	}

}

void Swordman::UltStart()
{
	GameUnit::UltStart();
	SwordUlt = false;
	SkillEffectRenderer->Off();
	MainSpriteRenderer->ChangeAnimation("Swordman_Ult");
}

void Swordman::UltUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Ult2);
		return;
	}
}

void Swordman::Ult2Start()
{
	GetLevel()->CreateActor<SwordmanUltEffect>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

	Transform.SetWorldPosition(AggroUnit->Transform.GetWorldPosition());

	if (AggroUnit->GetDir() == GameUnitDir::Left)
	{
		Transform.AddWorldPosition({ 30.0f,0.0f });
	}
	else if (AggroUnit->GetDir() == GameUnitDir::Right)
	{
		Transform.AddWorldPosition({ -30.0f,0.0f });
	}

	SkillEffectRenderer->Off();

	MainSpriteRenderer->ChangeAnimation("Swordman_Ult2");
}

void Swordman::Ult2Update(float _Delta)
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

void Swordman::DiePrevStart()
{
	GameUnit::DiePrevStart();
	SkillEffectRenderer->Off();

	SkillEffectRenderer->ChangeAnimation("SwordmanSkillBlack");
	MainSpriteRenderer->ChangeAnimation("Swordman_Die");
}

bool Swordman::UltCheck()
{
	//이벤트 사용.
	if (TeamType::Blue == MyTeam)
	{
		UltRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, Event);
	}
	else if (TeamType::Red == MyTeam)
	{
		UltRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, Event);
	}

	if (50.0f <= UltValue && false == UseUlt)
	{
		SwordUlt = true;
	}

	return SwordUlt;
}