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

}

void GameUnit::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameUnit::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameUnit::Update(float _Delta)
{
	StateUpdate(_Delta);

	//float Speed = 100.0f;

	//float4 WPos = Transform.GetWorldPosition();
	//if (GameEngineInput::IsPress('A'))
	//{
	//	Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('D'))
	//{
	//	Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('W'))
	//{
	//	Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('S'))
	//{
	//	Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('Q'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	//}

	//if (GameEngineInput::IsPress('E'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	//}
}


void GameUnit::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GameUnitState::Idle:
		return IdleUpdate(_Delta);
	case GameUnitState::Move:
		return MoveUpdate(_Delta);
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
		case GameUnitState::Idle:
			IdleStart();
			break;
		case GameUnitState::Move:
			MoveStart();
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

void GameUnit::IdleStart()
{

}

void GameUnit::IdleUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		//ChangeState(GameUnitState::Move);
		return;
	}
}

void GameUnit::MoveStart()
{

}

void GameUnit::MoveUpdate(float _Delta)
{
	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(GameUnitState::Idle);
		return;
	}

	// 적위치 - 내위치
	float4 EnemyPos = EnemyUnit1->Transform.GetWorldPosition();
	float4 MyPos = Transform.GetWorldPosition();

	float4 MoveDir = EnemyPos - MyPos;
	MoveDir.Normalize();

	Transform.AddLocalPosition((MoveDir * 10.0f * _Delta));
}


void GameUnit::MaxStart()
{

}

void GameUnit::MaxUpdate(float _Delta)
{

}