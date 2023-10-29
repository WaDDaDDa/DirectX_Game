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
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });

	TextBoxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	//TextBoxRenderer->SetSprite("equipment_slot_bg_0.png");

	PrintText = GameEngineString::UnicodeToAnsi(CurText);

	TextBoxRenderer->SetText("Galmuri14", PrintText, 40.0f, float4::WHITE, FW1_LEFT);
	TextBoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	TextBoxRenderer->Transform.AddLocalPosition({ -600.0f, 50.0f });

	// 텍스트 출력 위치.
	TextBoxRenderer->SetImageScale(TextBoxScale);
	TextBoxRenderer->Transform.AddLocalPosition(TextBoxPos);
	// MainSpriteRenderer->SetPivotType(PivotType::Bottom);

	ChangeState(IntroCutState::CutScene1);

	GameEngineInput::AddInputObject(this);
}

void IntroCut::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void IntroCut::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void IntroCut::Update(float _Delta)
{
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
	case IntroCutState::NewGame:
		return NewGameUpdate(_Delta);
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
		case IntroCutState::NewGame:
			NewGameStart();
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
	MainSpriteRenderer->SetImageScale(WindowScale);

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
	SceneTime += _Delta;

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (CurText.size() > Scene1Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(IntroCutState::Black);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene1Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 40.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene1Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 40.0f, float4::WHITE, FW1_LEFT);
	}

}

void IntroCut::CutScene2Start()
{
	MainSpriteRenderer->SetSprite("cutscene2.png");
	Arrow = GetLevel()->CreateActor<TextArrow>();
}

void IntroCut::CutScene2Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE, this))
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
	if (GameEngineInput::IsDown(VK_SPACE, this))
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
	if (GameEngineInput::IsDown(VK_SPACE, this))
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
	if (GameEngineInput::IsDown(VK_SPACE, this))
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
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		// 임시 - 마지막 씬이므로 Team UI 생성.
		//ChangeState(IntroCutState::Black);

		if (nullptr != Arrow)
		{
			Arrow->Death();
			Arrow = nullptr;
		}

		ChangeState(IntroCutState::NewGame);
		return;
	}
}


void IntroCut::NewGameStart()
{
	if (nullptr != Arrow)
	{
		Arrow->Death();
		Arrow = nullptr;
	}

	// 페이드 효과
	MainSpriteRenderer->GetColorData().MulColor.W -= 0.8f;

	GetLevel()->CreateActor<NewGame_UI>();
}

void IntroCut::NewGameUpdate(float _Delta)
{

}

void IntroCut::MaxStart()
{

}

void IntroCut::MaxUpdate(float _Delta)
{

}