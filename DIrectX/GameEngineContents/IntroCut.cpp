#include "PreCompile.h"

#include "IntroCut.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "NewGame_UI.h"
#include "TextArrow.h"

IntroCut::IntroCut()
{

}

IntroCut::~IntroCut()
{

}

void IntroCut::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	TextBoxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);

	TextBoxRenderer->SetSprite("equipment_slot_bg_0.png");

	// 텍스트 출력 위치.
	TextBoxRenderer->Transform.SetLocalScale(TextBoxScale);
	TextBoxRenderer->Transform.AddLocalPosition(TextBoxPos);

	ChangeState(IntroCutState::CutScene1);
}


void IntroCut::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
		return;
	}

	StateUpdate(_Delta);
}


void IntroCut::StateUpdate(float _Delta)
{
	switch (State)
	{
	case IntroCutState::Black:
		return BlackUpdate(_Delta);
	case IntroCutState::CutScene1:
		return CutScene1Update(_Delta);
	case IntroCutState::CutScene2:
		return CutScene2Update(_Delta);
	case IntroCutState::CutScene3:
		return CutScene3Update(_Delta);
	case IntroCutState::CutScene4:
		return CutScene4Update(_Delta);
	case IntroCutState::CutScene5:
		return CutScene5Update(_Delta);
	case IntroCutState::CutScene6:
		return CutScene6Update(_Delta);
	case IntroCutState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void IntroCut::ChangeState(IntroCutState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case IntroCutState::Black:
			BlackStart();
			break;
		case IntroCutState::CutScene1:
			CutScene1Start();
			break;
		case IntroCutState::CutScene2:
			CutScene2Start();
			break;
		case IntroCutState::CutScene3:
			CutScene3Start();
			break;
		case IntroCutState::CutScene4:
			CutScene4Start();
			break;
		case IntroCutState::CutScene5:
			CutScene5Start();
			break;
		case IntroCutState::CutScene6:
			CutScene6Start();
			break;
		case IntroCutState::Max:
			MaxStart();
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

void IntroCut::BlackStart()
{
	if (nullptr != Arrow)
	{
		Arrow->Death();
		Arrow = nullptr;
	}

	MainSpriteRenderer->SetSprite("Black_0.png");
	Scene += 1;
}

void IntroCut::BlackUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.2f)
	{
		if (Scene == 6)
		{
			Scene = 0;
		}

		ChangeState(Scene);
		return;
	}
}

void IntroCut::CutScene1Start()
{
	MainSpriteRenderer->SetSprite("cutscene1.png");
	Arrow = GetLevel()->CreateActor<TextArrow>();
}

void IntroCut::CutScene1Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(IntroCutState::Black);
		return;
	}
}

void IntroCut::CutScene2Start()
{
	MainSpriteRenderer->SetSprite("cutscene2.png");
	Arrow = GetLevel()->CreateActor<TextArrow>();

}

void IntroCut::CutScene2Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(IntroCutState::Black);
		return;
	}
}

void IntroCut::CutScene3Start()
{
	MainSpriteRenderer->SetSprite("cutscene3.png");

	Arrow = GetLevel()->CreateActor<TextArrow>();
}

void IntroCut::CutScene3Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(IntroCutState::Black);
		return;
	}
}

void IntroCut::CutScene4Start()
{
	MainSpriteRenderer->SetSprite("cutscene4.png");

	Arrow = GetLevel()->CreateActor<TextArrow>();
}

void IntroCut::CutScene4Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(IntroCutState::Black);
		return;
	}
}

void IntroCut::CutScene5Start()
{
	MainSpriteRenderer->SetSprite("cutscene5.png");
	Arrow = GetLevel()->CreateActor<TextArrow>();

}

void IntroCut::CutScene5Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(IntroCutState::Black);
		return;
	}
}

void IntroCut::CutScene6Start()
{
	MainSpriteRenderer->SetSprite("cutscene6.png");
	Arrow = GetLevel()->CreateActor<TextArrow>();
}

void IntroCut::CutScene6Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		// 임시 - 마지막 씬이므로 Team UI 생성.
		//ChangeState(IntroCutState::Black);

		if (nullptr != Arrow)
		{
			Arrow->Death();
			Arrow = nullptr;
		}

		GetLevel()->CreateActor<NewGame_UI>();
		return;
	}
}

void IntroCut::MaxStart()
{

}

void IntroCut::MaxUpdate(float _Delta)
{

}