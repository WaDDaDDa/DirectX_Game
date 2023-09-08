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
			//BodyCol = CreateComponent<GameEngineCollision>(ColOrder::UnitBody);
			//BodyCol->Transform.SetLocalScale(BodyColScale);
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

void GameUnit::TeamSet(TeamType _Team)
{
	GameEngineRandom NewRandom;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	NewRandom.SetSeed(RandSeed);

	if (TeamType::Blue == _Team)
	{
		BodyCol = CreateComponent<GameEngineCollision>(ColOrder::BlueTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);

		float4 StartPos = NewRandom.RandomVectorBox2D(-250.0f, -280.0f, 100.0f, -100.0f);
		Transform.AddLocalPosition(StartPos);
	}
	else if (TeamType::Red == _Team)
	{
		BodyCol = CreateComponent<GameEngineCollision>(ColOrder::RedTeamBody);
		BodyCol->Transform.SetLocalScale(BodyColScale);

		//ChangeDir(GameUnitDir::Left);
		float4 StartPos = NewRandom.RandomVectorBox2D(250.0f, 280.0f, 100.0f, -100.0f);
		Transform.AddLocalPosition(StartPos);
	}
}


void GameUnit::Update(float _Delta)
{
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
	case GameUnitState::Att:
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
		case GameUnitState::Att:
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

	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(GameUnitState::SearchMove);
		return;
	}
}

void GameUnit::MoveStart()
{
	AggroSetting();

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = EnemyPos - MyPos;
	MoveDir.Normalize();
}

void GameUnit::MoveUpdate(float _Delta)
{
	ChangeDir();
	if (GetLiveTime() >= 3.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	Transform.AddLocalPosition((MoveDir * 50.0f * _Delta));
}

void GameUnit::BackMoveStart()
{
	AggroSetting();

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	float4 MoveDir = -(EnemyPos - MyPos);
	MoveDir.Normalize();
}

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

void GameUnit::SearchMoveStart()
{
	GameEngineRandom Rand;
	static long long RandSeed = reinterpret_cast<long long>(this);
	RandSeed++;
	Rand.SetSeed(RandSeed);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	TargetPos = Rand.RandomVectorBox2D(-340.0f, 340.0f, -250.0f, 110.0f);
	TargetPos += { HalfWindowScale.X, -HalfWindowScale.Y, -500.0f };

	// 적위치 - 내위치
	float4 EnemyPos = AggroUnit->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	MoveDir = TargetPos - MyPos;

	MoveDir.Normalize();

	if (Dir == GameUnitDir::Right)
	{
	//	TargetPos.X
	}
}

void GameUnit::SearchMoveUpdate(float _Delta)
{
	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	Transform.AddLocalPosition((MoveDir * 100.0f * _Delta));
}


void GameUnit::MaxStart()
{

}

void GameUnit::MaxUpdate(float _Delta)
{

}