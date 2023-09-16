#include "PreCompile.h"
#include "GameUnit.h"



GameUnit::GameUnit()
{

}

GameUnit::~GameUnit()
{

}

void GameUnit::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

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
			// SpwanRenderer->ChangeAnimation("SpwanEffect");
			SpwanRenderer->AutoSpriteSizeOn();
		}

		{	// 콜리젼
			PushCol = CreateComponent<GameEngineCollision>(CollisionOrder::UnitBody);
			PushCol->Transform.SetLocalScale(PushColScale);
		}
	}
}

void GameUnit::LevelStart(GameEngineLevel* _PrevLevel)
{
	AggroUnit = EnemyGroup[0];
	ChangeState(GameUnitState::Spwan);
}

void GameUnit::LevelEnd(GameEngineLevel* _NextLevel)
{

}

// 팀정보 셋팅.  공격범위 같은것들도 셋팅됨.
void GameUnit::TeamSet(TeamType _Team)
{
	GameEngineRandom NewRandom;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	NewRandom.SetSeed(RandSeed);

	if (TeamType::Blue == _Team)
	{
		// 바디 충돌체
		BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);
		// 공격 범위 충돌체
		AttackRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamAttackRange);
		AttackRangeCol->Transform.SetLocalScale(AttackRange);

		float4 StartPos = NewRandom.RandomVectorBox2D(-250.0f, -280.0f, 100.0f, -100.0f);
		Transform.AddLocalPosition(StartPos);
		
		MyTeam = TeamType::Blue;
	}
	else if (TeamType::Red == _Team)
	{
		// 바디 충돌체
		BodyCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);

		// 공격 범위 충돌체
		AttackRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamAttackRange);
		AttackRangeCol->Transform.SetLocalScale(AttackRange);

		//ChangeDir(GameUnitDir::Left);
		float4 StartPos = NewRandom.RandomVectorBox2D(250.0f, 280.0f, 100.0f, -100.0f);
		Transform.AddLocalPosition(StartPos);

		MyTeam = TeamType::Red;
	}
}


void GameUnit::Update(float _Delta)
{
	StateUpdate(_Delta);

	AttackValue += _Delta;
	SkillValue += _Delta;
	UltValue += _Delta;
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
	case GameUnitState::Skill:
	case GameUnitState::Ult:
	case GameUnitState::Damage:
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
		case GameUnitState::Skill:
			break;
		case GameUnitState::Ult:
			break;
		case GameUnitState::Damage:
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
	SpwanRenderer->On();
	SpwanRenderer->ChangeAnimation("SpwanEffect");
}

void GameUnit::SpwanUpdate(float _Delta)
{
	if (true == SpwanRenderer->IsCurAnimationEnd())
	{
		SpwanRenderer->Off();
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
	// 적이 있다면으로 조건 변경.
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(GameUnitState::Move);
		return;
	}
}

// 어그로 유닛에게 다가가는 움직임.
void GameUnit::MoveStart()
{
	AggroSetting();

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = EnemyPos - MyPos;
	MoveDir.Normalize();
}

// 어그로 유닛에게 다가가는 움직임.
// 넘어갈 수 있는 State 종류 ( Idle, Attack, BackMove,  )
void GameUnit::MoveUpdate(float _Delta)
{
	ChangeDir();
	if (GetLiveTime() >= 3.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	// 공격 범위에 적군 body가 들어오면. 공격.
	if (TeamType::Blue == MyTeam)
	{
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackDelay <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackDelay <= AttackValue)
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}

	// 바디겹치면 멀어지는 움직임.
	if (PushCol->Collision(CollisionOrder::UnitBody))
	{
		ChangeState(GameUnitState::CollMove);
		return;
	}


	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// 어그로유닛에게서 멀어지는 움직임.
void GameUnit::BackMoveStart()
{
	AggroSetting();

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

// 어그로유닛에게서 멀어지는 움직임.
void GameUnit::BackMoveUpdate(float _Delta)
{
	ChangeDir();

	if (GetLiveTime() >= 4.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	Transform.AddLocalPosition((MoveDir * 50.0f * _Delta));
}

// 맵의 랜덤한 위치를 탐색해서 이동하는 움직임. 유닛 방향에따라 다름.
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

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

}

// 맵의 랜덤한 위치를 탐색해서 이동하는 움직임. 유닛 방향에따라 다름.
void GameUnit::SearchMoveUpdate(float _Delta)
{
	ChangeDir();

	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = TargetPos - MyPos;

	MoveDir.Normalize();

	Transform.AddLocalPosition((MoveDir * 100.0f * _Delta));
}

// 유닛들이 겹쳤을때 겹친것을 벗어나기 위한 움직임.
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

// 맵의 랜덤한 위치를 탐색해서 이동하는 움직임. 유닛 방향에따라 다름.
void GameUnit::CollMoveUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.2f)
	{
		ChangeState(GameUnitState::Move);
		return;
	}

	Transform.AddLocalPosition((MoveDir * 50.0f * _Delta));
}

void GameUnit::AttackStart()
{
	AttackValue = 0.0f;
}

void GameUnit::AttackUpdate(float _Delta)
{

}

void GameUnit::MaxStart()
{

}

void GameUnit::MaxUpdate(float _Delta)
{

}