#include "PreCompile.h"
#include "BanPickCard.h"
#include "GameUnitStatus.h"
#include "UI_Mouse.h"

float BanPickCard::XInter = 0.0f;


BanPickCard::BanPickCard()
{

}

BanPickCard::~BanPickCard()
{

}

void BanPickCard::Start()
{
	UI_Button::Start();

	{
		// 싱글 스프라이트 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Stadium\\Unit_Icon");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		// 초상화 로드
		GameEngineSprite::CreateSingle("Archer_Icon.png");
		GameEngineSprite::CreateSingle("Knight_Icon.png");
		GameEngineSprite::CreateSingle("Monk_Icon.png");
		GameEngineSprite::CreateSingle("Fighter_Icon.png");
		GameEngineSprite::CreateSingle("Ninja_Icon.png");
		GameEngineSprite::CreateSingle("Priest_Icon.png");
		GameEngineSprite::CreateSingle("Pyromancer_Icon.png");
		GameEngineSprite::CreateSingle("Pythoness_Icon.png");
		GameEngineSprite::CreateSingle("Swordman_Icon.png");
	}

	// Card 배경
	Renderer = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UI);
	Renderer->CreateAnimation("BanPickCard_Null", "BanPick", 0.1f, 15, 15, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::UI) });
	Renderer->ChangeAnimation("BanPickCard_Null");

	// Card 테두리
	Renderer2 = CreateComponent<GameEngineUIRenderer>(ContentsOrder::BackUI);
	Renderer2->CreateAnimation("BanPickCard_Blue", "BanPick", 0.1f, 19, 19, false);
	Renderer2->CreateAnimation("BanPickCard_Red", "BanPick", 0.1f, 20, 20, false);
	Renderer2->AutoSpriteSizeOn();
	Renderer2->SetAutoScaleRatio(2.0f);
	Renderer2->Transform.AddLocalPosition({ 0.0f, 0.0f, -static_cast<float>(ContentsOrder::BackUI) });
	Renderer2->ChangeAnimation("BanPickCard_Blue");
	Renderer2->Off();

	SetButtonColScale(ColScale);

	Transform.AddLocalPosition(StartPos);

	// 이벤트 셋팅
	//ColEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
	//	{
	//		// 처음한번 실행.
	//		if (false == IsSelect)
	//		{
	//			UnitImage->ChangeAnimation(GetUnitName() += "_Stay");
	//		}
	//	};

	//ColEvent.Stay = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
	//	{
	//		// 커서 올라가있는 중 실행.
	//		if (GameEngineInput::IsDown(VK_LBUTTON, this))
	//		{
	//			UnitImage->ChangeAnimation(GetUnitName() += "_Att");
	//			IsSelect = true;
	//		}
	//	};

	//ColEvent.Exit = [=](GameEngineCollision* _this, GameEngineCollision* _Col)
	//	{
	//		// 커서 올라가있다가 떨어졌을때 실행.
	//		if (false == IsSelect)
	//		{
	//			UnitImage->ChangeAnimation(GetUnitName() += "_Idle");
	//		}

	//	};
}

void BanPickCard::LevelStart(GameEngineLevel* _PrevLevel)
{
	XInter = 0.0f;
}

void BanPickCard::Init()
{
	UnitName = UnitStat.UnitName;

	// Unit이미지
	UnitImage = CreateComponent<GameEngineUIRenderer>(ContentsOrder::UIImage);
	UnitImage->CreateAnimation(GetUnitNameToString() += "_Idle", GetUnitNameToString() += "CardAni", 0.1f, 0, 0, false);
	UnitImage->CreateAnimation(GetUnitNameToString() += "_Stay", GetUnitNameToString() += "CardAni", 0.1f, 0, 4, true);
	UnitImage->CreateAnimation(GetUnitNameToString() += "_Att", GetUnitNameToString() += "CardAni", 0.1f, 13, 16, false);
	UnitImage->AutoSpriteSizeOn();
	UnitImage->SetAutoScaleRatio(2.0f);
	UnitImage->Transform.AddLocalPosition(UnitImagePos);
	UnitImage->Transform.AddLocalPosition({ 0.0f, 12.0f, -static_cast<float>(ContentsOrder::UIImage) });
	UnitImage->ChangeAnimation(GetUnitNameToString() += "_Idle");

	Transform.AddLocalPosition({ XInter, 0.0f });

	XInter += 80.0f;

}

void BanPickCard::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BanPickCard::IdleStart()
{
	if (false == IsSelect)
	{
		UnitImage->ChangeAnimation(GetUnitNameToString() += "_Idle");
	}
}

void BanPickCard::IdleUpdate(float _Delta)
{

}

void BanPickCard::EnterStart()
{

}

void BanPickCard::EnterUpdate(float _Delta)
{

}

void BanPickCard::StayStart()
{
	if (false == IsSelect)
	{
		UnitImage->ChangeAnimation(GetUnitNameToString() += "_Stay");
	}

	IsStart = true;

	if (TeamType::Blue == UI_Mouse::GameMouse->GetPlayerTeam())
	{
		Renderer2->ChangeAnimation("BanPickCard_Blue");

	}
	else if (TeamType::Red == UI_Mouse::GameMouse->GetPlayerTeam())
	{
		Renderer2->ChangeAnimation("BanPickCard_Red");
	}

	Renderer2->On();
}

void BanPickCard::StayUpdate(float _Delta)
{
	
}

void BanPickCard::EndStart()
{
	if (false == IsSelect)
	{
		UnitImage->ChangeAnimation(GetUnitNameToString() += "_Idle");
	}

	Renderer2->Off();

}

void BanPickCard::EndUpdate(float _Delta)
{

}

void BanPickCard::ClickStart()
{
	if (false == IsSelect)
	{
		UnitImage->ChangeAnimation(GetUnitNameToString() += "_Att");
		IsSelect = true;
		IsPick = true;
	}
}

void BanPickCard::ClickUpdate(float _Delta)
{

}
