#include "PreCompile.h"
#include "UI_Button.h"


UI_Button::UI_Button()
{

}

UI_Button::~UI_Button()
{

}


void UI_Button::Start()
{
	// ȭ�� ���߱� �������.
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });

	ButtonCol = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
	ButtonCol->SetCollisionType(ColType::AABBBOX2D);
	ButtonCol->Transform.SetLocalScale(ButtonColScale);

	// �ݸ����� �������� �ʰ� �ϱ�����.
	ButtonCol->Transform.AddLocalPosition({0.0f, 0.0f, -30.0f});

	ChangeState(UI_ButtonState::Idle);

	GameEngineInput::AddInputObject(this);

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

void UI_Button::LevelStart(GameEngineLevel* _PrevLevel)
{
	
}

void UI_Button::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void UI_Button::Update(float _Delta)
{
	//�̺�Ʈ ���.
	ButtonCol->CollisionEvent(CollisionOrder::Mouse, ColEvent);
	StateUpdate(_Delta);
}


void UI_Button::StateUpdate(float _Delta)
{
	switch (State)
	{
	case UI_ButtonState::Idle:
		return IdleUpdate(_Delta);
	case UI_ButtonState::Stay:
		return StayUpdate(_Delta);
	case UI_ButtonState::Click:
		return ClickUpdate(_Delta);
	case UI_ButtonState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void UI_Button::ChangeState(UI_ButtonState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case UI_ButtonState::Idle:
			IdleStart();
			break;
		case UI_ButtonState::Stay:
			StayStart();
			break;
		case UI_ButtonState::Click:
			ClickStart();
			break;
		case UI_ButtonState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void UI_Button::MaxStart()
{

}

void UI_Button::MaxUpdate(float _Delta)
{

}

void UI_Button::IdleStart()
{

}

void UI_Button::IdleUpdate(float _Delta)
{

}

void UI_Button::StayStart()
{

}

void UI_Button::StayUpdate(float _Delta)
{

}

void UI_Button::ClickStart()
{

}

void UI_Button::ClickUpdate(float _Delta)
{

}