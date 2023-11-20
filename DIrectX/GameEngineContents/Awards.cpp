#include "PreCompile.h"

#include "Awards.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "NewGame_UI.h"
#include "TextArrow.h"
#include "TeamInfo.h"
#include "EnemyInfo.h"

Awards::Awards()
{

}

Awards::~Awards()
{

}

void Awards::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::BackGround);
	MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackGround) });
	MainSpriteRenderer->SetSprite("Awards", 0);

	// 프레임펑션
	CoachFrameFunction = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			CoachHairCheck(CurSprite);
			return;
		};
	FrameFunction = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			HairCheck(CurSprite);
			return;
		};
	FrameFunction2 = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			HairCheck2(CurSprite);
			return;
		};
	FrameFunction3 = [=](const SpriteData& CurSprite, int _SpriteIndex)
		{
			// 처음한번 실행.
			HairCheck3(CurSprite);
			return;
		};

	PrintText = GameEngineString::UnicodeToAnsi(CurText);

	TextBoxBg = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	TextBoxBg->SetSprite("Awards", 4);
	TextBoxBg->SetImageScale({1260.0f, 150.0f});
	TextBoxBg->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	TextBoxBg->Transform.AddLocalPosition({ 0.0f, -270.0f });
	TextBoxBg->Off();

	TextBoxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Text);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	TextBoxRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Text) });
	TextBoxRenderer->Transform.AddLocalPosition({ -600.0f, 50.0f });

	ModeratorRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	ModeratorRenderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	ModeratorRenderer->Transform.AddLocalPosition({ -280.0f, -210.0f });
	ModeratorRenderer->SetPivotType(PivotType::Bottom);
	ModeratorRenderer->AutoSpriteSizeOn();
	ModeratorRenderer->SetAutoScaleRatio(8.0f);

	ModeratorRenderer->CreateAnimation("Idle", "Moderator", 0.1f, 13, 15);
	ModeratorRenderer->CreateAnimation("Open", "Moderator", 0.1f, 16, 18, false);
	ModeratorRenderer->CreateAnimation("Clap", "Moderator", 0.1f, 19, 20);
	ModeratorRenderer->ChangeAnimation("Idle");

	std::list<std::shared_ptr<class GamePlayer>>& PlayerGroup = TeamInfo::MyInfo.GetMyPlayer();

	std::list<std::shared_ptr<GamePlayer>>::iterator Start = PlayerGroup.begin();
	std::list<std::shared_ptr<GamePlayer>>::iterator End = PlayerGroup.end();

	CoachHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	CoachHair->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

	CoachBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	CoachBody->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	CoachBody->SetPivotType(PivotType::Bottom);
	CoachBody->Transform.AddLocalPosition({ -20.0f, -200.0f });

	CoachBody->CreateAnimation("Idle", "Character_Coach", 0.1f, 0, 3);
	CoachBody->CreateAnimation("Win", "Character_Coach", 0.1f, 34, 38);
	CoachBody->AutoSpriteSizeOn();
	CoachBody->SetAutoScaleRatio(7.0f);
	CoachBody->SetFrameChangeFunctionAll(CoachFrameFunction);
	CoachBody->ChangeAnimation("Idle");

	CoachHair->SetSprite("Coach_Hair", TeamInfo::MyInfo.GetHairNum());
	CoachHair->AutoSpriteSizeOn();
	CoachHair->SetAutoScaleRatio(7.0f);
	CoachHair->Transform.AddLocalPosition({ 0.0f, 0.0f });

	WinnerUnitHair = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitHair->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

	WinnerUnitBody = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitBody->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	WinnerUnitBody->SetPivotType(PivotType::Bottom);
	WinnerUnitBody->Transform.AddLocalPosition({ -100.0f, -200.0f });

	WinnerUnitBody->CreateAnimation("Idle", "Character_Coach", 0.1f, 0, 3);
	WinnerUnitBody->CreateAnimation("Win", "Character_Coach", 0.1f, 34, 38);
	WinnerUnitBody->AutoSpriteSizeOn();
	WinnerUnitBody->SetAutoScaleRatio(7.0f);
	WinnerUnitBody->SetFrameChangeFunctionAll(FrameFunction);
	WinnerUnitBody->ChangeAnimation("Idle");

	WinnerUnitHair->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
	WinnerUnitHair->AutoSpriteSizeOn();
	WinnerUnitHair->SetAutoScaleRatio(7.0f);
	WinnerUnitHair->Transform.AddLocalPosition({ 0.0f, 0.0f });
	Start++;

	WinnerUnitHair2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitHair2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

	WinnerUnitBody2 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitBody2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	WinnerUnitBody2->SetPivotType(PivotType::Bottom);
	WinnerUnitBody2->Transform.AddLocalPosition({ 50.0f, -200.0f });

	WinnerUnitBody2->CreateAnimation("Idle", "Character_Coach", 0.1f, 0, 3);
	WinnerUnitBody2->CreateAnimation("Win", "Character_Coach", 0.1f, 34, 38);
	WinnerUnitBody2->AutoSpriteSizeOn();
	WinnerUnitBody2->SetAutoScaleRatio(7.0f);
	WinnerUnitBody2->SetFrameChangeFunctionAll(FrameFunction2);
	WinnerUnitBody2->ChangeAnimation("Idle");

	WinnerUnitHair2->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
	WinnerUnitHair2->AutoSpriteSizeOn();
	WinnerUnitHair2->SetAutoScaleRatio(7.0f);
	WinnerUnitHair2->Transform.AddLocalPosition({ 0.0f, 0.0f });
	Start++;

	WinnerUnitHair3 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitHair3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });

	WinnerUnitBody3 = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::Unit);
	WinnerUnitBody3->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::Unit) });
	WinnerUnitBody3->SetPivotType(PivotType::Bottom);
	WinnerUnitBody3->Transform.AddLocalPosition({ 100.0f, -200.0f });

	WinnerUnitBody3->CreateAnimation("Idle", "Character_Coach", 0.1f, 0, 3);
	WinnerUnitBody3->CreateAnimation("Win", "Character_Coach", 0.1f, 34, 38);
	WinnerUnitBody3->AutoSpriteSizeOn();
	WinnerUnitBody3->SetAutoScaleRatio(7.0f);
	WinnerUnitBody3->SetFrameChangeFunctionAll(FrameFunction3);
	WinnerUnitBody3->ChangeAnimation("Idle");

	WinnerUnitHair3->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
	WinnerUnitHair3->AutoSpriteSizeOn();
	WinnerUnitHair3->SetAutoScaleRatio(7.0f);
	WinnerUnitHair3->Transform.AddLocalPosition({ 0.0f, 0.0f });

	UnitOff();

	LightRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::FrontEffect);
	LightRenderer->Transform.AddLocalPosition({ 0.0f, 135.0f, -static_cast<float>(ContentsOrder::FrontEffect) });
	LightRenderer->SetSprite("Awards", 1);
	LightRenderer->AutoSpriteSizeOn();
	LightRenderer->SetAutoScaleRatio(8.0f);	
	LightRenderer->GetColorData().MulColor.W -= 0.5f;
	LightRenderer->Off();

	LeftCurtain = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	LeftCurtain->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	LeftCurtain->SetSprite("Awards", 2);
	LeftCurtain->AutoSpriteSizeOn();
	LeftCurtain->SetAutoScaleRatio(9.0f);
	LeftCurtain->Transform.AddLocalPosition({ -355.0f, 50.0f });

	RightCurtain = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	RightCurtain->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UIImage) });
	RightCurtain->SetSprite("Awards", 3);
	RightCurtain->AutoSpriteSizeOn();
	RightCurtain->SetAutoScaleRatio(9.0f);
	RightCurtain->Transform.AddLocalPosition({ 355.0f, 50.0f });

	WinnerLogo = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UI);
	WinnerLogo->AutoSpriteSizeOn();
	WinnerLogo->SetAutoScaleRatio(2.0f);
	WinnerLogo->Transform.AddLocalPosition({ 0.0f, 230.0f, -static_cast<float>(ContentsOrder::UI) });
	WinnerLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
	WinnerLogo->Off();

	WinnerName = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	WinnerName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
	WinnerName->Transform.AddLocalPosition({ 0.0f, 200.0f, -static_cast<float>(ContentsOrder::UIImage) });
	WinnerName->Off();

	WinnerText = CreateComponent<GameEngineSpriteRenderer>(ContentsOrder::UIImage);
	WinnerText->SetText("Galmuri14", "", 32.0f, float4::WHITE, FW1_CENTER);
	WinnerText->Transform.AddLocalPosition({ 0.0f, 300.0f, -static_cast<float>(ContentsOrder::UIImage) });
	WinnerText->Off();

	// 텍스트 출력 위치.
	TextBoxRenderer->Transform.AddLocalPosition(TextBoxPos);

	ChangeState(AwardsState::CurtainOpen);

	GameEngineInput::AddInputObject(this);
}

void Awards::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void Awards::UnitOff()
{
	CoachBody->Off();
	CoachHair->Off();
	WinnerUnitBody->Off();
	WinnerUnitHair->Off();
	WinnerUnitBody2->Off();
	WinnerUnitHair2->Off();
	WinnerUnitBody3->Off();
	WinnerUnitHair3->Off();
}

void Awards::UnitOn()
{
	CoachBody->On();
	CoachHair->On();
	WinnerUnitBody->On();
	WinnerUnitHair->On();
	WinnerUnitBody2->On();
	WinnerUnitHair2->On();
	WinnerUnitBody3->On();
	WinnerUnitHair3->On();
}

void Awards::UnitBlack()
{
	CoachBody->GetColorData().PlusColor -= float4::ONENULL;
	CoachHair->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitBody->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitHair->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitBody2->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitHair2->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitBody3->GetColorData().PlusColor -= float4::ONENULL;
	WinnerUnitHair3->GetColorData().PlusColor -= float4::ONENULL;
}

void Awards::UnitWhite()
{
	CoachBody->GetColorData().PlusColor += float4::ONENULL;
	CoachHair->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitBody->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitHair->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitBody2->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitHair2->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitBody3->GetColorData().PlusColor += float4::ONENULL;
	WinnerUnitHair3->GetColorData().PlusColor += float4::ONENULL;
}

void Awards::UnitIdle()
{
	CoachBody->ChangeAnimation("Idle");
	WinnerUnitBody->ChangeAnimation("Idle");
	WinnerUnitBody2->ChangeAnimation("Idle");
	WinnerUnitBody3->ChangeAnimation("Idle");
}

void Awards::UnitWin()
{
	CoachBody->ChangeAnimation("Win");
	WinnerUnitBody->ChangeAnimation("Win");
	WinnerUnitBody2->ChangeAnimation("Win");
	WinnerUnitBody3->ChangeAnimation("Win");
}

void Awards::PlayerWinUnit()
{
	std::list<std::shared_ptr<class GamePlayer>>& PlayerGroup = TeamInfo::MyInfo.GetMyPlayer();

	std::list<std::shared_ptr<GamePlayer>>::iterator Start = PlayerGroup.begin();
	std::list<std::shared_ptr<GamePlayer>>::iterator End = PlayerGroup.end();

	CoachHair->SetSprite("Coach_Hair", TeamInfo::MyInfo.GetHairNum());

	WinnerUnitHair->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
	Start++;

	WinnerUnitHair2->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
	Start++;

	WinnerUnitHair3->SetSprite("Coach_Hair", (*Start)->GetSpec().HairNum);
}

void Awards::PlayerLoseUnit()
{
	CoachHair->SetSprite("Coach_Hair", 0);

	WinnerUnitHair->SetSprite("Coach_Hair", EnemyInfo::Info.GetOnePlayer().HairNum);

	WinnerUnitHair2->SetSprite("Coach_Hair", EnemyInfo::Info.GetTwoPlayer().HairNum);

	WinnerUnitHair3->SetSprite("Coach_Hair", EnemyInfo::Info.GetThreePlayer().HairNum);
}

void Awards::HairCheck(const SpriteData& _CurSprite)
{
	// 헤어위치 잡는 작업.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (62.0f - ColorCheckPos.Y) * 7.0f;
	WinnerUnitHair->Transform.SetLocalPosition({ WinnerUnitBody->Transform.GetLocalPosition().X, WinnerUnitBody->Transform.GetLocalPosition().Y + ResultY, WinnerUnitHair->Transform.GetLocalPosition().Z});
}

void Awards::HairCheck2(const SpriteData& _CurSprite)
{
	// 헤어위치 잡는 작업.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (62.0f - ColorCheckPos.Y) * 7.0f;
	WinnerUnitHair2->Transform.SetLocalPosition({ WinnerUnitBody2->Transform.GetLocalPosition().X, WinnerUnitBody2->Transform.GetLocalPosition().Y + ResultY, WinnerUnitHair2->Transform.GetLocalPosition().Z });
}

void Awards::HairCheck3(const SpriteData& _CurSprite)
{
	// 헤어위치 잡는 작업.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (62.0f - ColorCheckPos.Y) * 7.0f;
	WinnerUnitHair3->Transform.SetLocalPosition({ WinnerUnitBody3->Transform.GetLocalPosition().X, WinnerUnitBody3->Transform.GetLocalPosition().Y + ResultY, WinnerUnitHair3->Transform.GetLocalPosition().Z });
}

void Awards::CoachHairCheck(const SpriteData& _CurSprite)
{
	// 헤어위치 잡는 작업.
	GameEngineColor CurColor = GameEngineColor::RED;
	float4 ColorCheckPos = CheckPos;

	while (GameEngineColor::BLACK != CurColor)
	{

		CurColor = _CurSprite.Texture->GetColor(ColorCheckPos, GameEngineColor::RED);
		ColorCheckPos.Y += 1.0f;
	}

	float ResultY = (62.0f - ColorCheckPos.Y) * 7.0f;
	CoachHair->Transform.SetLocalPosition({ CoachBody->Transform.GetLocalPosition().X, CoachBody->Transform.GetLocalPosition().Y + ResultY, CoachHair->Transform.GetLocalPosition().Z });
}

void Awards::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Awards::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Awards::StateUpdate(float _Delta)
{
	switch (State)
	{
	case AwardsState::CurtainOpen:
		return CurtainOpenUpdate(_Delta);
	case AwardsState::CutScene1:
		return CutScene1Update(_Delta);
	case AwardsState::CutScene2:
		return CutScene2Update(_Delta);
	case AwardsState::CutScene3:
		return CutScene3Update(_Delta);
	case AwardsState::CutScene4:
		return CutScene4Update(_Delta);
	case AwardsState::CutScene5:
		return CutScene5Update(_Delta);
	case AwardsState::CutScene6:
		return CutScene6Update(_Delta);
	case AwardsState::CutScene7:
		return CutScene7Update(_Delta);
	case AwardsState::CutScene8:
		return CutScene8Update(_Delta);
	case AwardsState::CurtainClose:
		return CurtainCloseUpdate(_Delta);
	case AwardsState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Awards::ChangeState(AwardsState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case AwardsState::CurtainOpen:
			CurtainOpenStart();
			break;
		case AwardsState::CutScene1:
			CutScene1Start();
			break;
		case AwardsState::CutScene2:
			CutScene2Start();
			break;
		case AwardsState::CutScene3:
			CutScene3Start();
			break;
		case AwardsState::CutScene4:
			CutScene4Start();
			break;
		case AwardsState::CutScene5:
			CutScene5Start();
			break;
		case AwardsState::CutScene6:
			CutScene6Start();
			break;
		case AwardsState::CutScene7:
			CutScene7Start();
			break;
		case AwardsState::CutScene8:
			CutScene8Start();
			break;
		case AwardsState::CurtainClose :
			CurtainCloseStart();
			break;
		case AwardsState::Max:
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

void Awards::CurtainOpenStart()
{
	TextSkip = false;
	CurtainValue = 0.0f;
}

void Awards::CurtainOpenUpdate(float _Delta)
{
	if (true == TextSkip)
	{
		CurtainValue += _Delta;
		if (CurtainValue >= 1.0f)
		{
			CurtainValue = 1.0f;
		}

		float XPos = std::lerp(355.0f, 1000.0f, CurtainValue);
		float YPos = LeftCurtain->Transform.GetLocalPosition().Y;
		float ZPos = LeftCurtain->Transform.GetLocalPosition().Z;
		LeftCurtain->Transform.SetLocalPosition({ -XPos , YPos , ZPos });
		RightCurtain->Transform.SetLocalPosition({ XPos , YPos , ZPos });

		if (GameEngineInput::IsDown(VK_SPACE, this) && 1000.0f == XPos)
		{
			ChangeState(AwardsState::CutScene1);
			return;
		}

	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}
}

void Awards::CutScene1Start()
{
	TextSkip = false;
	TextBoxBg->On();
}

void Awards::CutScene1Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene1Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene2);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene1Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene1Text[CurTextNum]);
		CurTextNum++;

		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}

}

void Awards::CutScene2Start()
{
	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}
	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);

}

void Awards::CutScene2Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene2Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene3);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene2Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene2Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

void Awards::CutScene3Start()
{
	UnitOn();
	UnitBlack();

	if (true == TeamInfo::MyInfo.Win)
	{
		PlayerWinUnit();
	}
	else if (false == TeamInfo::MyInfo.Win)
	{
		PlayerLoseUnit();
	}

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}
	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
}

void Awards::CutScene3Update(float _Delta)
{
	SceneTime += _Delta;

	ModeratorRenderer->ChangeAnimation("Open");

	if (CurText.size() > Scene3Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene4);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene3Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene3Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

// 스포트라이트 밝혀지는 순간
void Awards::CutScene4Start()
{
	UnitWhite();

	ModeratorRenderer->ChangeAnimation("Clap");

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}

	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);

	Scene4Text += Scene3Text;

	WinnerText->SetText("Galmuri14", "아마추어 리그 우승 팀", 32.0f, float4::WHITE, FW1_CENTER);
	WinnerText->On();

	if (true == TeamInfo::MyInfo.Win)
	{
		Scene4Text += GameEngineString::AnsiToUnicode(TeamInfo::MyInfo.GetTeamName());

		WinnerLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
		WinnerLogo->On();
		WinnerName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
		WinnerName->On();
	}
	else if (false == TeamInfo::MyInfo.Win)
	{
		Scene4Text += GameEngineString::AnsiToUnicode(EnemyInfo::Info.GetTeamName());

		WinnerLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
		WinnerLogo->On();
		WinnerName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
		WinnerName->On();
	}

	Scene4Text += Scene3_1Text;

	LightRenderer->On();

	UnitWin();
}

void Awards::CutScene4Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene4Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene5);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene4Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene4Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}
// 준우승 수상
void Awards::CutScene5Start()
{
	ModeratorRenderer->ChangeAnimation("Idle");

	UnitIdle();
	UnitOff();
	WinnerText->Off();
	WinnerLogo->Off();
	WinnerName->Off();

	LightRenderer->Off();

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}
	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
}

void Awards::CutScene5Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene5Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene6);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene5Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene5Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

// 준우승팀은... 검은 스포트라이트 전
void Awards::CutScene6Start()
{
	ModeratorRenderer->ChangeAnimation("Open");

	UnitOn();
	UnitBlack();

	if (false == TeamInfo::MyInfo.Win)
	{
		PlayerWinUnit();
	}
	else if (true == TeamInfo::MyInfo.Win)
	{
		PlayerLoseUnit();
	}

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;

	if (true != CurText.empty())
	{
		CurText.clear();
	}
	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
}

void Awards::CutScene6Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene6Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene7);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene6Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene6Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

// 스포트라이트
void Awards::CutScene7Start()
{
	ModeratorRenderer->ChangeAnimation("Clap");

	UnitWhite();

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}

	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);

	Scene7Text += Scene6Text;

	WinnerText->SetText("Galmuri14", "아마추어 리그 준우승 팀", 32.0f, float4::WHITE, FW1_CENTER);
	WinnerText->On();

	if (false == TeamInfo::MyInfo.Win)
	{
		Scene7Text += GameEngineString::AnsiToUnicode(TeamInfo::MyInfo.GetTeamName());

		WinnerLogo->SetSprite("TeamLogo", static_cast<unsigned int>(TeamInfo::MyInfo.GetIconNum()));
		WinnerLogo->On();
		WinnerName->SetText("Galmuri14", TeamInfo::MyInfo.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
		WinnerName->On();
	}
	else if (true == TeamInfo::MyInfo.Win)
	{
		Scene7Text += GameEngineString::AnsiToUnicode(EnemyInfo::Info.GetTeamName());

		WinnerLogo->SetSprite("TeamLogo", static_cast<unsigned int>(EnemyInfo::Info.GetIconNum()));
		WinnerLogo->On();
		WinnerName->SetText("Galmuri14", EnemyInfo::Info.GetTeamName(), 32.0f, float4::WHITE, FW1_CENTER);
		WinnerName->On();
	}

	Scene7Text += Scene6_1Text;

	LightRenderer->On();

	UnitWin();
}

void Awards::CutScene7Update(float _Delta)
{

	SceneTime += _Delta;

	if (CurText.size() > Scene7Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CutScene8);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene7Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene7Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

void Awards::CutScene8Start()
{
	ModeratorRenderer->ChangeAnimation("Idle");


	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}

	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);

	LightRenderer->Off();
	UnitOff();
	WinnerText->Off();
	WinnerLogo->Off();
	WinnerName->Off();
}


void Awards::CutScene8Update(float _Delta)
{
	SceneTime += _Delta;

	if (CurText.size() > Scene8Text.size() || true == TextSkip)
	{
		if (GameEngineInput::IsDown(VK_SPACE, this))
		{
			ChangeState(AwardsState::CurtainClose);
			return;
		}
		PrintText = GameEngineString::UnicodeToAnsi(Scene8Text);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}

	if (0.01f <= SceneTime)
	{
		SceneTime = 0.0f;

		CurText.push_back(Scene8Text[CurTextNum]);
		CurTextNum++;


		PrintText = GameEngineString::UnicodeToAnsi(CurText);

		TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
	}
}

void Awards::CurtainCloseStart()
{
	CurtainValue = 0.0f;
	TextBoxBg->Off();

	// 텍스트 초기화
	TextSkip = false;
	CurTextNum = 0;
	if (true != CurText.empty())
	{
		CurText.clear();
	}

	PrintText = GameEngineString::UnicodeToAnsi(CurText);
	TextBoxRenderer->SetText("Galmuri14", PrintText, 32.0f, float4::WHITE, FW1_LEFT);
}

void Awards::CurtainCloseUpdate(float _Delta)
{
	if (true == TextSkip)
	{
		CurtainValue += _Delta;
		if (CurtainValue >= 1.0f)
		{
			CurtainValue = 1.0f;
		}

		float XPos = std::lerp(1000.0f, 355.0f, CurtainValue);
		float YPos = LeftCurtain->Transform.GetLocalPosition().Y;
		float ZPos = LeftCurtain->Transform.GetLocalPosition().Z;
		LeftCurtain->Transform.SetLocalPosition({ -XPos , YPos , ZPos });
		RightCurtain->Transform.SetLocalPosition({ XPos , YPos , ZPos });

		if (GameEngineInput::IsDown(VK_SPACE, this) && 355.0f == XPos)
		{
			//레벨 체인지.
			//ChangeState(AwardsState::CutScene1);
			return;
		}

	}

	if (GameEngineInput::IsDown(VK_SPACE, this) && false == TextSkip)
	{
		TextSkip = true;
		return;
	}
}

void Awards::MaxStart()
{

}

void Awards::MaxUpdate(float _Delta)
{

}