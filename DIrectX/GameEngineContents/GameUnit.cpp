#include "PreCompile.h"
#include "GameUnit.h"

#include "GameUnitUI.h"
#include "PlayerCard.h"


#define MAP_LEFT 320.0f
#define MAP_RIGHT 950.0f
#define MAP_UP -250.0f
#define MAP_DOWN -620.0f

GameUnit::GameUnit()
{

}

GameUnit::~GameUnit()
{

}

void GameUnit::Start()
{
	Transform.AddLocalPosition({ 0.0f, 0.0f, 300.0f });

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
			SpwanRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::FrontEffect) });
			SpwanRenderer->AutoSpriteSizeOn();
		}
		{	// 콜리젼
			PushCol = CreateComponent<GameEngineCollision>(CollisionOrder::UnitBody);
			PushCol->Transform.SetLocalScale(PushColScale);
		}
	}

	// 이벤트 셋팅
	MoveEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			AggroSetting(_Col->GetActor()->GetDynamic_Cast_This<GameUnit>()->GetPointer());
			ChangeState(GameUnitState::Move);
			return;
		};

	MoveEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			ChangeState(GameUnitState::BackMove);
			return;
		};

	MoveEvent.Exit = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			ChangeState(GameUnitState::Move);
			return;
		};
}

void GameUnit::LevelStart(GameEngineLevel* _PrevLevel)
{
	AggroSetting(EnemyGroup[0]);
	ChangeState(GameUnitState::Spwan);
	// HPUI 생성
	GetLevel()->CreateActor<GameUnitUI>()->SetUnit(GetDynamic_Cast_This<GameUnit>());

	if (true == IsTitle)
	{
		return;
	}

	GetLevel()->CreateActor<PlayerCard>()->SetUnit(GetDynamic_Cast_This<GameUnit>());
}

void GameUnit::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
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
		// 스킬 범위 충돌체
		SkillRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamSkillRange);
		SkillRangeCol->Transform.SetLocalScale(SkillRange);
		// 스킬 충돌체
		SkillCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillCol->Transform.SetLocalScale(SkillColRange);
		// 궁극기 범위 충돌체
		UltRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamUltRange);
		UltRangeCol->Transform.SetLocalScale(UltRange);

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
		// 스킬 범위 충돌체
		SkillRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillRangeCol->Transform.SetLocalScale(SkillRange);
		// 스킬 충돌체
		SkillCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamSkillRange);
		SkillCol->Transform.SetLocalScale(SkillColRange);
		// 궁극기 범위 충돌체
		UltRangeCol = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamUltRange);
		UltRangeCol->Transform.SetLocalScale(UltRange);

		MyTeam = TeamType::Red;
	}
}

bool GameUnit::SkillCheck()
{
	if (TeamType::Blue == MyTeam)
	{
		// 스킬사용
		if (SkillRangeCol->Collision(CollisionOrder::RedTeamBody) && SkillCooltime <= SkillValue)
		{
			SkillRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						AggroSetting(reinterpret_cast<GameUnit*>(_Collision[i]->GetActor()));
					}
				});

			return true;
		}

	}
	else if (TeamType::Red == MyTeam)
	{
		//스킬
		if (SkillRangeCol->Collision(CollisionOrder::BlueTeamBody) && SkillCooltime <= SkillValue)
		{
			SkillRangeCol->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						AggroSetting(reinterpret_cast<GameUnit*>(_Collision[i]->GetActor()));
					}
				});

			return true;
		}
	}

	return false;
}

bool GameUnit::UltCheck()
{
	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (UltRangeCol->Collision(CollisionOrder::RedTeamBody) && UltCooltime <= UltValue && false == UseUlt)
		{
			return true;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (UltRangeCol->Collision(CollisionOrder::BlueTeamBody) && UltCooltime <= UltValue && false == UseUlt)
		{
			return true;
		}
	}

	return false;
}

bool GameUnit::AttCheck()
{
	AggroCheck = false;

	if (TeamType::Blue == MyTeam)
	{

		// 스킬사용
		if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue)
		{
			AttackRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						if (AggroUnit == reinterpret_cast<GameUnit*>(_Collision[i]->GetActor()))
						{
							AggroCheck = true;
						}
					}
				});
		}

	}
	else if (TeamType::Red == MyTeam)
	{
		//스킬
		if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
		{
			AttackRangeCol->Collision(CollisionOrder::BlueTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
				{
					for (size_t i = 0; i < _Collision.size(); i++)
					{
						if (AggroUnit == reinterpret_cast<GameUnit*>(_Collision[i]->GetActor()))
						{
							AggroCheck = true;
						}
					}
				});
		}
	}

	if (true == AggroCheck)
	{
		return true;
	}

	return false;



	//if (TeamType::Blue == MyTeam)
	//{
	//	// 궁극기 사용
	//	if (AttackRangeCol->Collision(CollisionOrder::RedTeamBody) && AttackSpeed <= AttackValue) 
	//	{
	//		return true;
	//	}
	//}
	//else if (TeamType::Red == MyTeam)
	//{
	//	// 궁극
	//	if (AttackRangeCol->Collision(CollisionOrder::BlueTeamBody) && AttackSpeed <= AttackValue)
	//	{
	//		return true;
	//	}
	//}

	//return false;
}

void GameUnit::MapOverCheck()
{
	// 맵왼쪽 끝
	if (MAP_LEFT >= Transform.GetWorldPosition().X)
	{
		Transform.SetWorldPosition({ MAP_LEFT + 1.0f, Transform.GetWorldPosition().Y, 300.0f });
		MoveDir = { -MoveDir.X, MoveDir.Y };
	}

	// 맵오른쪽 끝
	if (MAP_RIGHT <= Transform.GetWorldPosition().X)
	{
		Transform.SetWorldPosition({ MAP_RIGHT - 1.0f, Transform.GetWorldPosition().Y, 300.0f });
		MoveDir = { -MoveDir.X, MoveDir.Y };
	}

	// 맵 위끝
	if (MAP_UP <= Transform.GetWorldPosition().Y)
	{
		Transform.SetWorldPosition({ Transform.GetWorldPosition().X, MAP_UP - 1.0f, 300.0f });
		MoveDir = { MoveDir.X, -MoveDir.Y };
	}

	// 맵 아래끝
	if (MAP_DOWN >= Transform.GetWorldPosition().Y)
	{
		Transform.SetWorldPosition({ Transform.GetWorldPosition().X, MAP_DOWN + 1.0f, 300.0f });
		MoveDir = { MoveDir.X, -MoveDir.Y };
	}
}

void GameUnit::Update(float _Delta)
{
	// 색 원상복구
	if (true == DamageCheck)
	{
		DamageDelta += _Delta;

		if (0.1f <= DamageDelta)
		{
			MainSpriteRenderer->GetColorData().PlusColor -= float4::ONENULL;
			DamageDelta = 0.0f;
			DamageCheck = false;
		}
	}

	DieCheck();


	PushValue += _Delta;
	AttackValue += _Delta;
	SkillValue += _Delta;
	UltValue += _Delta;


	if (UnitHP <= 0.0f && ImDie == false)
	{
		ChangeState(GameUnitState::DiePrev);
		return;
	}

	if (true == AllEnemyDieCheck() && ImDie == false)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	if (AggroUnit->GetState() == GameUnitState::Die || AggroUnit->GetState() == GameUnitState::DiePrev)
	{
		NextAggro();
	}

	StateUpdate(_Delta);
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
	// 색 원상복구
	if (true == DamageCheck)
	{
		MainSpriteRenderer->GetColorData().PlusColor -= float4::ONE;
		DamageDelta = 0.0f;
		DamageCheck = false;
	}

	SkillEffectRenderer->Off();

	GameEngineRandom NewRandom;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	NewRandom.SetSeed(RandSeed);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	HalfWindowScale.Y = -HalfWindowScale.Y;
	HalfWindowScale.Z = 300.0f;
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
	ImDie = false;
	UnitHP = UnitMaxHP;
	SpwanRenderer->On();
	SpwanRenderer->ChangeAnimation("SpwanEffect");
}

void GameUnit::SpwanUpdate(float _Delta)
{
	if (true == SpwanRenderer->IsCurAnimationEnd())
	{
		ChangeState(GameUnitState::Idle);
		return;
	}
}

void GameUnit::IdleStart()
{
	SkillEffectRenderer->Off();
	SpwanRenderer->Off();
	SpwanRenderer->ChangeAnimation("SpwanEffectBlack");
	ChangeDir();
}

void GameUnit::IdleUpdate(float _Delta)
{
	// 적이 있다면으로 조건 변경.
	if (GetLiveTime() >= 0.2f)
	{

		ChangeState(GameUnitState::Move);
		return;
	}

	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// 스킬사용
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// 공격
		if (AttCheck())
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//스킬
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// 공격
		if (AttCheck())
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	
	//이벤트 사용.
	if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
	{
		return;
	}
	else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
	{
		return;
	}
}

// 어그로 유닛에게 다가가는 움직임.
void GameUnit::MoveStart()
{
	SkillEffectRenderer->Off();

	if (AggroUnit->GetState() == GameUnitState::Die || AggroUnit->GetState() == GameUnitState::DiePrev)
	{
		NextAggroChange();
	}
	//AggroSetting();

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
	if (AggroUnit->GetState() == GameUnitState::Die || AggroUnit->GetState() == GameUnitState::DiePrev)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	ChangeMoveDir();
	// 공격 범위에 적군 body가 들어오면. 공격.
	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// 스킬사용
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// 공격
		if (AttCheck()) 
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//스킬
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// 공격
		if (AttCheck()) 
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

	// 바디겹치면 멀어지는 움직임.
	if (PushCol->Collision(CollisionOrder::UnitBody) && PushDelay <= PushValue)
	{
		ChangeState(GameUnitState::CollMove);
		return;
	}

	MapOverCheck();

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// 어그로유닛에게서 멀어지는 움직임.
void GameUnit::BackMoveStart()
{
	SkillEffectRenderer->Off();

	//AggroSetting();

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

// 어그로유닛에게서 멀어지는 움직임.
void GameUnit::BackMoveUpdate(float _Delta)
{
	ChangeMoveDir();

	// 공격 범위에 적군 body가 들어오면. 공격.
	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// 스킬사용
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// 공격
		if (AttCheck()) 
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//스킬
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// 공격
		if (AttCheck()) 
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}

	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(GameUnitState::Move);
		return;
	}

	//이벤트 사용.
	if (TeamType::Blue == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::RedTeamBody, MoveEvent))
	{
		return;
	}
	else if (TeamType::Red == MyTeam && AttackRangeCol->CollisionEvent(CollisionOrder::BlueTeamBody, MoveEvent))
	{
		return;
	}

	MapOverCheck();

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// 맵의 랜덤한 위치를 탐색해서 이동하는 움직임. 유닛 방향에따라 다름.
void GameUnit::SearchMoveStart()
{
	SkillEffectRenderer->Off();

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
	ChangeMoveDir();

	// 공격 범위에 적군 body가 들어오면. 공격.
	if (TeamType::Blue == MyTeam)
	{
		// 궁극기 사용
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}

		// 스킬사용
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}

		// 공격
		if (AttCheck()) 
		{
			ChangeState(GameUnitState::Attack);
			return;
		}
	}
	else if (TeamType::Red == MyTeam)
	{
		// 궁극
		if (UltCheck())
		{
			ChangeState(GameUnitState::Ult);
			return;
		}
		//스킬
		if (SkillCheck())
		{
			ChangeState(GameUnitState::Skill);
			return;
		}
		// 공격
		if (AttCheck()) 
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

// 유닛들이 겹쳤을때 겹친것을 벗어나기 위한 움직임.
void GameUnit::CollMoveStart()
{
	PushCol->Collision(CollisionOrder::UnitBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			float4 EnemyPos = _Collision[i]->GetActor()->Transform.GetWorldPosition();
			//float4 EnemyPos = _Collision[i]->Transform.GetWorldPosition();
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
	ChangeMoveDir();

	if (GetLiveTime() >= 0.2f)
	{
		PushValue = 0.0f;
		ChangeState(GameUnitState::Idle);
		return;
	}

	MapOverCheck();

	Transform.AddLocalPosition((MoveDir * UnitSpeed * _Delta));
}

// 공격시전
void GameUnit::AttackStart()
{

}

void GameUnit::AttackUpdate(float _Delta)
{

}

// 공격 대미지
void GameUnit::Attack2Start()
{
	AttackValue = 0.0f;

	if (TeamType::Blue == MyTeam)
	{
		AttackRangeCol->Collision(CollisionOrder::RedTeamBody, [=](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
			{
				for (size_t i = 0; i < _Collision.size(); i++)
				{
					// 공격대미지 공식
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt, GetDynamic_Cast_This<GameUnit>());
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
					reinterpret_cast<GameUnit*>(_Collision[i]->GetActor())->DamageHP(UnitAtt, GetDynamic_Cast_This<GameUnit>());
					return;
				}
			});
	}

}

void GameUnit::Attack2Update(float _Delta)
{

}

// 스킬 시전
void GameUnit::SkillStart()
{
	AttackValue = 0.0f;
	SkillValue = 0.0f;
}

void GameUnit::SkillUpdate(float _Delta)
{

}

// 궁극기 시전
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
	DieCount += 1;
	SkillEffectRenderer->Off();

	SpwanRenderer->Off();
	SpwanRenderer->ChangeAnimation("SpwanEffectBlack");
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