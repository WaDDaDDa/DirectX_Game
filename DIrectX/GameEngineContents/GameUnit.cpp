#include "PreCompile.h"
#include "GameUnit.h"

#include "GameUnitUI.h"

GameUnit::GameUnit()
{

}

GameUnit::~GameUnit()
{

}

void GameUnit::Start()
{
	{

		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\GameUnit\\Unit_Effect\\");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

		{
			SpwanRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
			SpwanRenderer->CreateAnimation("SpwanEffect", "SpwanEffect", 0.1f, 0, 10, false);
			SpwanRenderer->CreateAnimation("SpwanEffectBlack", "SpwanEffect", 0.1f, 22, 22, false);
			// SpwanRenderer->ChangeAnimation("SpwanEffect");
			SpwanRenderer->AutoSpriteSizeOn();
		}

		{	// �ݸ���
			PushCol = CreateComponent<GameEngineCollision>(CollisionOrder::UnitBody);
			PushCol->Transform.SetLocalScale(PushColScale);
		}
	}
}

void GameUnit::LevelStart(GameEngineLevel* _PrevLevel)
{
	AggroUnit = EnemyGroup[0];
	ChangeState(GameUnitState::Spwan);
	// HPUI ����
	GetLevel()->CreateActor<GameUnitUI>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}

void GameUnit::LevelEnd(GameEngineLevel* _NextLevel)
{

}

// ������ ����.  ���ݹ��� �����͵鵵 ���õ�.
void GameUnit::TeamSet(TeamType _Team)
{
	GameEngineRandom NewRandom;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	NewRandom.SetSeed(RandSeed);

	if (TeamType::Blue == _Team)
	{
		// �ٵ� �浹ü
		BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);
		// ���� ���� �浹ü
		AttackRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamAttackRange);
		AttackRangeCol->Transform.SetLocalScale(AttackRange);
		// ��ų ���� �浹ü
		SkillRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamSkillRange);
		SkillRangeCol->Transform.SetLocalScale(SkillRange);
		// ��ų �浹ü
		SkillCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillCol->Transform.SetLocalScale(SkillColRange);
		// �ñر� ���� �浹ü
		UltRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamUltRange);
		UltRangeCol->Transform.SetLocalScale(UltRange);

		MyTeam = TeamType::Blue;
	}
	else if (TeamType::Red == _Team)
	{
		// �ٵ� �浹ü
		BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);

		// ���� ���� �浹ü
		AttackRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamAttackRange);
		AttackRangeCol->Transform.SetLocalScale(AttackRange);
		// ��ų ���� �浹ü
		SkillRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillRangeCol->Transform.SetLocalScale(SkillRange);
		// ��ų �浹ü
		SkillCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillCol->Transform.SetLocalScale(SkillColRange);
		// �ñر� ���� �浹ü
		UltRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamUltRange);
		UltRangeCol->Transform.SetLocalScale(UltRange);

		MyTeam = TeamType::Red;
	}
}

bool GameUnit::SkillCheck()
{
	if (TeamType::Blue == MyTeam)
	{
		// ��ų���
		if (SkillRangeCol->Collision(CollisionOrder::RedTeamBody) && SkillCooltime <= SkillValue)
		{
			return true;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		//��ų
		if (SkillRangeCol->Collision(CollisionOrder::BlueTeamBody) && SkillCooltime <= SkillValue)
		{
			return true;
		}
	}

	return false;
}

bool GameUnit::UltCheck()
{
	if (TeamType::Blue == MyTeam)
	{
		// �ñر� ���
		if (UltRangeCol->Collision(CollisionOrder::RedTeamBody) && UltCooltime <= UltValue && false == UseUlt)
		{
			return true;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// �ñ�
		if (UltRangeCol->Collision(CollisionOrder::BlueTeamBody) && UltCooltime <= UltValue && false == UseUlt)
		{
			return true;
		}
	}

	return false;
}


void GameUnit::Update(float _Delta)
{
	DieCheck();
	StateUpdate(_Delta);

	PushValue += _Delta;
	AttackValue += _Delta;
	SkillValue += _Delta;
	UltValue += _Delta;

	if (true == AllEnemyDieCheck() && ImDie == false)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	if (AggroUnit->GetState() == GameUnitState::Die || AggroUnit->GetState() == GameUnitState::DiePrev)
	{
		NextAggro();
	}

	// �̺�Ʈ ����
	//if (TeamType::Blue == MyTeam)
	//{
	//	BodyCol->CollisionEvent(CollisionOrder::RedTeamAttack, Event);
	//}
	//else if (TeamType::Red == MyTeam)
	//{
	//	BodyCol->CollisionEvent(CollisionOrder::BlueTeamAttack, Event);
	//}

	if (UnitHP <= 0.0f && ImDie == false)
	{
		ChangeState(GameUnitState::DiePrev);
		return;
	}
}


void GameUnit::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GameUnitState::Spwan:
		return SpwanUpdate(_Delta);
	case GameUnitState::Idle:
		return IdleUpdate(_Delta);
	case GameUnitState::Move:
		return MoveUpdate(_Delta);
	case GameUnitState::BackMove:
		return BackMoveUpdate(_Delta);
	case GameUnitState::SearchMove:
		return SearchMoveUpdate(_Delta);
	case GameUnitState::CollMove:
		return CollMoveUpdate(_Delta);
	case GameUnitState::Attack:
		return AttackUpdate(_Delta);
	case GameUnitState::Attack2:
		return Attack2Update(_Delta);
	case GameUnitState::Skill:
		return SkillUpdate(_Delta);
	case GameUnitState::Skill2:
		return Skill2Update(_Delta);
	case GameUnitState::Ult:
		return UltUpdate(_Delta);
	case GameUnitState::Ult2:
		return Ult2Update(_Delta);
	case GameUnitState::Damage:
	case GameUnitState::DiePrev:
		return DiePrevUpdate(_Delta);
	case GameUnitState::Die:
		return DieUpdate(_Delta);
	case GameUnitState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void GameUnit::ChangeState(GameUnitState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case GameUnitState::Spwan:
			SpwanStart();
			break;
		case GameUnitState::Idle:
			IdleStart();
			break;
		case GameUnitState::Move:
			MoveStart();
			break;
		case GameUnitState::BackMove:
			BackMoveStart();
			break;
		case GameUnitState::SearchMove:
			SearchMoveStart();
			break;
		case GameUnitState::CollMove:
			CollMoveStart();
			break;
		case GameUnitState::Attack:
			AttackStart();
			break;
		case GameUnitState::Attack2:
			Attack2Start();
			break;
		case GameUnitState::Skill:
			SkillStart();
			break;
		case GameUnitState::Skill2:
			Skill2Start();
			break;
		case GameUnitState::Ult:
			UltStart();
			break;
		case GameUnitState::Ult2:
			Ult2Start();
			break;
		case GameUnitState::Damage:
			break;
		case GameUnitState::DiePrev:
			DiePrevStart();
			break;
		case GameUnitState::Die:
			DieStart();
			break;
		case GameUnitState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void GameUnit::SpwanStart()
{
	GameEngineRandom NewRandom;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	NewRandom.SetSeed(RandSeed);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	HalfWindowScale.Y = -HalfWindowScale.Y;
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	if (TeamType::Blue == MyTeam)
	{
		float4 StartPos = NewRandom.RandomVectorBox2D(-220.0f, -280.0f, 80.0f, -150.0f);
		Transform.SetWorldPosition(StartPos + HalfWindowScale);
	}
	else if (TeamType::Red == MyTeam)
	{
		float4 StartPos = NewRandom.RandomVectorBox2D(220.0f, 280.0f, 80.0f, -150.0f);
		Transform.SetWorldPosition(StartPos + HalfWindowScale);
	}
	UnitHP = UnitMaxHP;
	SpwanRenderer->On();
	SpwanRenderer->ChangeAnimation("SpwanEffect");
}

void GameUnit::SpwanUpdate(float _Delta)
{
	if (true == SpwanRenderer->IsCurAnimationEnd())
	{
		SpwanRenderer->Off();
		SpwanRenderer->ChangeAnimation("SpwanEffectBlack");
		ChangeState(GameUnitState::Idle);
		return;
	}
}

void GameUnit::IdleStart()
{
	ChangeDir();
}

void GameUnit::IdleUpdate(float _Delta)
{
	// ���� �ִٸ����� ���� ����.
	if (GetLiveTime() >= 0.5f)
	{

		ChangeState(GameUnitState::Move);
		return;
	}
}

// ��׷� ���ֿ��� �ٰ����� ������.
void GameUnit::MoveStart()
{
	AggroSetting();

	// ����ġ - ����ġ
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = EnemyPos - MyPos;
	MoveDir.Normalize();
}

// ��׷� ���ֿ��� �ٰ����� ������.
// �Ѿ �� �ִ� State ���� ( Idle, Attack, BackMove,  )
void GameUnit::MoveUpdate(float _Delta)
{
	ChangeMoveDir();

	// ���� ������ ���� body�� ������. ����.
	if (TeamType::Blue == MyTeam)
	{
		// �ñر� ���
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// ��ų���
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// ����
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// �ñ�
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//��ų
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// ����
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}

	if (GetLiveTime() >= 2.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	// �ٵ��ġ�� �־����� ������.
	if (PushCol->Collision(CollisionOrder::UnitBody) && PushDelay <= PushValue)
	{
		ChangeState(GameUnitState::CollMove);
		return;
	}


	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// ��׷����ֿ��Լ� �־����� ������.
void GameUnit::BackMoveStart()
{
	//AggroSetting();

	// ����ġ - ����ġ
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

// ��׷����ֿ��Լ� �־����� ������.
void GameUnit::BackMoveUpdate(float _Delta)
{
	ChangeMoveDir();

	// ���� ������ ���� body�� ������. ����.
	if (TeamType::Blue == MyTeam)
	{
		// �ñر� ���
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// ��ų���
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// ����
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// �ñ�
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//��ų
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// ����
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}

	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// ���� ������ ��ġ�� Ž���ؼ� �̵��ϴ� ������. ���� ���⿡���� �ٸ�.
void GameUnit::SearchMoveStart()
{
	GameEngineRandom Rand;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	Rand.SetSeed(RandSeed);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	TargetPos = Rand.RandomVectorBox2D(-340.0f, 340.0f, -250.0f, 110.0f);
	TargetPos += { HalfWindowScale.X, -HalfWindowScale.Y };

	// ����ġ - ����ġ
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

}

// ���� ������ ��ġ�� Ž���ؼ� �̵��ϴ� ������. ���� ���⿡���� �ٸ�.
void GameUnit::SearchMoveUpdate(float _Delta)
{
	ChangeMoveDir();

	// ���� ������ ���� body�� ������. ����.
	if (TeamType::Blue == MyTeam)
	{
		// �ñر� ���
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// ��ų���
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// ����
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// �ñ�
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//��ų
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// ����
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}

	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = TargetPos - MyPos;

	MoveDir.Normalize();

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// ���ֵ��� �������� ��ģ���� ����� ���� ������.
void GameUnit::CollMoveStart()
{
	PushCol->Collision(CollisionOrder::UnitBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			float4 EnemyPos = _Collision[i]->Transform.GetWorldPosition();
			float4 MyPos = this->Transform.GetWorldPosition();
			MoveDir = -(EnemyPos - MyPos);
			MoveDir.Normalize();
			return;
		}
	});

}

// ���� ������ ��ġ�� Ž���ؼ� �̵��ϴ� ������. ���� ���⿡���� �ٸ�.
void GameUnit::CollMoveUpdate(float _Delta)
{
	ChangeMoveDir();

	if (GetLiveTime() >= 0.2f)
	{
		PushValue = 0.0f;
		ChangeState(GameUnitState::Move);
		return;

		GameEngineRandom NewRand;
		int MoveRand = NewRand.RandomInt(0, 3);
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

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// ���ݽ���
void GameUnit::AttackStart()
{

}

void GameUnit::AttackUpdate(float _Delta)
{

}

// ���� �����
void GameUnit::Attack2Start()
{
	AttackValue = 0.0f;

	if (TeamType::Blue == MyTeam)
	{
		AttackRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			{
				for (size_t i = 0; i < _Collision.size(); i++)
				{
					// ���ݴ���� ����
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt);
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
					// ���ݴ���� ����
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt);
					return;
				}
			});
	}

}

void GameUnit::Attack2Update(float _Delta)
{

}

// ��ų ����
void GameUnit::SkillStart()
{
	AttackValue = 0.0f;
	SkillValue = 0.0f;
}

void GameUnit::SkillUpdate(float _Delta)
{

}

// �ñر� ����
void GameUnit::UltStart()
{
	UseUlt = true;
}

void GameUnit::UltUpdate(float _Delta)
{

}

void GameUnit::Ult2Start()
{

}

void GameUnit::Ult2Update(float _Delta)
{

}

void GameUnit::DiePrevStart()
{
	ImDie = true;
}

void GameUnit::DiePrevUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Die);
		return;
	}
}

void GameUnit::DieStart()
{

}

void GameUnit::DieUpdate(float _Delta)
{
	RespawnTime += _Delta;

	if (RespawnTime >= 5.0f)
	{
		RespawnTime = 0.0f;
		ImDie = false;
		ChangeState(GameUnitState::Spwan);
		return;
	}
}

void GameUnit::MaxStart()
{

}

void GameUnit::MaxUpdate(float _Delta)
{

}