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
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("Knight", "Knight");
		MainSpriteRenderer->ChangeAnimation("Knight");
		MainSpriteRenderer->AutoSpriteSizeOn();
	}
}

void GameUnit::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}


void GameUnit::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GameUnitState::Idle:
		break;
	case GameUnitState::Move:
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
		break;
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
			break;
		case GameUnitState::Move:
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
			break;
		default:
			break;
		}
	}
	// 스프라이트 셋팅이 바뀔때 마다 Transform의 로컬스케일이 변하므로 
	// 변할때마다 스케일 세팅을 다시한다.
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	MainSpriteRenderer->Transform.SetLocalScale(WindowScale);

	ResetLiveTime();

	State = _State;
}
