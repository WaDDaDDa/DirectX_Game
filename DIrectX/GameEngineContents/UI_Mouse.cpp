#include "PreCompile.h"
#include "UI_Mouse.h"


UI_Mouse::UI_Mouse()
{

}

UI_Mouse::~UI_Mouse()
{

}


void UI_Mouse::Start()
{
	MouseCol = CreateComponent<GameEngineCollision>(CollisionOrder::Mouse);
	MouseCol->Transform.SetLocalScale(MouseColScale);

	ChangeState(UI_MouseState::Idle);

	// �̺�Ʈ ����
	ColEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// ó���ѹ� ����.
		};

	ColEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// Ŀ�� �ö��ִ� �� ����.
		};

	ColEvent.Exit = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
		{
			// Ŀ�� �ö��ִٰ� ���������� ����.
		};
}

void UI_Mouse::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void UI_Mouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void UI_Mouse::Update(float _Delta)
{
	//�̺�Ʈ ���.
	Transform.SetWorldPosition(GetLevel()->GetMainCamera()->GetWorldMousePos2D());
	StateUpdate(_Delta);
}


void UI_Mouse::StateUpdate(float _Delta)
{
	switch (State)
	{
	case UI_MouseState::Idle:
		return IdleUpdate(_Delta);
	case UI_MouseState::Stay:
		return StayUpdate(_Delta);
	case UI_MouseState::Click:
		return ClickUpdate(_Delta);
	case UI_MouseState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void UI_Mouse::ChangeState(UI_MouseState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case UI_MouseState::Idle:
			IdleStart();
			break;
		case UI_MouseState::Stay:
			StayStart();
			break;
		case UI_MouseState::Click:
			ClickStart();
			break;
		case UI_MouseState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void UI_Mouse::MaxStart()
{

}

void UI_Mouse::MaxUpdate(float _Delta)
{

}

void UI_Mouse::IdleStart()
{

}

void UI_Mouse::IdleUpdate(float _Delta)
{

}

void UI_Mouse::StayStart()
{

}

void UI_Mouse::StayUpdate(float _Delta)
{

}

void UI_Mouse::ClickStart()
{

}

void UI_Mouse::ClickUpdate(float _Delta)
{

}